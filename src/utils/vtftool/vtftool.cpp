/*
 *
 * vtftool.cpp
 *
 * Tool for converting JPEG, PNG, TGA and other images to VTF format
 *
 */
#include "vtf/vtf.h"
#include "bitmap/bitmap.h"
#include "tier0/icommandline.h"

#include "utllinkedlist.h"
#include "utlbuffer.h"

/* STB Includes */
#define STB_IMAGE_IMPLEMENTATION
#define STB_DXT_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_dxt.h"


/* Function prototypes */
void                            show_help();
const char*                     flag_to_string(CompiledVtfFlags flags);
CompiledVtfFlags                string_to_flags(const char* str);
const char*                     format_to_string(ImageFormat fmt);
ImageFormat                     string_to_format(const char* fmt);
bool                            check_arg(const char* arg, const char* _short, const char* _long = nullptr);
CUtlVector<const char*>*    	parse_list_arg(char* arg);
void                            create_vtf(struct vtftool_settings_t settings, const char* src, const char* dst);
int                             parse_long_int_arg(char* arg);

/* Globals */
bool g_bVerbose = false;

/* Utility macros */
#define IS_ARG(_name) (check_arg(arg, _name))
#define IS_LARG(_name) (check_arg(arg, _name, _name))
#define CHECK_ARG(_extra_index) (argc > (i + (_extra_index)))
#define NEXT_ARG() (CHECK_ARG(1) ? argv[argc+1] : nullptr)
#define CHECK_ARG_OR_FAIL(_extra_index) if(CHECK_ARG(_extra_index)) { show_help(); exit(1); }
#define VERBOSE_PRINT(...) if(g_bVerbose) { printf(__VA_ARGS__); }
#define ASSERT_FAILURE(_cond, ...) if(!(_cond)){ printf(__VA_ARGS__); exit(1); }

/* It would be great to do this in a nicer way, but not all compilers are epic */
struct {
	CompiledVtfFlags flags;
	const char* name;
} g_FlagMapping[] = {
	{CompiledVtfFlags::TEXTUREFLAGS_ALL_MIPS, "allmips"},
	{CompiledVtfFlags::TEXTUREFLAGS_ANISOTROPIC, "anisotropic"},
	{CompiledVtfFlags::TEXTUREFLAGS_BORDER, "border"},
	{CompiledVtfFlags::TEXTUREFLAGS_CLAMPS, "clamps"},
	{CompiledVtfFlags::TEXTUREFLAGS_CLAMPT, "clampt"},
	{CompiledVtfFlags::TEXTUREFLAGS_CLAMPU, "clampu"},
	{CompiledVtfFlags::TEXTUREFLAGS_DEPTHRENDERTARGET, "depthrendertarget"},
	{CompiledVtfFlags::TEXTUREFLAGS_EIGHTBITALPHA, "8bitalpha"},
	{CompiledVtfFlags::TEXTUREFLAGS_ENVMAP, "envmap"},
	{CompiledVtfFlags::TEXTUREFLAGS_HINT_DXT5, "dxt5"},
	{CompiledVtfFlags::TEXTUREFLAGS_IGNORE_PICMIP, "ignorepicmap"},
	{CompiledVtfFlags::TEXTUREFLAGS_IMMEDIATE_CLEANUP, "immediatecleanup"},
	{CompiledVtfFlags::TEXTUREFLAGS_NODEBUGOVERRIDE, "nodebugoverride"},
	{CompiledVtfFlags::TEXTUREFLAGS_NODEPTHBUFFER, "nodepthbuffer"},
	{CompiledVtfFlags::TEXTUREFLAGS_NOLOD, "nolog"},
	{CompiledVtfFlags::TEXTUREFLAGS_NOMIP, "nomip"},
	{CompiledVtfFlags::TEXTUREFLAGS_NORMAL, "normal"},
	{CompiledVtfFlags::TEXTUREFLAGS_ONEBITALPHA, "1bitalpha"},
	{CompiledVtfFlags::TEXTUREFLAGS_POINTSAMPLE, "pointsample"},
	{CompiledVtfFlags::TEXTUREFLAGS_PROCEDURAL, "procedural"},
	{CompiledVtfFlags::TEXTUREFLAGS_RENDERTARGET, "rendertarget"},
	{CompiledVtfFlags::TEXTUREFLAGS_SINGLECOPY, "singlecopy"},
	{CompiledVtfFlags::TEXTUREFLAGS_SRGB, "srgb"},
	{CompiledVtfFlags::TEXTUREFLAGS_SSBUMP, "ssbump"},
	{CompiledVtfFlags::TEXTUREFLAGS_STAGING_MEMORY, "stagingmemory"},
	{CompiledVtfFlags::TEXTUREFLAGS_TRILINEAR, "trilinear"},
	{CompiledVtfFlags::TEXTUREFLAGS_VERTEXTEXTURE, "vertextexture"},
};

