/*

Intercepts SDL2 calls and modifies them to be compatible with vulkan

*/

#include <stddef.h>
#include <stdint.h>
#include <dlfcn.h>
#include <unistd.h>

#include <SDL2/SDL_video.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_vulkan.h>
#include <SDL2/SDL.h>

#define APICALL extern "C" __attribute__((visibility("default")))

//    SDL_WINDOW_OPENGL = 0x00000002,             /**< window usable with OpenGL context */
//    SDL_WINDOW_VULKAN        = 0x10000000,      /**< window usable for Vulkan surface */

typedef SDL_Window *(*pfnSDL_CreateWindow)(const char *, int, int, int, int, uint32_t);
typedef void(*pfnSDL_SetWindowTitle)(SDL_Window*,const char*);

void *g_pSDLHandle = nullptr;
pfnSDL_CreateWindow g_pCreateWindow = nullptr;
pfnSDL_SetWindowTitle g_pSetWindowTitle = nullptr;

static void *LoadSDL2();
static pfnSDL_CreateWindow GetCreateWindowFunc();
static pfnSDL_SetWindowTitle GetSetWindowTitleFunc();

/**
 * Using this to override the SDL2 SDL_CreateWindow function so we can inject what we need in there.
 */
APICALL SDL_Window *SDL_CreateWindow(const char *title, int x, int y, int w, int h, uint32_t flags)
{
	printf("TRACE: Intercepted call to SDL_CreateWindow: x=%i y=%i w=%i h=%i title=%s\n", x, y, w, h, title);

	char newTitle[512];
	snprintf(newTitle, sizeof(newTitle), "%s [On Vulkan via ToVK]", title);

	/* Clear the OpenGL flag and substitute the Vulkan flag */
	flags &= ~(SDL_WINDOW_OPENGL);
	flags |= SDL_WINDOW_VULKAN;
	

	auto func = GetCreateWindowFunc();
	return func(newTitle, x, y, w, h, flags);
}

APICALL void SDL_SetWindowTitle(SDL_Window* window, const char* title)
{
	printf("TRACE: Intercepted call to SDL_SetWindowTitle: window=0x%p title=%s\n", window, title);
	char newTitle[512];
	snprintf(newTitle, sizeof(newTitle), "%s [On Vulkan via ToVK]", title);
	
	auto func = GetSetWindowTitleFunc();
	func(window, newTitle);
}

APICALL int SDL_GL_MakeCurrent(SDL_Window* window, SDL_GLContext context)
{
	printf("TRACE: STUB: Intercepted call to SDL_GL_MakeCurrent: window=0x%p context=0x%p\n", window, context);
	return 0;
}

APICALL SDL_GLContext SDL_GL_CreateContext(SDL_Window* window)
{
	printf("TRACE: STUB: Intercepted call to SDL_GL_CreateContext, returning dummy: window=0x%p\n", window);
	static int thisDoesNothing = 49;
	return &thisDoesNothing;
}

// Override this so we can return ptrs to OUR gl funcs :) 
APICALL void* SDL_GL_GetProcAddress(const char *proc)
{
	static void* pOurDll = dlopen("libtogl.so", RTLD_LAZY);
	printf("TRACE: SDL_GL_GetProcAddress called: proc=%s\n", proc);
	return dlsym(pOurDll, proc);
}

static void *LoadSDL2()
{
	if (!g_pSDLHandle)
	{
		/* first try the SDL2 in the bin directory */
		g_pSDLHandle = dlopen("libSDL2-2.0.so.0", RTLD_LAZY);

		if (g_pSDLHandle)
			return g_pSDLHandle;

		printf("Could not load libSDL2-2.0.so.0 from the game bin directory!\n");
		abort();

		// TODO: Maybe could load this from /lib32/ but I doubt that'd work
	}
	return g_pSDLHandle;
}

static pfnSDL_CreateWindow GetCreateWindowFunc()
{
	if (!g_pCreateWindow)
	{
		if (!g_pSDLHandle)
			LoadSDL2();

		g_pCreateWindow = (pfnSDL_CreateWindow)dlsym(g_pSDLHandle, "SDL_CreateWindow");

		if (!g_pCreateWindow)
		{
			printf("Could not find SDL_CreateWindow in SDL2 library.\n");
			abort();
		}
	}
	return g_pCreateWindow;
}

static pfnSDL_SetWindowTitle GetSetWindowTitleFunc()
{
	if(!g_pSetWindowTitle)
	{
		if(!g_pSDLHandle)
			LoadSDL2();
			
		g_pSetWindowTitle = (pfnSDL_SetWindowTitle)dlsym(g_pSDLHandle, "SDL_SetWindowTitle");
		if(!g_pSetWindowTitle)
		{
			printf("Could not find SDL_SetWindowTitle!\n");
			abort();
		}
	}
	return g_pSetWindowTitle;
}

struct StaticInitHelper 
{
	StaticInitHelper()
	{
		printf("SDL2 Proxy: Up and running\n\n\n\n");
	}
};
StaticInitHelper helper;