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

    std::string in_param("in param");
    std::string out_param;
    testFunction_IPC(in_param, &out_param);
}

void ObigoProxy::testFunction_IPC(const std::string& a_in, std::string* const a_out) {
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    m_proxy->testFunction(a_in, callStatus, returnMessage);
    *a_out = returnMessage;
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
