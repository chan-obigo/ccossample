#ifndef _OBIGO_STUB_H_
#define _OBIGO_STUB_H_

#include <iostream>

#include <CommonAPI/CommonAPI.hpp>
#include "obigo/ObigoTestStubImpl.h"

namespace v1 {
namespace commonapi {
namespace examples {

class ObigoStub {
 public:
    static ObigoStub* getInstance();

    void Connect();
    void fireCreateApplicationEvent();
    void fireDestroyApplicationEvent(uint32_t surface_id);
    void fireDestroyIviSurfaceEvent(uint32_t surface_id);
    void fireDestroyWlSurfaceEvent(uint32_t surface_id);
    void fireDestroyWlEglSurfaceEvent(uint32_t surface_id);
    void fireDestroyEglSurfaceEvent(uint32_t surface_id);
    void fireMakeCurrentNoSurfaceEvent(uint32_t surface_id);

 private:
    ObigoStub();
    ~ObigoStub();

    static ObigoStub* m_pThis;

    std::shared_ptr<ObigoTestStubImpl> m_service;
};

}  // namespace examples
}  // namespace commonapi
}  // namespace v1

#endif  // _OBIGO_STUB_H_
