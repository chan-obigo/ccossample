#include "ObigoProxy.h"

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

    m_proxy->getDestroyChildEvent().subscribe([&](const int32_t& surface_id) {
        fprintf(stdout, "[ObigoChild]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    });
}

void ObigoProxy::CreateHSubSurface(const uint32_t& a_in) {
    CommonAPI::CallStatus callStatus;
    m_proxy->CreateHSubSurface(a_in, callStatus);
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