struct {
	ImageFormat format;
	const char* name;
} g_FormatMapping[] = {
	{ImageFormat::IMAGE_FORMAT_A8, "a8"},
	{ImageFormat::IMAGE_FORMAT_ABGR8888, "abgr8888"},
	{ImageFormat::IMAGE_FORMAT_ARGB8888, "argb8888"},
	{ImageFormat::IMAGE_FORMAT_ATI1N, "ati1n"},
	{ImageFormat::IMAGE_FORMAT_ATI2N, "ati2n"},
	{ImageFormat::IMAGE_FORMAT_ATI_DST16, "ati_dst16"},
	{ImageFormat::IMAGE_FORMAT_ATI_DST24, "ati_dst24"},
	{ImageFormat::IMAGE_FORMAT_BGR565, "bgr565"},
	{ImageFormat::IMAGE_FORMAT_BGR888, "bgr888"},
	{ImageFormat::IMAGE_FORMAT_BGR888_BLUESCREEN, "bgr888_bluescreen"},
	{ImageFormat::IMAGE_FORMAT_BGRA4444, "bgra4444"},
	{ImageFormat::IMAGE_FORMAT_BGRA5551, "bgra5551"},
	{ImageFormat::IMAGE_FORMAT_BGRA8888, "bgra8888"},
	{ImageFormat::IMAGE_FORMAT_BGRX5551, "bgrx5551"},
	{ImageFormat::IMAGE_FORMAT_BGRX8888, "bgrx8888"},
	{ImageFormat::IMAGE_FORMAT_DXT1, "dxt1"},
	{ImageFormat::IMAGE_FORMAT_DXT1_ONEBITALPHA, "dxt1_1bitalpha"},
	{ImageFormat::IMAGE_FORMAT_DXT1_RUNTIME, "dxt1_runtime"},
	{ImageFormat::IMAGE_FORMAT_DXT3, "dxt3"},
	{ImageFormat::IMAGE_FORMAT_DXT5, "dxt5"},
	{ImageFormat::IMAGE_FORMAT_DXT5_RUNTIME, "dxt5_runtime"},
	{ImageFormat::IMAGE_FORMAT_I8, "i8"},
	{ImageFormat::IMAGE_FORMAT_IA88, "ia88"},
	{ImageFormat::IMAGE_FORMAT_NV_DST16, "nv_dst16"},
	{ImageFormat::IMAGE_FORMAT_NV_DST24, "nv_dst24"},
	{ImageFormat::IMAGE_FORMAT_NV_INTZ, "nv_intz"},
	{ImageFormat::IMAGE_FORMAT_NV_NULL, "nv_null"},
	{ImageFormat::IMAGE_FORMAT_NV_RAWZ, "nv_rawz"},
	{ImageFormat::IMAGE_FORMAT_P8, "p8"},
	{ImageFormat::IMAGE_FORMAT_R32F, "r32f"},
	{ImageFormat::IMAGE_FORMAT_RGB323232F, "rgb323232f"},
	{ImageFormat::IMAGE_FORMAT_RGB565, "rgb565"},
	{ImageFormat::IMAGE_FORMAT_RGB888, "rgb888"},
	{ImageFormat::IMAGE_FORMAT_RGB888_BLUESCREEN, "rgb888_bluescreen"},
	{ImageFormat::IMAGE_FORMAT_RGBA16161616, "rgba16161616"},
	{ImageFormat::IMAGE_FORMAT_RGBA16161616F, "rgba16161616f"},
	{ImageFormat::IMAGE_FORMAT_RGBA32323232F, "rgba32323232f"},
	{ImageFormat::IMAGE_FORMAT_RGBA8888, "rgba8888"},
	{ImageFormat::IMAGE_FORMAT_UV88, "uv88"},
	{ImageFormat::IMAGE_FORMAT_UVLX8888, "uvlx8888"},
	{ImageFormat::IMAGE_FORMAT_UVWQ8888, "uvwq8888"}
};

