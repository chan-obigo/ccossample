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

void ObigoStub::fireDestroyIviSurfaceEvent(uint32_t surface_id) {
    m_service->fireDestroyIviSurfaceEvent(surface_id);
}

void ObigoStub::fireDestroyWlSurfaceEvent(uint32_t surface_id) {
    m_service->fireDestroyWlSurfaceEvent(surface_id);
}

void ObigoStub::fireDestroyWlEglSurfaceEvent(uint32_t surface_id) {
    m_service->fireDestroyWlEglSurfaceEvent(surface_id);
}

void ObigoStub::fireDestroyEglSurfaceEvent(uint32_t surface_id) {
    m_service->fireDestroyEglSurfaceEvent(surface_id);
}

void ObigoStub::fireMakeCurrentNoSurfaceEvent(uint32_t surface_id) {
    m_service->fireMakeCurrentNoSurfaceEvent(surface_id);
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
