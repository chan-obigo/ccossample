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

    void CreatedApplication(const uint32_t& a_in);
    void DestroyedApplication(const uint32_t& a_in);

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
