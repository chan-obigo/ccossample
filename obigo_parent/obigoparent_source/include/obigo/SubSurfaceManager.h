#ifndef _OBIGO_SURFACEMANAGER_H_
#define _OBIGO_SURFACEMANAGER_H_

#include <HSubSurface.h>
#include <WindowBase.h>
#include "subsurface/ExampleSubSurfaceListener.h"

class SubSurfaceManager {
 public:
    static SubSurfaceManager* getInstance();

    void create();
    void show(const ccos::window::HWindowId& a_winID);
    void hide(const ccos::window::HWindowId& a_winID);

 private:
    SubSurfaceManager();
    ~SubSurfaceManager();

    static SubSurfaceManager* m_pThis;

    std::shared_ptr<ccos::window::HSubSurface> mSubSurface1;
    std::shared_ptr<ccos::window::HSubSurface> mSubSurface2;
    std::shared_ptr<ccos::window::HSubSurface> mSubSurface3;
    std::shared_ptr<ccos::window::HSubSurface> mSubSurface4;

    ExampleSubSurfaceListener mSubSurfaceListener1;
    ExampleSubSurfaceListener mSubSurfaceListener2;
    ExampleSubSurfaceListener mSubSurfaceListener3;
    ExampleSubSurfaceListener mSubSurfaceListener4;

    bool isCreated;
};

#endif  // _OBIGO_SURFACEMANAGER_H_
