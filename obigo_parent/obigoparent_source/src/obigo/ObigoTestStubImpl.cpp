#include "obigo/ObigoTestStubImpl.h"
#include "obigo/SubSurfaceManager.h"

namespace v1 {
namespace commonapi {
namespace examples {

ObigoTestStubImpl::ObigoTestStubImpl() {}

ObigoTestStubImpl::~ObigoTestStubImpl() {}

void ObigoTestStubImpl::CreatedApplication(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, CreatedApplicationReply_t _reply) {
    (void)_client;
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, _surface_id); fflush(stdout);
    SubSurfaceManager::getInstance()->reply_create_application(_surface_id);
    _reply();
}

void ObigoTestStubImpl::DestroyedApplication(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, DestroyedApplicationReply_t _reply) {
    (void)_client;
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, _surface_id); fflush(stdout);
    SubSurfaceManager::getInstance()->reply_destroy_application(_surface_id);
    _reply();
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