/* Settings used to specify settings for the tool */
struct vtftool_settings_t
{
	bool                    no_mips;
	ImageFormat             image_format;
	unsigned int            image_flags;
	int                     width;
	int                     height;
	int                     depth;
	int                     frame_count;
	ImageFormat             default_format;
};

/*
=====================
int main
 Main entry point
=====================
 */
int main(int argc, char** argv)
{
	CommandLine()->CreateCmdLine(argc, argv);
	
	vtftool_settings_t settings;
	memset(&settings, 0, sizeof(vtftool_settings_t));
	/* Set default format */
	settings.default_format = ImageFormat::IMAGE_FORMAT_RGBA8888;
	const char* input = nullptr;
	const char* output = nullptr;
	
	settings.frame_count = 1;

	/* Argument parsing */
	for(unsigned i = 0; i < argc; i++)
	{
		char* arg = argv[i];
		size_t arglen = strlen(arg);

		/* Parse short arg */
		if(*arg == '-' && arglen > 1 && arg[1] != '-')
		{
			if(IS_ARG("-h"))
			{
				show_help();
				exit(0);
			}
			else if(IS_ARG("-v"))
			{
				g_bVerbose = true;
				continue;
			}
			else if(IS_ARG("-o"))
			{
				if(i == argc-1)
					show_help();
				output = argv[i+1];
				i++;
				continue;
			}
			else if(IS_ARG("-i"))
			{
				if(i == argc-1)
					show_help();
				input = argv[i+1];
				i++;
				continue;
			}
		}
		/* Parse long args */
		else if(arg[0] == '-' && arglen > 1 && arg[1] == '-')
		{
			if(IS_LARG("--help"))
			{
				show_help();
				exit(0);
			}
			else if(IS_LARG("--verbose"))
			{
				g_bVerbose = true;
				continue;
			}
			else if(IS_LARG("--version"))
			{
				printf("vtftool v0.1\n");
				exit(0);
			}
			/* --flags is a list argument, as you can specify any number of flags for a VTF */
			else if(IS_LARG("--flags"))
			{
				/* Handle the list args here */
				CUtlVector<const char*> *flags = parse_list_arg(arg);
				for(auto c : *flags)
					settings.image_flags |= string_to_flags(c);

				/* Now check if image_flags is -1 */
				/* If it is, die */
				if(settings.image_flags == -1 || flags->Count() < 1)
				{
					printf("Invalid flags type\n\n");
					show_help();
					exit(1);
				}

				/* Free the list */
				delete flags;
			}
			/* --format is a list argument, but it can only have one value */
			else if(IS_LARG("--format"))
			{
				/* Handle the list here */
				CUtlVector<const char*>* format = parse_list_arg(arg);

				/* Since this isn't technically a list arg, check if the length is more than 1 or less than 0 */
				if(format->Count() <= 0 || format->Count() > 1)
				{
					printf("Invalid image format specified\n\n");
					show_help();
					exit(1);
				}

				settings.image_format = string_to_format((*format)[0]);

				VERBOSE_PRINT("Compiling for format %s\n", (*format)[0]);

				/* Free the list */
				delete format;
			}
			/* --depth tells us the depth of the source image */
			else if(IS_LARG("--depth"))
			{
				/* Parse the depth argument */
				int depth = parse_long_int_arg(arg);

				settings.depth = depth;

				/* Check that the depth is in range */
				switch(depth)
				{
					case 8: settings.default_format = ImageFormat::IMAGE_FORMAT_RGBA8888; break;
					case 16: settings.default_format = ImageFormat::IMAGE_FORMAT_RGBA16161616; break;
					case 32: settings.default_format = ImageFormat::IMAGE_FORMAT_RGBA32323232F; break;
					default:
						printf("Invalid depth passed. Valid options: 8, 16, 32\n");
						exit(1);
				}
			}
		}
	}
	create_vtf(settings, input, output);
}

