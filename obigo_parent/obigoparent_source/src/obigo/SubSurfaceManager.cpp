#include "obigo/SubSurfaceManager.h"
#include "obigo/ObigoStub.h"

#include <unistd.h>

SubSurfaceManager* SubSurfaceManager::m_pThis = nullptr;

SubSurfaceManager::SubSurfaceManager() {
    isCreated = false;
    subSurfaceCount = 0;
    isShowed = false;
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

    int pid = -1;

    pid = fork();
    if (pid < 0) {
        fprintf(stdout, "[ObigoParent]::%s::%d::Fork Error\n", __func__, __LINE__); fflush(stdout);
        exit(0);
    } else if (pid == 0) {  // child
        execl("/ccos/apps/hmi/obigo_child/obigo_child", "/ccos/apps/hmi/obigo_child/obigo_child", "1", nullptr);
    } else {
        // parent noting to do
    }

    pid = fork();
    if (pid < 0) {
        fprintf(stdout, "[ObigoParent]::%s::%d::Fork Error\n", __func__, __LINE__); fflush(stdout);
        exit(0);
    } else if (pid == 0) {  // child
        execl("/ccos/apps/hmi/obigo_child/obigo_child", "/ccos/apps/hmi/obigo_child/obigo_child", "2", nullptr);
    } else {
        // parent noting to do
    }

    isCreated = true;
}

void SubSurfaceManager::created(const uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    subSurfaceCount++;
    if (surface_id == 1) {
        mSubSurface1 = std::make_shared<ccos::window::HSubSurface>(surface_id);
        mSubSurface1->setEventListener(&mSubSurfaceListener1);
    }
    if (surface_id == 2) {
        mSubSurface2 = std::make_shared<ccos::window::HSubSurface>(surface_id);
        mSubSurface2->setEventListener(&mSubSurfaceListener2);
    }
}

void SubSurfaceManager::show(const ccos::window::HWindowId& a_winID) {
    if (subSurfaceCount != 2) {
        fprintf(stdout, "[ObigoParent]::%s::%d::subsurface is not created, try again\n", __func__, __LINE__); fflush(stdout);
        return;
    }
    std::vector<ccos::window::HSubSurfaceHandle> zOrder{ mSubSurface1->getHandle(),
                                                         mSubSurface2->getHandle()};

    ccos::window::HSubSurfaceController::getInstance()->connect(a_winID, zOrder);

    mSubSurface1->setSourceRectangle({0, 0, 250, 250});
    mSubSurface1->setDestRectangle({500, 250, 250, 250});

    mSubSurface2->setSourceRectangle({0, 0, 250, 250});
    mSubSurface2->setDestRectangle({800, 250, 250, 250});
    isShowed = true;
}

void SubSurfaceManager::raiseIssue(const ccos::window::HWindowId& a_winID) {
    if (isShowed = false) {
        fprintf(stdout, "[ObigoParent]::%s::%d::subsurface is not shown, try again\n", __func__, __LINE__); fflush(stdout);
        return;
    }

    // disconnect HSubsurface 2
    std::vector<ccos::window::HSubSurfaceHandle> zOrder{ mSubSurface1->getHandle()};
    ccos::window::HSubSurfaceController::getInstance()->connect(a_winID, zOrder);

    // destroy HSubsurface 2
    mSubSurface2.reset();

    // destroy HSubsurface 2's process
    v1::commonapi::examples::ObigoStub::getInstance()->fireDestroyChildEvent(2);
}
