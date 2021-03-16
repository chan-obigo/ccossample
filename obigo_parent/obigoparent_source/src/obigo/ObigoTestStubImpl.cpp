#include "obigo/ObigoTestStubImpl.h"
#include "obigo/SubSurfaceManager.h"

namespace v1 {
namespace commonapi {
namespace examples {

ObigoTestStubImpl::ObigoTestStubImpl() {}

ObigoTestStubImpl::~ObigoTestStubImpl() {}

void ObigoTestStubImpl::CreateHSubSurface(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, CreateHSubSurfaceReply_t _reply) {
    (void)_client;
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, _surface_id); fflush(stdout);
    SubSurfaceManager::getInstance()->created(_surface_id);
    _reply();
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