/*
=====================
void show_help
 Displays help info
=====================
 */
void show_help()
{
	printf("\tvtftool v0.1\n");
	printf("\t-h --help            - Show this help message and exit\n");
	printf("\t-v --verbose         - Enable verbose mode\n");
	printf("\t--flags=<flags>      - Specify texture flags with a comma separated list. Valid values are:\n\t\t");
	for(unsigned int i = 0; i < ARRAYSIZE(g_FlagMapping); i++)
		printf("%s, ", g_FlagMapping[i].name);
	printf("\n");
	printf("\t--format=<format>    - Specify the VTF image format. Valid values are:\n\t\t");
	for(unsigned int i = 0; i < ARRAYSIZE(g_FormatMapping); i++)
		printf("%s, ", g_FormatMapping[i].name);
	printf("\t--nomips             - Don't generate mips for this texture\n");
	printf("\t-i <file>            - Input file\n");
	printf("\t-o <file>            - Output file\n");
	printf("\t--depth=<depth>      - Depth, in bits per channel, of the source image. Defaults to 8\n");
	exit(0);
}

/*
=====================
bool check_arg
 Checks if an arg is set
=====================
 */
bool check_arg(const char* arg, const char* _short, const char* _long)
{
	if(strcmp(arg, _short) == 0) return true;
	if(!_long) return false;
	size_t strlen1 = strlen(arg);
	size_t strlen2 = strlen(_long);
	/* Parse the long arg */
	for(int i = 0; i < strlen1 && i < strlen2; i++)
	{
		if(arg[i] != _long[i]) return false;
	}
	return true;
}

/*
=====================
CUtlLinkedList<const char*> parse_list_arg
 Parses a comma separated list into a linked list
=====================
 */
CUtlVector<const char*>* parse_list_arg(char* arg)
{
	int i = 0;
	size_t len = strlen(arg);
	for(; i < len, arg[i] != '='; i++);
	i++;

	CUtlVector<const char*> *arglist = new CUtlVector<const char*>();
	const char* _list = nullptr;
	for(; i < len; i++)
	{
		if(!_list) _list = &arg[i];
		if(arg[i] == ',')
		{
			arg[i] = '\0';
			arglist->AddToTail(strdup(_list));
			_list = nullptr;
		}
	}
	/* Handle cases where we hit the end of the list */
	if(_list) arglist->AddToTail(strdup(_list));

	return arglist;
}

/*
=====================
parse_long_int_arg
 Parses a long arg as an integer
=====================
 */
int parse_long_int_arg(char* arg)
{
	int i = 0;
	size_t len = strlen(arg);
	for(; i < len; i++)
		if(arg[i] == '=') { i++; break; };
	return strtol(&arg[i], nullptr, 10);
}

/*
=====================
flag_to_string
 Converts a CompiledVtfFlags enum to a string
=====================
 */
const char* flag_to_string(CompiledVtfFlags flags)
{
	for(auto x : g_FlagMapping)
		if(x.flags == flags) return x.name;
	return "";
}

/*
=====================
string_to_flags
 Converts a string to a CompiledVtfFlags enum val
=====================
 */
CompiledVtfFlags string_to_flags(const char* str)
{
	for(auto x : g_FlagMapping)
		if(strcmp(str, x.name) == 0) return x.flags;
	return CompiledVtfFlags::TEXTUREFLAGS_UNUSED_00400000;	/* Return something else here later please */
}

/*
=====================
format_to_string
 Converts an ImageFormat enum to a string
=====================
 */
const char* format_to_string(ImageFormat fmt)
{
	for(auto x : g_FormatMapping)
		if(x.format == fmt) return x.name;
	return "";
}

