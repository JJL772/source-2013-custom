// Stubs for OpenGL calls 

//#include <GL/gl.h>

#include "tier0/platform.h"
#include "tier1/strtools.h"

#define GL_FUNC(x, y, ret, name, params, unused) \
extern "C" __attribute__((visibility("default"))) ret name params

#define GL_FUNC_VOID(x, y, name, params, unused) \
extern "C" __attribute__((visibility("default"))) void name params

// Nothing 
#define GL_EXT(...)
#define APICALL extern "C" __attribute__((visibility("default")))
#define APIENTRY

// THE FOLLOWING CODE IS FROM GL.H

using GLbitfield = unsigned int;
using GLhandleARB = unsigned int;
typedef unsigned int	GLenum;
typedef unsigned char	GLboolean;
typedef unsigned int	GLbitfield;
typedef void		GLvoid;
typedef signed char	GLbyte;		/* 1-byte signed */
typedef short		GLshort;	/* 2-byte signed */
typedef int		GLint;		/* 4-byte signed */
typedef unsigned char	GLubyte;	/* 1-byte unsigned */
typedef unsigned short	GLushort;	/* 2-byte unsigned */
typedef unsigned int	GLuint;		/* 4-byte unsigned */
typedef int		GLsizei;	/* 4-byte signed */
typedef float		GLfloat;	/* single precision float */
typedef float		GLclampf;	/* single precision float in [0,1] */
typedef double		GLdouble;	/* double precision float */
typedef double		GLclampd;	/* double precision float in [0,1] */
using GLcharARB = char;
using GLvoid = void;
using GLsizeiptrARB = GLsizei*;
using GLintptr = GLint*;
using GLchar = char;
using GLsizeiptr = GLsizei*;
using GLuint64 = uint64_t;

#define GL_NO_ERROR 0
#define GL_FALSE 0
#define GL_TRUE 1

//  THIS IS ALL COPIED FROM GLFUNCS.H

GL_FUNC(OpenGL,true,GLenum,glGetError,(void),())
{
	return GL_NO_ERROR;
}

