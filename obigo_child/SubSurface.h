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
    void Draw();
    int GetSurfaceId() { return m_surfaceId; }
    bool Shown() { return m_wasShown; }
    bool setShown(bool shown) { m_wasShown = shown; }

 private:
    struct wl_surface* m_wlsurface;
    struct ivi_surface* m_ivisurface;
    EGLClient* m_eglCleint;
    int m_surfaceId;
    bool m_wasShown;
};

#endif  // _OBIGO_SUBSURFACE_H_
