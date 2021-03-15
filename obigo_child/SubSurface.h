#ifndef _OBIGO_SUBSURFACE_H_
#define _OBIGO_SUBSURFACE_H_

#include <wayland-client-protocol.h>
#include <ilm/ivi-application-client-protocol.h>

class SubSurface {
 public:
    SubSurface();
    ~SubSurface();

    void CreateSurface(int32_t surfaceid);

 private:
    struct wl_surface* m_wlsurface;
    struct ivi_surface* m_ivisurface;
};

#endif  // _OBIGO_SUBSURFACE_H_
