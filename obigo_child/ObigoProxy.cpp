#include "ObigoProxy.h"

extern bool g_is_destroy;
extern int g_surface_id;

namespace v1 {
namespace commonapi {
namespace examples {

ObigoProxy* ObigoProxy::m_pThis = nullptr;

ObigoProxy::ObigoProxy() {}

ObigoProxy::~ObigoProxy() {}

ObigoProxy* ObigoProxy::getInstance() {
    if (nullptr == m_pThis) {
        m_pThis = new ObigoProxy();
    }
    return m_pThis;
}

void ObigoProxy::Connect() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.ObigoTest";
    std::string connection = "client-sample";

    m_proxy = runtime->buildProxy<ObigoTestProxy>(domain, instance, connection);

    while (!m_proxy->isAvailable()) {
        usleep(10);
    }

    // Followings lambda functions are not run on main thread
    m_proxy->getDestroyIviSurfaceEvent().subscribe([&](const int32_t& surface_id) {
        // DOTO () - Please Destroy surface_id's ivi surface
        fprintf(stdout, "[ObigoChild]::DestroyIviSurfaceEvent::%d::%d\n", __LINE__, surface_id); fflush(stdout);
        if (g_surface_id == surface_id) {
            g_is_destroy = true;
        }
    });

    m_proxy->getDestroyWlSurfaceEvent().subscribe([&](const int32_t& surface_id) {
        // DOTO () - Please Destroy surface_id's wl surface
        fprintf(stdout, "[ObigoChild]::DestroyWlSurfaceEvent::%d::%d\n", __LINE__, surface_id); fflush(stdout);
    });

    m_proxy->getDestroyWlEglSurfaceEvent().subscribe([&](const int32_t& surface_id) {
        // DOTO () - Please Destroy surface_id's wl egl surface
        fprintf(stdout, "[ObigoChild]::DestroyWlEglSurfaceEvent::%d::%d\n", __LINE__, surface_id); fflush(stdout);
    });

    m_proxy->getDestroyEglSurfaceEvent().subscribe([&](const int32_t& surface_id) {
        // DOTO () - Please Destroy surface_id's egl surface
        fprintf(stdout, "[ObigoChild]::DestroyEglSurfaceEvent::%d::%d\n", __LINE__, surface_id); fflush(stdout);
    });

    m_proxy->getMakeCurrentNoSurfaceEvent().subscribe([&](const int32_t& surface_id) {
        // DOTO () - Turn off MakeCurrent for surface_id
        // The other surface must be in makecurrent state.
        fprintf(stdout, "[ObigoChild]::MakeCurrentNoSurfaceEvent::%d::%d\n", __LINE__, surface_id); fflush(stdout);
    });
}

void ObigoProxy::CreateHSubSurface(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->CreateHSubSurface(a_in, callStatus);
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
