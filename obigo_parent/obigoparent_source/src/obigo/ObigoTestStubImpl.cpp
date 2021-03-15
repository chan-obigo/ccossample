#include "obigo/ObigoTestStubImpl.h"

#include "LogContext.h"

namespace v1 {
namespace commonapi {
namespace examples {

ObigoTestStubImpl::ObigoTestStubImpl() {}

ObigoTestStubImpl::~ObigoTestStubImpl() {}

void ObigoTestStubImpl::testFunction(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, testFunctionReply_t _reply) {
    (void)_client;
    HInfo() << "ObigoTestStubImpl:: ++++++++++++++++++ " << __func__ << "::" << __LINE__;
    HInfo() << "ObigoTestStubImpl:: ++++++++++++++++++ " << _name;
    std::string message = "return";
    _reply(message);
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
