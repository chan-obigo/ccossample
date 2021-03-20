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
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.ObigoTest";
    std::string connection = "service-sample";

    m_service = std::make_shared<ObigoTestStubImpl>();
    runtime->registerService(domain, instance, m_service, connection);
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
}

void ObigoStub::fireCreateApplicationEvent(uint32_t index) {
    m_service->fireCreateApplicationEvent(index);
}

void ObigoStub::fireDestroyApplicationEvent(uint32_t surface_id) {
    m_service->fireDestroyApplicationEvent(surface_id);
}

void ObigoStub::fireShowApplicationEvent(uint32_t surface_id) {
    m_service->fireShowApplicationEvent(surface_id);
}

void ObigoStub::fireHideApplicationEvent(uint32_t surface_id) {
    m_service->fireHideApplicationEvent(surface_id);
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

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
