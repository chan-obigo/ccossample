#ifndef _OBIGO_PROXY_H_
#define _OBIGO_PROXY_H_

#include <unistd.h>
#include <iostream>
#include <string>

#include <CommonAPI/CommonAPI.hpp>
#include <v1/commonapi/examples/ObigoTestProxy.hpp>

namespace v1 {
namespace commonapi {
namespace examples {

class ObigoProxy {
 public:
    static ObigoProxy* getInstance();

    void Connect();

    void testFunction_IPC(const std::string& a_in, std::string* const a_out);

 private:
    ObigoProxy();
    ~ObigoProxy();

    static ObigoProxy* m_pThis;

    std::shared_ptr<ObigoTestProxyDefault> m_proxy;
};

}  // namespace examples
}  // namespace commonapi
}  // namespace v1

#endif  // _OBIGO_PROXY_H_
