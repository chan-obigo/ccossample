#include "obigo/SubSurfaceManager.h"

SubSurfaceManager* SubSurfaceManager::m_pThis = nullptr;

SubSurfaceManager::SubSurfaceManager() {
    isCreated = false;
}

SubSurfaceManager::~SubSurfaceManager() {}

SubSurfaceManager* SubSurfaceManager::getInstance() {
    if (nullptr == m_pThis) {
        m_pThis = new SubSurfaceManager();
    }
    return m_pThis;
}

void SubSurfaceManager::create() {
    if (isCreated) {
        return;
    }
    mSubSurface1 = std::make_shared<ccos::window::HSubSurface>(27777);
    mSubSurface2 = std::make_shared<ccos::window::HSubSurface>(27778);
    mSubSurface3 = std::make_shared<ccos::window::HSubSurface>(27779);
    mSubSurface4 = std::make_shared<ccos::window::HSubSurface>(27780);

    mSubSurface1->setEventListener(&mSubSurfaceListener1);
    mSubSurface2->setEventListener(&mSubSurfaceListener2);
    mSubSurface3->setEventListener(&mSubSurfaceListener3);
    mSubSurface4->setEventListener(&mSubSurfaceListener4);

    isCreated = true;
}

void SubSurfaceManager::show(const ccos::window::HWindowId& a_winID) {
    std::vector<ccos::window::HSubSurfaceHandle> zOrder{ mSubSurface1->getHandle(),
                                                         mSubSurface2->getHandle(),
                                                         mSubSurface3->getHandle(),
                                                         mSubSurface4->getHandle() };

    ccos::window::HSubSurfaceController::getInstance()->connect(a_winID, zOrder);

    mSubSurface1->setSourceRectangle({0, 0, 250, 250});
    mSubSurface1->setDestRectangle({500, 250, 250, 250});

    mSubSurface2->setSourceRectangle({0, 0, 250, 250});
    mSubSurface2->setDestRectangle({800, 250, 250, 250});

    mSubSurface3->setSourceRectangle({0, 0, 250, 250});
    mSubSurface3->setDestRectangle({1100, 250, 250, 250});

    mSubSurface4->setSourceRectangle({0, 0, 250, 250});
    mSubSurface4->setDestRectangle({1400, 250, 250, 250});
}

void SubSurfaceManager::hide(const ccos::window::HWindowId& a_winID) {
    ccos::window::HSubSurfaceController::getInstance()->disconnect(a_winID);
}
