#ifndef _OBIGO_SURFACEMANAGER_H_
#define _OBIGO_SURFACEMANAGER_H_

#include <HSubSurface.h>
#include <WindowBase.h>
#include "subsurface/ExampleSubSurfaceListener.h"

class SubSurfaceManager {
 public:
    static SubSurfaceManager* getInstance();

    void create();
    void created(const uint32_t surface_id);
    void show(const ccos::window::HWindowId& a_winID);
    void raiseIssue(const ccos::window::HWindowId& a_winID);

 private:
    SubSurfaceManager();
    ~SubSurfaceManager();

    static SubSurfaceManager* m_pThis;

    std::shared_ptr<ccos::window::HSubSurface> mSubSurface1;
    std::shared_ptr<ccos::window::HSubSurface> mSubSurface2;

    ExampleSubSurfaceListener mSubSurfaceListener1;
    ExampleSubSurfaceListener mSubSurfaceListener2;

    bool isCreated;
    int subSurfaceCount;
    bool isShowed;
};

#endif  // _OBIGO_SURFACEMANAGER_H_
