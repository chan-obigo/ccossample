#ifndef _OBIGO_SUBSURFACE_H_
#define _OBIGO_SUBSURFACE_H_

#include <wayland-client-protocol.h>
#include <ilm/ivi-application-client-protocol.h>

class EGLClient;

class SubSurface {
 public:
    SubSurface();
    ~SubSurface();

    void CreateSurface(int32_t surfaceid);
    void redraw();
    void destroy();

 private:
    struct wl_surface* m_wlsurface;
    struct ivi_surface* m_ivisurface;
    EGLClient* m_eglCleint;
    void *shm_data;
};

#endif  // _OBIGO_SUBSURFACE_H_