GL_FUNC_VOID(OpenGL,true,glActiveTexture,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glAlphaFunc,(GLenum a,GLclampf b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glAttachObjectARB,(GLhandleARB a,GLhandleARB b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBegin,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBindAttribLocationARB,(GLhandleARB a,GLuint b,const GLcharARB *c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBindBufferARB,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBindProgramARB,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBindTexture,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBlendColor,(GLclampf a,GLclampf b,GLclampf c,GLclampf d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBlendEquation,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBlendFunc,(GLenum a,GLenum b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBufferDataARB,(GLenum a,GLsizeiptrARB b,const GLvoid *c,GLenum d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glClear,(GLbitfield a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glClearColor,(GLclampf a,GLclampf b,GLclampf c,GLclampf d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glClearDepth,(GLclampd a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glClearStencil,(GLint a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glClipPlane,(GLenum a,const GLdouble *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glColorMask,(GLboolean a,GLboolean b,GLboolean c,GLboolean d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glCompileShaderARB,(GLhandleARB a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glCompressedTexImage2D,(GLenum a,GLint b,GLenum c,GLsizei d,GLsizei e,GLint f,GLsizei g,const GLvoid *h),(a,b,c,d,e,f,g,h))
{
	
}
GL_FUNC_VOID(OpenGL,true,glCompressedTexImage3D,(GLenum a,GLint b,GLenum c,GLsizei d,GLsizei e,GLsizei f,GLint g,GLsizei h,const GLvoid *i),(a,b,c,d,e,f,g,h,i))
{
	
}
GL_FUNC(OpenGL,true,GLhandleARB,glCreateProgramObjectARB,(void),())
{
	return 0;
}
GL_FUNC(OpenGL,true,GLhandleARB,glCreateShaderObjectARB,(GLenum a),(a))
{
	return 0;
}
GL_FUNC_VOID(OpenGL,true,glDeleteBuffersARB,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDeleteObjectARB,(GLhandleARB a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDeleteProgramsARB,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDeleteQueriesARB,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDeleteShader,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDeleteTextures,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDepthFunc,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDepthMask,(GLboolean a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDepthRange,(GLclampd a,GLclampd b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDetachObjectARB,(GLhandleARB a,GLhandleARB b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDisable,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDisableVertexAttribArray,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDrawArrays,(GLenum a,GLint b,GLsizei c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDrawBuffer,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDrawBuffers,(GLsizei a,const GLenum *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDrawRangeElements,(GLenum a,GLuint b,GLuint c,GLsizei d,GLenum e,const GLvoid *f),(a,b,c,d,e,f))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDrawRangeElementsBaseVertex,(GLenum a,GLuint b,GLuint c,GLsizei d,GLenum e,const GLvoid *f, GLenum g),(a,b,c,d,e,f,g))
{
	
}
GL_FUNC_VOID(OpenGL,true,glEnable,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glEnableVertexAttribArray,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glEnd,(void),())
{
	
}
GL_FUNC_VOID(OpenGL,true,glFinish,(void),())
{
	
}
GL_FUNC_VOID(OpenGL,true,glFlush,(void),())
{
	
}
GL_FUNC_VOID(OpenGL,true,glFrontFace,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGenBuffersARB,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGenProgramsARB,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGenQueriesARB,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGenTextures,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetBooleanv,(GLenum a,GLboolean *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetCompressedTexImage,(GLenum a,GLint b,GLvoid *c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetDoublev,(GLenum a,GLdouble *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetFloatv,(GLenum a,GLfloat *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetInfoLogARB,(GLhandleARB a,GLsizei b,GLsizei *c,GLcharARB *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetIntegerv,(GLenum a,GLint *b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetObjectParameterivARB,(GLhandleARB a,GLenum b,GLint *c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetProgramivARB,(GLenum a,GLenum b,GLint *c),(a,b,c))
{
	
}

const char* g_pExtensions[] = {
	"GL_AMD_multi_draw_indirect",
"GL_AMD_seamless_cubemap_per_texture",
"GL_AMD_vertex_shader_layer",
"GL_AMD_vertex_shader_viewport_index",
"GL_ARB_ES2_compatibility",
"GL_ARB_ES3_1_compatibility",
"GL_ARB_ES3_2_compatibility",
"GL_ARB_ES3_compatibility",
"GL_ARB_arrays_of_arrays",
"GL_ARB_base_instance",
"GL_ARB_bindless_texture",
"GL_ARB_blend_func_extended",
"GL_ARB_buffer_storage",
"GL_ARB_clear_buffer_object",
"GL_ARB_clear_texture",
"GL_ARB_clip_control",
"GL_ARB_color_buffer_float",
"GL_ARB_compatibility",
"GL_ARB_compressed_texture_pixel_storage",
"GL_ARB_compute_shader",
"GL_ARB_compute_variable_group_size",
"GL_ARB_conditional_render_inverted",
"GL_ARB_conservative_depth",
"GL_ARB_copy_buffer",
"GL_ARB_copy_image",
"GL_ARB_cull_distance",
"GL_ARB_debug_output",
"GL_ARB_depth_buffer_float",
"GL_ARB_depth_clamp",
"GL_ARB_depth_texture",
"GL_ARB_derivative_control",
"GL_ARB_direct_state_access",
"GL_ARB_draw_buffers",
"GL_ARB_draw_buffers_blend",
"GL_ARB_draw_elements_base_vertex",
"GL_ARB_draw_indirect",
"GL_ARB_draw_instanced",
"GL_ARB_enhanced_layouts",
"GL_ARB_explicit_attrib_location",
"GL_ARB_explicit_uniform_location",
"GL_ARB_fragment_coord_conventions",
"GL_ARB_fragment_layer_viewport",
"GL_ARB_fragment_program",
"GL_ARB_fragment_program_shadow",
"GL_ARB_fragment_shader",
"GL_ARB_fragment_shader_interlock",
"GL_ARB_framebuffer_no_attachments",
"GL_ARB_framebuffer_object",
"GL_ARB_framebuffer_sRGB",
"GL_ARB_geometry_shader4",
"GL_ARB_get_program_binary",
"GL_ARB_get_texture_sub_image",
"GL_ARB_gl_spirv",
"GL_ARB_gpu_shader5",
"GL_ARB_gpu_shader_fp64",
"GL_ARB_gpu_shader_int64",
"GL_ARB_half_float_pixel",
"GL_ARB_half_float_vertex",
"GL_ARB_imaging",
"GL_ARB_indirect_parameters",
"GL_ARB_instanced_arrays",
"GL_ARB_internalformat_query",
"GL_ARB_internalformat_query2",
"GL_ARB_invalidate_subdata",
"GL_ARB_map_buffer_alignment",
"GL_ARB_map_buffer_range",
"GL_ARB_multi_bind",
"GL_ARB_multi_draw_indirect",
"GL_ARB_multisample",
"GL_ARB_multitexture",
"GL_ARB_occlusion_query",
"GL_ARB_occlusion_query2",
"GL_ARB_parallel_shader_compile",
"GL_ARB_pipeline_statistics_query",
"GL_ARB_pixel_buffer_object",
"GL_ARB_point_parameters",
"GL_ARB_point_sprite",
"GL_ARB_polygon_offset_clamp",
"GL_ARB_post_depth_coverage",
"GL_ARB_program_interface_query",
"GL_ARB_provoking_vertex",
"GL_ARB_query_buffer_object",
"GL_ARB_robust_buffer_access_behavior",
"GL_ARB_robustness",
"GL_ARB_sample_locations",
"GL_ARB_sample_shading",
"GL_ARB_sampler_objects",
"GL_ARB_seamless_cube_map",
"GL_ARB_seamless_cubemap_per_texture",
"GL_ARB_separate_shader_objects",
"GL_ARB_shader_atomic_counter_ops",
"GL_ARB_shader_atomic_counters",
"GL_ARB_shader_ballot",
"GL_ARB_shader_bit_encoding",
"GL_ARB_shader_clock",
"GL_ARB_shader_draw_parameters",
"GL_ARB_shader_group_vote",
"GL_ARB_shader_image_load_store",
"GL_ARB_shader_image_size",
"GL_ARB_shader_objects",
"GL_ARB_shader_precision",
"GL_ARB_shader_storage_buffer_object",
"GL_ARB_shader_subroutine",
"GL_ARB_shader_texture_image_samples",
"GL_ARB_shader_texture_lod",
"GL_ARB_shader_viewport_layer_array",
"GL_ARB_shading_language_100",
"GL_ARB_shading_language_420pack",
"GL_ARB_shading_language_include",
"GL_ARB_shading_language_packing",
"GL_ARB_shadow",
"GL_ARB_sparse_buffer",
"GL_ARB_sparse_texture",
"GL_ARB_sparse_texture2",
"GL_ARB_sparse_texture_clamp",
"GL_ARB_spirv_extensions",
"GL_ARB_stencil_texturing",
"GL_ARB_sync",
"GL_ARB_tessellation_shader",
"GL_ARB_texture_barrier",
"GL_ARB_texture_border_clamp",
"GL_ARB_texture_buffer_object",
"GL_ARB_texture_buffer_object_rgb32",
"GL_ARB_texture_buffer_range",
"GL_ARB_texture_compression",
"GL_ARB_texture_compression_bptc",
"GL_ARB_texture_compression_rgtc",
"GL_ARB_texture_cube_map",
"GL_ARB_texture_cube_map_array",
"GL_ARB_texture_env_add",
"GL_ARB_texture_env_combine",
"GL_ARB_texture_env_crossbar",
"GL_ARB_texture_env_dot3",
"GL_ARB_texture_filter_anisotropic",
"GL_ARB_texture_filter_minmax",
"GL_ARB_texture_float",
"GL_ARB_texture_gather",
"GL_ARB_texture_mirror_clamp_to_edge",
"GL_ARB_texture_mirrored_repeat",
"GL_ARB_texture_multisample",
"GL_ARB_texture_non_power_of_two",
"GL_ARB_texture_query_levels",
"GL_ARB_texture_query_lod",
"GL_ARB_texture_rectangle",
"GL_ARB_texture_rg",
"GL_ARB_texture_rgb10_a2ui",
"GL_ARB_texture_stencil8",
"GL_ARB_texture_storage",
"GL_ARB_texture_storage_multisample",
"GL_ARB_texture_swizzle",
"GL_ARB_texture_view",
"GL_ARB_timer_query",
"GL_ARB_transform_feedback2",
"GL_ARB_transform_feedback3",
"GL_ARB_transform_feedback_instanced",
"GL_ARB_transform_feedback_overflow_query",
"GL_ARB_transpose_matrix",
"GL_ARB_uniform_buffer_object",
"GL_ARB_vertex_array_bgra",
"GL_ARB_vertex_array_object",
"GL_ARB_vertex_attrib_64bit",
"GL_ARB_vertex_attrib_binding",
"GL_ARB_vertex_buffer_object",
"GL_ARB_vertex_program",
"GL_ARB_vertex_shader",
"GL_ARB_vertex_type_10f_11f_11f_rev",
"GL_ARB_vertex_type_2_10_10_10_rev",
"GL_ARB_viewport_array",
"GL_ARB_window_pos",
"GL_ATI_draw_buffers",
"GL_ATI_texture_float",
"GL_ATI_texture_mirror_once",
"GL_EXTX_framebuffer_mixed_formats",
"GL_EXT_Cg_shader",
"GL_EXT_abgr",
"GL_EXT_bgra",
"GL_EXT_bindable_uniform",
"GL_EXT_blend_color",
"GL_EXT_blend_equation_separate",
"GL_EXT_blend_func_separate",
"GL_EXT_blend_minmax",
"GL_EXT_blend_subtract",
"GL_EXT_compiled_vertex_array",
"GL_EXT_depth_bounds_test",
"GL_EXT_direct_state_access",
"GL_EXT_draw_buffers2",
"GL_EXT_draw_instanced",
"GL_EXT_draw_range_elements",
"GL_EXT_fog_coord",
"GL_EXT_framebuffer_blit",
"GL_EXT_framebuffer_multisample",
"GL_EXT_framebuffer_multisample_blit_scaled",
"GL_EXT_framebuffer_object",
"GL_EXT_framebuffer_sRGB",
"GL_EXT_geometry_shader4",
"GL_EXT_gpu_program_parameters",
"GL_EXT_gpu_shader4",
"GL_EXT_import_sync_object",
"GL_EXT_memory_object",
"GL_EXT_memory_object_fd",
"GL_EXT_multi_draw_arrays",
"GL_EXT_multiview_texture_multisample",
"GL_EXT_multiview_timer_query",
"GL_EXT_packed_depth_stencil",
"GL_EXT_packed_float",
"GL_EXT_packed_pixels",
"GL_EXT_pixel_buffer_object",
"GL_EXT_point_parameters",
"GL_EXT_polygon_offset_clamp",
"GL_EXT_post_depth_coverage",
"GL_EXT_provoking_vertex",
"GL_EXT_raster_multisample",
"GL_EXT_rescale_normal",
"GL_EXT_secondary_color",
"GL_EXT_semaphore",
"GL_EXT_semaphore_fd",
"GL_EXT_separate_shader_objects",
"GL_EXT_separate_specular_color",
"GL_EXT_shader_image_load_formatted",
"GL_EXT_shader_image_load_store",
"GL_EXT_shader_integer_mix",
"GL_EXT_shadow_funcs",
"GL_EXT_sparse_texture2",
"GL_EXT_stencil_two_side",
"GL_EXT_stencil_wrap",
"GL_EXT_texture3D",
"GL_EXT_texture_array",
"GL_EXT_texture_buffer_object",
"GL_EXT_texture_compression_dxt1",
"GL_EXT_texture_compression_latc",
"GL_EXT_texture_compression_rgtc",
"GL_EXT_texture_compression_s3tc",
"GL_EXT_texture_cube_map",
"GL_EXT_texture_edge_clamp",
"GL_EXT_texture_env_add",
"GL_EXT_texture_env_combine",
"GL_EXT_texture_env_dot3",
"GL_EXT_texture_filter_anisotropic",
"GL_EXT_texture_filter_minmax",
"GL_EXT_texture_integer",
"GL_EXT_texture_lod",
"GL_EXT_texture_lod_bias",
"GL_EXT_texture_mirror_clamp",
"GL_EXT_texture_object",
"GL_EXT_texture_sRGB",
"GL_EXT_texture_sRGB_R8",
"GL_EXT_texture_sRGB_decode",
"GL_EXT_texture_shadow_lod",
"GL_EXT_texture_shared_exponent",
"GL_EXT_texture_storage",
"GL_EXT_texture_swizzle",
"GL_EXT_timer_query",
"GL_EXT_transform_feedback2",
"GL_EXT_vertex_array",
"GL_EXT_vertex_array_bgra",
"GL_EXT_vertex_attrib_64bit",
"GL_EXT_window_rectangles",
"GL_EXT_x11_sync_object",
"GL_IBM_rasterpos_clip",
"GL_IBM_texture_mirrored_repeat",
"GL_KHR_blend_equation_advanced",
"GL_KHR_blend_equation_advanced_coherent",
"GL_KHR_context_flush_control",
"GL_KHR_debug",
"GL_KHR_no_error",
"GL_KHR_parallel_shader_compile",
"GL_KHR_robust_buffer_access_behavior",
"GL_KHR_robustness",
"GL_KHR_shader_subgroup",
"GL_KTX_buffer_region",
"GL_NVX_blend_equation_advanced_multi_draw_buffers",
"GL_NVX_conditional_render",
"GL_NVX_gpu_memory_info",
"GL_NVX_nvenc_interop",
"GL_NVX_progress_fence",
"GL_NV_ES1_1_compatibility",
"GL_NV_ES3_1_compatibility",
"GL_NV_alpha_to_coverage_dither_control",
"GL_NV_bindless_multi_draw_indirect",
"GL_NV_bindless_multi_draw_indirect_count",
"GL_NV_bindless_texture",
"GL_NV_blend_equation_advanced",
"GL_NV_blend_equation_advanced_coherent",
"GL_NV_blend_minmax_factor",
"GL_NV_blend_square",
"GL_NV_clip_space_w_scaling",
"GL_NV_command_list",
"GL_NV_compute_program5",
"GL_NV_conditional_render",
"GL_NV_conservative_raster",
"GL_NV_conservative_raster_dilate",
"GL_NV_conservative_raster_pre_snap_triangles",
"GL_NV_copy_depth_to_color",
"GL_NV_copy_image",
"GL_NV_depth_buffer_float",
"GL_NV_depth_clamp",
"GL_NV_draw_texture",
"GL_NV_draw_vulkan_image",
"GL_NV_explicit_multisample",
"GL_NV_feature_query",
"GL_NV_fence",
"GL_NV_fill_rectangle",
"GL_NV_float_buffer",
"GL_NV_fog_distance",
"GL_NV_fragment_coverage_to_color",
"GL_NV_fragment_program",
"GL_NV_fragment_program2",
"GL_NV_fragment_program_option",
"GL_NV_fragment_shader_interlock",
"GL_NV_framebuffer_mixed_samples",
"GL_NV_framebuffer_multisample_coverage",
"GL_NV_geometry_shader4",
"GL_NV_geometry_shader_passthrough",
"GL_NV_gpu_multicast",
"GL_NV_gpu_program4",
"GL_NV_gpu_program4_1",
"GL_NV_gpu_program5",
"GL_NV_gpu_program5_mem_extended",
"GL_NV_gpu_program_fp64",
"GL_NV_gpu_shader5",
"GL_NV_half_float",
"GL_NV_internalformat_sample_query",
"GL_NV_light_max_exponent",
"GL_NV_memory_attachment",
"GL_NV_memory_object_sparse",
"GL_NV_multisample_coverage",
"GL_NV_multisample_filter_hint",
"GL_NV_occlusion_query",
"GL_NV_packed_depth_stencil",
"GL_NV_parameter_buffer_object",
"GL_NV_parameter_buffer_object2",
"GL_NV_path_rendering",
"GL_NV_path_rendering_shared_edge",
"GL_NV_pixel_data_range",
"GL_NV_point_sprite",
"GL_NV_primitive_restart",
"GL_NV_query_resource",
"GL_NV_query_resource_tag",
"GL_NV_register_combiners",
"GL_NV_register_combiners2",
"GL_NV_robustness_video_memory_purge",
"GL_NV_sample_locations",
"GL_NV_sample_mask_override_coverage",
"GL_NV_shader_atomic_counters",
"GL_NV_shader_atomic_float",
"GL_NV_shader_atomic_float64",
"GL_NV_shader_atomic_fp16_vector",
"GL_NV_shader_atomic_int64",
"GL_NV_shader_buffer_load",
"GL_NV_shader_storage_buffer_object",
"GL_NV_shader_subgroup_partitioned",
"GL_NV_shader_thread_group",
"GL_NV_shader_thread_shuffle",
"GL_NV_stereo_view_rendering",
"GL_NV_texgen_reflection",
"GL_NV_texture_barrier",
"GL_NV_texture_compression_vtc",
"GL_NV_texture_env_combine4",
"GL_NV_texture_multisample",
"GL_NV_texture_rectangle",
"GL_NV_texture_rectangle_compressed",
"GL_NV_texture_shader",
"GL_NV_texture_shader2",
"GL_NV_texture_shader3",
"GL_NV_timeline_semaphore",
"GL_NV_transform_feedback",
"GL_NV_transform_feedback2",
"GL_NV_uniform_buffer_unified_memory",
"GL_NV_vdpau_interop",
"GL_NV_vdpau_interop2",
"GL_NV_vertex_array_range",
"GL_NV_vertex_array_range2",
"GL_NV_vertex_attrib_integer_64bit",
"GL_NV_vertex_buffer_unified_memory",
"GL_NV_vertex_program",
"GL_NV_vertex_program1_1",
"GL_NV_vertex_program2",
"GL_NV_vertex_program2_option",
"GL_NV_vertex_program3",
"GL_NV_viewport_array2",
"GL_NV_viewport_swizzle",
"GL_OVR_multiview",
"GL_OVR_multiview2",
"GL_S3_s3tc",
"GL_SGIS_generate_mipmap",
"GL_SGIS_texture_lod",
"GL_SGIX_depth_texture",
"GL_SGIX_shadow",
"GL_SUN_slice_accum",
};

int g_nExtCount = sizeof(g_pExtensions) / sizeof(g_pExtensions[0]);

#define GL_VENDOR 0x1f00
#define GL_RENDERER 0x1f01
#define GL_VERSION 0x1f02
#define GL_SHADING_LANGUAGE_VERSION 0x8b8c
#define GL_EXTENSIONS 0x1f03

GL_FUNC(OpenGL,true,const GLubyte *,glGetString,(GLenum a),(a))
{
	printf("STUBBED THAT MOTHERFUCKER\n");
	if(a == GL_VENDOR)
	{
		return "Nvidia";
	}
	else if(a == GL_RENDERER)
	{
		return "GTX 1070";
	}
	else if(a == GL_VERSION)
	{
		return "4.6.0";
	}
	else if(a == GL_SHADING_LANGUAGE_VERSION)
	{
		return "4.6.0";
	}
	else if(a == GL_EXTENSIONS)
	{
		static size_t strSz = g_nExtCount * 32;
		static char* gpExtString = (char*)calloc(1, g_nExtCount * 32);
		if(!*gpExtString)
		{
			for(int i = 0; i < g_nExtCount; i++)
			{
				strncat(gpExtString, g_pExtensions[i], strSz);
			}
		}
		return (const GLubyte*)gpExtString;
	}
	else
		return "";
}
GL_FUNC_VOID(OpenGL,true,glGetTexImage,(GLenum a,GLint b,GLenum c,GLenum d,GLvoid *e),(a,b,c,d,e))
{
	
}
GL_FUNC(OpenGL,true,GLint,glGetUniformLocationARB,(GLhandleARB a,const GLcharARB *b),(a,b))
{
	return 0;
}
GL_FUNC(OpenGL,true,GLboolean,glIsEnabled,(GLenum a),(a))
{
	return GL_FALSE;
}
GL_FUNC(OpenGL,true,GLboolean,glIsTexture,(GLuint a),(a))
{
	return GL_FALSE;
}
GL_FUNC_VOID(OpenGL,true,glLinkProgramARB,(GLhandleARB a),(a))
{
	
}
GL_FUNC(OpenGL,true,GLvoid*,glMapBufferARB,(GLenum a,GLenum b),(a,b))
{
	return nullptr;
}
GL_FUNC_VOID(OpenGL,true,glOrtho,(GLdouble a,GLdouble b,GLdouble c,GLdouble d,GLdouble e,GLdouble f),(a,b,c,d,e,f))
{
	
}
GL_FUNC_VOID(OpenGL,true,glPixelStorei,(GLenum a,GLint b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glPolygonMode,(GLenum a,GLenum b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glPolygonOffset,(GLfloat a,GLfloat b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glPopAttrib,(void),())
{
	
}
GL_FUNC_VOID(OpenGL,true,glProgramStringARB,(GLenum a,GLenum b,GLsizei c,const GLvoid *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glPushAttrib,(GLbitfield a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glReadBuffer,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glScissor,(GLint a,GLint b,GLsizei c,GLsizei d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glShaderSourceARB,(GLhandleARB a,GLsizei b,const GLcharARB **c,const GLint *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glStencilFunc,(GLenum a,GLint b,GLuint c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glStencilMask,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glStencilOp,(GLenum a,GLenum b,GLenum c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glTexCoord2f,(GLfloat a,GLfloat b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glTexImage2D,(GLenum a,GLint b,GLint c,GLsizei d,GLsizei e,GLint f,GLenum g,GLenum h,const GLvoid *i),(a,b,c,d,e,f,g,h,i))
{
	
}
GL_FUNC_VOID(OpenGL,true,glTexImage3D,(GLenum a,GLint b,GLint c,GLsizei d,GLsizei e,GLsizei f,GLint g,GLenum h,GLenum i,const GLvoid *j),(a,b,c,d,e,f,g,h,i,j))
{
	
}
GL_FUNC_VOID(OpenGL,true,glTexParameterfv,(GLenum a,GLenum b,const GLfloat *c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glTexParameteri,(GLenum a,GLenum b,GLint c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glTexSubImage2D,(GLenum a,GLint b,GLint c,GLint d,GLsizei e,GLsizei f,GLenum g,GLenum h,const GLvoid *i),(a,b,c,d,e,f,g,h,i))
{
	
}
GL_FUNC_VOID(OpenGL,true,glUniform1f,(GLint a,GLfloat b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glUniform1i,(GLint a,GLint b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glUniform1iARB,(GLint a,GLint b),(a,b))
{
	
}
GL_FUNC_VOID(OpenGL,true,glUniform4fv,(GLint a,GLsizei b,const GLfloat *c),(a,b,c))
{
	
}
GL_FUNC(OpenGL,true,GLboolean,glUnmapBuffer,(GLenum a),(a))
{
	return GL_TRUE;
}
GL_FUNC_VOID(OpenGL,true,glUseProgram,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glVertex3f,(GLfloat a,GLfloat b,GLfloat c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL,true,glVertexAttribPointer,(GLuint a,GLint b,GLenum c,GLboolean d,GLsizei e,const GLvoid *f),(a,b,c,d,e,f))
{
	
}
GL_FUNC_VOID(OpenGL,true,glViewport,(GLint a,GLint b,GLsizei c,GLsizei d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glEnableClientState,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDisableClientState,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glClientActiveTexture,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glVertexPointer,(GLint a,GLenum b,GLsizei c,const GLvoid *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glTexCoordPointer,(GLint a,GLenum b,GLsizei c,const GLvoid *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glProgramEnvParameters4fvEXT,(GLenum a,GLuint b,GLsizei c,const GLfloat *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glColor4sv,(const GLshort  *a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glStencilOpSeparate,(GLenum a,GLenum b,GLenum c,GLenum d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glStencilFuncSeparate,(GLenum a,GLenum b,GLint c,GLuint d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetTexLevelParameteriv,(GLenum a,GLint b,GLenum c,GLint *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(OpenGL,true,glColor4f,(GLfloat a,GLfloat b,GLfloat c,GLfloat d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glBindFramebufferEXT,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glBindRenderbufferEXT,(GLenum a,GLuint b),(a,b))
{
	
}
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8cd6

GL_FUNC(GL_EXT_framebuffer_object,false,GLenum,glCheckFramebufferStatusEXT,(GLenum a),(a))
{
	return GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT;
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glDeleteRenderbuffersEXT,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glFramebufferRenderbufferEXT,(GLenum a,GLenum b,GLenum c,GLuint d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glFramebufferTexture2DEXT,(GLenum a,GLenum b,GLenum c,GLuint d,GLint e),(a,b,c,d,e))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glFramebufferTexture3DEXT,(GLenum a,GLenum b,GLenum c,GLuint d,GLint e,GLint f),(a,b,c,d,e,f))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glGenFramebuffersEXT,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glGenRenderbuffersEXT,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_object,false,glDeleteFramebuffersEXT,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_blit,false,glBlitFramebufferEXT,(GLint a,GLint b,GLint c,GLint d,GLint e,GLint f,GLint g,GLint h,GLbitfield i,GLenum j),(a,b,c,d,e,f,g,h,i,j))
{
	
}
GL_FUNC_VOID(GL_EXT_framebuffer_multisample,false,glRenderbufferStorageMultisampleEXT,(GLenum a,GLsizei b,GLenum c,GLsizei d,GLsizei e),(a,b,c,d,e))
{
	
}
GL_FUNC(GL_APPLE_fence,false,GLboolean,glTestFenceAPPLE,(GLuint a),(a))
{
	return GL_FALSE;
}
GL_FUNC_VOID(GL_APPLE_fence,false,glSetFenceAPPLE,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(GL_APPLE_fence,false,glFinishFenceAPPLE,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(GL_APPLE_fence,false,glDeleteFencesAPPLE,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_APPLE_fence,false,glGenFencesAPPLE,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC(GL_NV_fence,false,GLboolean,glTestFenceNV,(GLuint a),(a))
{
	return GL_FALSE;
}
GL_FUNC_VOID(GL_NV_fence,false,glSetFenceNV,(GLuint a,GLenum b),(a,b))
{
	
}
GL_FUNC_VOID(GL_NV_fence,false,glFinishFenceNV,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(GL_NV_fence,false,glDeleteFencesNV,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_NV_fence,false,glGenFencesNV,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_draw_buffers2,true,glColorMaskIndexedEXT,(GLuint a,GLboolean b,GLboolean c,GLboolean d,GLboolean e),(a,b,c,d,e))
{
	
}
GL_FUNC_VOID(GL_EXT_draw_buffers2,true,glEnableIndexedEXT,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_draw_buffers2,true,glDisableIndexedEXT,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(GL_EXT_draw_buffers2,true,glGetBooleanIndexedvEXT,(GLenum a,GLuint b,GLboolean  *c),(a,b,c))
{
	
}
GL_FUNC_VOID(GL_EXT_bindable_uniform,false,glUniformBufferEXT,(GLuint a,GLint b,GLuint c),(a,b,c))
{
	
}
GL_FUNC(GL_EXT_bindable_uniform,false,int,glGetUniformBufferSizeEXT,(GLenum a, GLenum b),(a,b))
{
	return 0;
}
GL_FUNC(GL_EXT_bindable_uniform,false,GLintptr,glGetUniformOffsetEXT,(GLenum a, GLenum b),(a,b))
{
	return 0;
}
GL_FUNC_VOID(GL_APPLE_flush_buffer_range,false,glBufferParameteriAPPLE,(GLenum a,GLenum b,GLint c),(a,b,c))
{
	
}
GL_FUNC_VOID(GL_APPLE_flush_buffer_range,false,glFlushMappedBufferRangeAPPLE,(GLenum a,GLintptr b,GLsizeiptr c),(a,b,c))
{
	
}
GL_FUNC(GL_ARB_map_buffer_range,false,void*,glMapBufferRange,(GLenum a,GLintptr b,GLsizeiptr c,GLbitfield d),(a,b,c,d))
{
	return nullptr;
}
GL_FUNC_VOID(GL_ARB_map_buffer_range,false,glFlushMappedBufferRange,(GLenum a,GLintptr b,GLsizeiptr c),(a,b,c))
{
	
}
GL_FUNC_VOID(GL_ARB_vertex_buffer_object,true,glBufferSubData,(GLenum a,GLintptr b,GLsizeiptr c,const GLvoid *d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(GL_ARB_occlusion_query,false,glBeginQueryARB,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_occlusion_query,false,glEndQueryARB,(GLenum a),(a))
{
	
}
GL_FUNC_VOID(GL_ARB_occlusion_query,false,glGetQueryObjectivARB,(GLuint a,GLenum b,GLint *c),(a,b,c))
{
	
}
GL_FUNC_VOID(GL_ARB_occlusion_query,false,glGetQueryObjectuivARB,(GLuint a,GLenum b,GLuint *c),(a,b,c))
{
	
}
GL_FUNC_VOID(GL_APPLE_texture_range,false,glTextureRangeAPPLE,(GLenum a,GLsizei b,void *c),(a,b,c))
{
	
}
GL_FUNC_VOID(GL_APPLE_texture_range,false,glGetTexParameterPointervAPPLE,(GLenum a,GLenum b,void* *c),(a,b,c))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glBindFramebuffer,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glBindRenderbuffer,(GLenum a,GLuint b),(a,b))
{
	
}
GL_FUNC(GL_ARB_framebuffer_object,false,GLenum,glCheckFramebufferStatus,(GLenum a),(a))
{
	return 0;
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glDeleteRenderbuffers,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glFramebufferRenderbuffer,(GLenum a,GLenum b,GLenum c,GLuint d),(a,b,c,d))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glFramebufferTexture2D,(GLenum a,GLenum b,GLenum c,GLuint d,GLint e),(a,b,c,d,e))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glFramebufferTexture3D,(GLenum a,GLenum b,GLenum c,GLuint d,GLint e,GLint f),(a,b,c,d,e,f))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glGenFramebuffers,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glGenRenderbuffers,(GLsizei a,GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glDeleteFramebuffers,(GLsizei a,const GLuint *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glBlitFramebuffer,(GLint a,GLint b,GLint c,GLint d,GLint e,GLint f,GLint g,GLint h,GLbitfield i,GLenum j),(a,b,c,d,e,f,g,h,i,j))
{
	
}
GL_FUNC_VOID(GL_ARB_framebuffer_object,false,glRenderbufferStorageMultisample,(GLenum a,GLsizei b,GLenum c,GLsizei d,GLsizei e),(a,b,c,d,e))
{
	
}
GL_FUNC_VOID(GL_GREMEDY_string_marker,false,glStringMarkerGREMEDY,(GLsizei a,const void *b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_debug_output,false,glDebugMessageCallbackARB,(void (APIENTRY *a)(GLenum, GLenum , GLuint , GLenum , GLsizei , const GLchar* , GLvoid*) ,void* b),(a,b))
{
	
}
GL_FUNC_VOID(GL_ARB_debug_output,false,glDebugMessageControlARB,(GLenum a, GLenum b, GLenum c, GLsizei d, const GLuint* e, GLboolean f),(a,b,c,d,e,f))
{
	
}
GL_FUNC_VOID(GL_EXT_direct_state_access,false,glBindMultiTextureEXT,(GLenum a,GLuint b, GLuint c),(a,b,c))
{
	
}
GL_FUNC_VOID(OpenGL, true, glGenSamplers, (GLuint a, GLuint *b), (a, b))
{
	
}
GL_FUNC_VOID(OpenGL, true, glDeleteSamplers, (GLsizei a, const GLuint *b), (a, b))
{
	
}
GL_FUNC_VOID(OpenGL, true, glBindSampler, (GLuint a, GLuint b), (a, b))
{
	
}
GL_FUNC_VOID(OpenGL, true, glSamplerParameteri, (GLuint a, GLenum b, GLint c), (a, b, c))
{
	
}
GL_FUNC_VOID(OpenGL, true, glSamplerParameterf, (GLuint a, GLenum b, GLfloat c), (a, b, c))
{
	
}
GL_FUNC_VOID(OpenGL, true, glSamplerParameterfv, (GLuint a, GLenum b, const GLfloat *c), (a, b, c))
{
	
}
GL_FUNC(GL_NV_bindless_texture, false, GLuint64, glGetTextureHandleNV, (GLuint texture), (texture))
{
	return 0;
}
GL_FUNC(GL_NV_bindless_texture, false, GLuint64, glGetTextureSamplerHandleNV, (GLuint texture, GLuint sampler), (texture, sampler))
{
	return 0;
}
GL_FUNC_VOID(GL_NV_bindless_texture, false, glMakeTextureHandleResidentNV, (GLuint64 handle), (handle))
{
	
}
GL_FUNC_VOID(GL_NV_bindless_texture, false, glMakeTextureHandleNonResidentNV, (GLuint64 handle), (handle))
{
	
}
GL_FUNC_VOID(GL_NV_bindless_texture, false, glUniformHandleui64NV, (GLint location, GLuint64 value), (location, value))
{
	
}
GL_FUNC_VOID(GL_NV_bindless_texture, false, glUniformHandleui64vNV, (int location, GLsizei count, const GLuint64 *value), (location count, value))
{
	
}
GL_FUNC_VOID(GL_NV_bindless_texture, false, glProgramUniformHandleui64NV, (GLuint program, GLint location, GLuint64 value), (program, location, value))
{
	
}
GL_FUNC_VOID(GL_NV_bindless_texture, false, glProgramUniformHandleui64vNV, (GLuint program, GLint location, GLsizei count, const GLuint64 *values), (program, location, count, values))
{
	
}
GL_FUNC(GL_NV_bindless_texture, false, GLboolean, glIsTextureHandleResidentNV, (GLuint64 handle), (handle))
{
	return GL_FALSE;
}
GL_FUNC_VOID(OpenGL,true,glGenQueries,(GLsizei n, GLuint *ids), (n, ids))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDeleteQueries,(GLsizei n, const GLuint *ids),(n, ids))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBeginQuery,(GLenum target, GLuint id), (target, id))
{
	
}
GL_FUNC_VOID(OpenGL,true,glEndQuery,(GLenum target), (target))
{
	
}
GL_FUNC_VOID(OpenGL,true,glQueryCounter,(GLuint id, GLenum target), (id, target))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetQueryObjectiv,(GLuint id, GLenum pname, GLint *params), (id, pname, params))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGetQueryObjectui64v,(GLuint id, GLenum pname, GLuint64 *params), (id, pname, params))
{
	
}
GL_FUNC_VOID(OpenGL,true,glCopyBufferSubData,(GLenum readtarget, GLenum writetarget, GLintptr readoffset, GLintptr writeoffset, GLsizeiptr size),(readtarget, writetarget, readoffset, writeoffset, size))
{
	
}
GL_FUNC_VOID(OpenGL,true,glGenVertexArrays,(GLsizei n, GLuint *arrays),(n, arrays))
{
	
}
GL_FUNC_VOID(OpenGL,true,glDeleteVertexArrays,(GLsizei n, GLuint *arrays),(n, arrays))
{
	
}
GL_FUNC_VOID(OpenGL,true,glBindVertexArray,(GLuint a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glPushClientAttrib,(GLbitfield a),(a))
{
	
}
GL_FUNC_VOID(OpenGL,true,glPopClientAttrib,(void),())
{
	
}
GL_FUNC_VOID( GL_ARB_buffer_storage, false, glBufferStorage, (GLenum target, GLsizeiptr size, const void *data, GLbitfield flags), (target, size, data, flags) )
{
	
}
