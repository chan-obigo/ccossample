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
    mSubSurface1->setEventListener(&mSubSurfaceListener1);

    isCreated = true;
}

void SubSurfaceManager::show(const ccos::window::HWindowId& a_winID) {
    std::vector<ccos::window::HSubSurfaceHandle> zOrder{ mSubSurface1->getHandle()};

    ccos::window::HSubSurfaceController::getInstance()->connect(a_winID, zOrder);

    mSubSurface1->setSourceRectangle({0, 0, 250, 250});
    mSubSurface1->setDestRectangle({500, 250, 250, 250});
}

void SubSurfaceManager::hide(const ccos::window::HWindowId& a_winID) {
    ccos::window::HSubSurfaceController::getInstance()->disconnect(a_winID);
}
