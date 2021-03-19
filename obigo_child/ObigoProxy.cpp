#include "ObigoProxy.h"

extern void CreateApplication(const int32_t& index);
extern void DestroyApplication(const int32_t& surface_id);


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

    fprintf(stdout, "[ObigoChild]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    while (!m_proxy->isAvailable()) {
        usleep(10);
    }

    m_proxy->getCreateApplicationEvent().subscribe(CreateApplication);
    m_proxy->getDestroyApplicationEvent().subscribe(DestroyApplication);

    fprintf(stdout, "[ObigoChild]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    // Followings lambda functions are not run on main thread
    m_proxy->getDestroyIviSurfaceEvent().subscribe([&](const int32_t& surface_id) {
        // DOTO () - Please Destroy surface_id's ivi surface
        fprintf(stdout, "[ObigoChild]::DestroyIviSurfaceEvent::%d::%d\n",  __LINE__, surface_id); fflush(stdout);
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
}

void ObigoProxy::CreatedApplication(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->CreatedApplication(a_in, callStatus);
}

void ObigoProxy::DestroyedApplication(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->DestroyedApplication(a_in, callStatus);
}


}  // namespace examples
}  // namespace commonapi
}  // namespace v1
