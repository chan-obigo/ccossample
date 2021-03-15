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

    void testFunction(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, testFunctionReply_t _reply) override;
};

}  // namespace examples
}  // namespace commonapi
}  // namespace v1

#endif  // _OBIGO_TESTSTUBIMPL_H_
