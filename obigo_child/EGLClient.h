#ifndef _OBIGO_EGLCLIENT_H_
#define _OBIGO_EGLCLIENT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include <signal.h>

#include <wayland-client.h>
#include <wayland-egl.h>
#include <wayland-cursor.h>

#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <EGL/eglext.h>

#include <sys/types.h>
#include <unistd.h>


#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(a) (sizeof (a) / sizeof (a)[0])
#endif

struct display {
	struct wl_display *display;
	struct wl_registry *registry;
	struct wl_compositor *compositor;
	struct xdg_wm_base *wm_base;
	struct wl_seat *seat;
	struct wl_pointer *pointer;
	struct wl_touch *touch;
	struct wl_keyboard *keyboard;
	struct wl_shm *shm;
	struct wl_cursor_theme *cursor_theme;
	struct wl_cursor *default_cursor;
	struct wl_surface *cursor_surface;
	struct {
		EGLDisplay dpy;
		EGLContext ctx;
		EGLConfig conf;
	} egl;
	struct window *window;

	PFNEGLSWAPBUFFERSWITHDAMAGEEXTPROC swap_buffers_with_damage;
};

struct geometry {
	int width, height;
};

struct window {
	struct display *display;
	struct geometry geometry, window_size;
	struct {
		GLuint rotation_uniform;
		GLuint pos;
		GLuint col;
	} gl;

	uint32_t benchmark_time, frames;
	struct wl_egl_window *native;
	struct wl_surface *surface;
	struct xdg_surface *xdg_surface;
	struct xdg_toplevel *xdg_toplevel;
	EGLSurface egl_surface;
	struct wl_callback *callback;
	int fullscreen, maximized, opaque, buffer_size, frame_sync, delay;
	bool wait_for_configure;
};

class EGLClient {
 public:

 	// weston & simple-egl api
 	bool weston_check_egl_extension(const char *extensions, const char *extension);
    EGLDisplay weston_platform_get_egl_display(EGLenum platform, void *native_display,
 				const EGLint *attrib_list);
    EGLBoolean weston_platform_destroy_egl_surface(EGLDisplay display,
				    EGLSurface surface);
    void *weston_platform_get_egl_proc_address(const char *address);

    void init_egl(struct display *display, struct window *window);
    
	void init_gl(struct window *window);
    GLuint create_shader(struct window *window, const char *source, GLenum shader_type);
	void create_surface(struct window *window);
	void destroy_surface(struct window *window);
    void redraw(uint32_t time);
    void destroy();


    void initialize();
    wl_surface* get_wayland_surface() { return m_window.surface; }

    EGLClient();
    EGLClient(int width, int height);
    virtual ~EGLClient() {}

 private:

 	struct display m_display;
 	struct window m_window;
};




#endif