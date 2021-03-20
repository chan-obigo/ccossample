#include "ObigoProxy.h"

extern void CreateApplication(const int32_t& index);
extern void DestroyApplication(const int32_t& surface_id);
extern void ShowApplication(const int32_t& surface_id);
extern void HideApplication(const int32_t& surface_id);
extern void DestroyIviSurface(const int32_t& surface_id);
extern void DestroyWlSurface(const int32_t& surface_id);
extern void DestroyWlEglSurface(const int32_t& surface_id);
extern void DestroyEglSurface(const int32_t& surface_id);

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
    m_proxy->getShowApplicationEvent().subscribe(ShowApplication);
    m_proxy->getHideApplicationEvent().subscribe(HideApplication);
    m_proxy->getDestroyIviSurfaceEvent().subscribe(DestroyIviSurface);
    m_proxy->getDestroyWlSurfaceEvent().subscribe(DestroyWlSurface);
    m_proxy->getDestroyWlEglSurfaceEvent().subscribe(DestroyWlEglSurface);
    m_proxy->getDestroyEglSurfaceEvent().subscribe(DestroyEglSurface);
}

void ObigoProxy::CreatedApplication(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->CreatedApplication(a_in, callStatus);
}

void ObigoProxy::DestroyedApplication(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->DestroyedApplication(a_in, callStatus);
}

void ObigoProxy::ShownApplication(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->ShownApplication(a_in, callStatus);
}

void ObigoProxy::HiddenApplication(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->HiddenApplication(a_in, callStatus);
}

void ObigoProxy::DestroyedIviSurface(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->DestroyedIviSurface(a_in, callStatus);
}

void ObigoProxy::DestroyedWlSurface(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->DestroyedWlSurface(a_in, callStatus);
}

void ObigoProxy::DestroyedWlEglSurface(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->DestroyedWlEglSurface(a_in, callStatus);
}

void ObigoProxy::DestroyedEglSurface(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->DestroyedEglSurface(a_in, callStatus);
}


}  // namespace examples
}  // namespace commonapi
}  // namespace v1