/*
=====================
string_to_format
 Converts a string to an ImageFormat enum val
=====================
 */
ImageFormat string_to_format(const char* fmt)
{
	for(auto x : g_FormatMapping)
		if(strcmp(fmt, x.name) == 0) return x.format;
	return ImageFormat::IMAGE_FORMAT_UNKNOWN;
}

/*
=====================
create_vtf
 Actually creates the VTF file
=====================
 */
void create_vtf(vtftool_settings_t settings, const char* src, const char* dst)
{
	/* Check params */
	ASSERT_FAILURE(src, "Internal error: src was null\n");
	ASSERT_FAILURE(dst, "Internal error: dst was null\n");
	ASSERT_FAILURE(settings.image_format != ImageFormat::IMAGE_FORMAT_UNKNOWN, "Internal error: Unknown image format passed to create_vtf");

	/* Create the empty VTF container */
	VERBOSE_PRINT("Creating empty VTF texture\n");
	IVTFTexture* pTex = CreateVTFTexture();
	ASSERT_FAILURE(pTex, "Internal error: Failed to create VTF Texture!\n");

	/* Init the texture with our params */
	/* We're going to abuse the system a bit here, and trick the VTF library into converting the image for us */
	/* STB loads images into a buffer in an RGBA format with 8, 16 or 32bits per channel. We will specify 8bits per channel for now */
	VERBOSE_PRINT("pTex->Init w=%u h=%u depth=%u fmt=%s flags=%u frames=%u\n", settings.width, settings.height, settings.depth,
		format_to_string(settings.default_format), settings.image_flags, settings.frame_count);
	bool bres = pTex->Init(settings.width, settings.height, settings.depth, settings.default_format, settings.image_flags, settings.frame_count);

	ASSERT_FAILURE(bres, "Internal error: Failed to init VTF Texture!\n");

	/* Go ahead and load the Texture now */
	void* pImgDat = nullptr;
	int src_width, src_height, src_channels;
	switch(settings.default_format)
	{
		case IMAGE_FORMAT_RGBA8888:
			pImgDat = stbi_load(src, &src_width, &src_height, &src_channels, 0);
			break;
		case IMAGE_FORMAT_RGBA16161616:
			pImgDat = stbi_load_16(src, &src_width, &src_height, &src_channels, 0);
			break;
		case IMAGE_FORMAT_RGBA32323232F:
			pImgDat = stbi_loadf(src, &src_width, &src_height, &src_channels, 0);
			break;
		default:
			ASSERT_FAILURE(0, "Internal error");
			break;
	}

	ASSERT_FAILURE(pImgDat, "Failed to load %s!", src);

	/* Get num mips and frames */
	int num_mips = pTex->MipCount();
	int num_frames = pTex->FrameCount();
	int num_faces = pTex->FaceCount();

	for(int i = 0; i < num_frames; i++)
	{
		for(int j = 0; j < num_faces; j++)
		{
			unsigned char* pStorage = pTex->ImageData(i,j,0);

			VERBOSE_PRINT("Copying data into frame %u, face %u\n", i, j);

			/* Copy in le data */
			int storage_len = pTex->ComputeMipSize(0);
			memcpy(pStorage, pImgDat, storage_len);
		}
	}

	/* Trick the vtf library into converting the image format for us */
	VERBOSE_PRINT("Converting image fromat from %s to %s\n", format_to_string(settings.default_format), format_to_string(settings.image_format));
	pTex->ConvertImageFormat(settings.image_format, false);

	/* Generate the mips */
	VERBOSE_PRINT("Generating mips\n");
	pTex->GenerateMipmaps();

	/* Serialize the VTF texture  */
	VERBOSE_PRINT("Serializing to CUtlBuffer\n");
	CUtlBuffer outbuf;
	pTex->Serialize(outbuf);

	/* Write it finally */
	FILE* file = fopen(dst, "wb");
	if(!file)
		ASSERT_FAILURE("Failed to open the output file %s\n", dst);
	fwrite(outbuf.Base(), 1, outbuf.Size(), file);
	fflush(file);
	fclose(file);
}
