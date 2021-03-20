#ifndef _OBIGO_TESTSTUBIMPL_H_
#define _OBIGO_TESTSTUBIMPL_H_

#include <v1/commonapi/examples/ObigoTestStubDefault.hpp>

namespace v1 {
namespace commonapi {
namespace examples {

class ObigoTestStubImpl : public ObigoTestStubDefault {
 public:
    ObigoTestStubImpl();
    ~ObigoTestStubImpl();

    void CreatedApplication(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, CreatedApplicationReply_t _reply) override;
    void DestroyedApplication(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, DestroyedApplicationReply_t _reply) override;

    void ShownApplication(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, ShownApplicationReply_t _reply) override;
    void HiddenApplication(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, HiddenApplicationReply_t _reply) override;

    void DestroyedIviSurface(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, DestroyedIviSurfaceReply_t _reply) override;
    void DestroyedWlSurface(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, DestroyedWlSurfaceReply_t _reply) override;
    void DestroyedWlEglSurface(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, DestroyedWlEglSurfaceReply_t _reply) override;
    void DestroyedEglSurface(const std::shared_ptr<CommonAPI::ClientId> _client, uint32_t _surface_id, DestroyedEglSurfaceReply_t _reply) override;
};

}  // namespace examples
}  // namespace commonapi
}  // namespace v1

#endif  // _OBIGO_TESTSTUBIMPL_H_
