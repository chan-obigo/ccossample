#include "obigo/ObigoStub.h"

namespace v1 {
namespace commonapi {
namespace examples {

ObigoStub* ObigoStub::m_pThis = nullptr;

ObigoStub::ObigoStub() {}

ObigoStub::~ObigoStub() {}

ObigoStub* ObigoStub::getInstance() {
    if (nullptr == m_pThis) {
        m_pThis = new ObigoStub();
    }
    return m_pThis;
}

void ObigoStub::Connect() {
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.ObigoTest";
    std::string connection = "service-sample";

    m_service = std::make_shared<ObigoTestStubImpl>();
    runtime->registerService(domain, instance, m_service, connection);
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
