#include "obigo/ObigoTestStubImpl.h"

#include "LogContext.h"

namespace v1 {
namespace commonapi {
namespace examples {

ObigoTestStubImpl::ObigoTestStubImpl() {}

ObigoTestStubImpl::~ObigoTestStubImpl() {}

void ObigoTestStubImpl::testFunction(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, testFunctionReply_t _reply) {
    (void)_client;
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    fprintf(stdout, "[ObigoParent]::%s::%d::%s\n", __func__, __LINE__, _name.c_str()); fflush(stdout);
    std::string message = "return";
    _reply(message);
}

}  // namespace examples
}  // namespace commonapi
}  // namespace v1
