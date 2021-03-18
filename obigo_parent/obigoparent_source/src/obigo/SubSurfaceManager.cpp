#include "obigo/SubSurfaceManager.h"
#include "obigo/ObigoStub.h"

#include <unistd.h>

SubSurfaceManager* SubSurfaceManager::m_pThis = nullptr;


SubSurfaceManager::SubSurfaceInfo::SubSurfaceInfo() {
    subsurfaceListener = nullptr;
    rect = nullptr;
    isShow = false;
}

SubSurfaceManager::SubSurfaceInfo::~SubSurfaceInfo() {
    if (rect) {
        rect->used = false;
    }
    if (subsurfaceListener) {
        delete subsurfaceListener;
    }
}

SubSurfaceManager::SubSurfaceManager() {
    m_activeSurface = 0;
    initializeRectangle();
}

SubSurfaceManager::~SubSurfaceManager() {}

SubSurfaceManager* SubSurfaceManager::getInstance() {
    if (nullptr == m_pThis) {
        m_pThis = new SubSurfaceManager();
    }
    return m_pThis;
}

void SubSurfaceManager::setWinID(ccos::window::HWindowId id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, id); fflush(stdout);
    m_winId = id;
}

void SubSurfaceManager::create() {
    v1::commonapi::examples::ObigoStub::getInstance()->fireCreateApplicationEvent();
}

void SubSurfaceManager::show(const ccos::window::HWindowId& a_winID) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%ld\n", __func__, __LINE__, m_subSurfaceList.size()); fflush(stdout);
    std::vector<ccos::window::HSubSurfaceHandle> zOrder;
    ccos::window::HSubSurfaceHandle activeHandle = 0;

    for (auto item : m_subSurfaceList) {
        struct SubSurfaceManager::SubSurfaceInfo* surfaceInfo = item.second;
        if (surfaceInfo->isShow) {
            zOrder.push_back(surfaceInfo->subsurface->getHandle());
        }
    }
    ccos::window::HSubSurfaceController::getInstance()->connect(a_winID, zOrder);
}

void SubSurfaceManager::raiseIssue(const ccos::window::HWindowId& a_winID) {
    uint32_t surface_id;
    std::map<uint32_t, struct SubSurfaceInfo*>::iterator it = m_subSurfaceList.begin();
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, 0); fflush(stdout);
    if (it == m_subSurfaceList.end()) {
        fprintf(stdout, "[ObigoParent]::%s::%d::%d <== No item in list\n", __func__, __LINE__, 0); fflush(stdout);
        return;
    }
    surface_id = it->first;
    delete it->second;
    v1::commonapi::examples::ObigoStub::getInstance()->fireDestroyApplicationEvent(surface_id);
    fprintf(stdout, "[ObigoParent]::%s::%d::%d <== will be destroyed\n", __func__, __LINE__, surface_id); fflush(stdout);
    m_subSurfaceList.erase(it);

#if 1
    show(m_winId);
#else    
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    it = m_subSurfaceList.begin();
    if (it != m_subSurfaceList.end()) {
        struct SubSurfaceManager::SubSurfaceInfo* surfaceInfo = it->second;
        surfaceInfo->isShow = true;
        show(m_winId);
        fprintf(stdout, "[ObigoParent]::%s::%d::%d <== will be shown\n", __func__, __LINE__, it->first); fflush(stdout);
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    }
    else {
        fprintf(stdout, "[ObigoParent]::%s::%d::%d <== No item to be shown\n", __func__, __LINE__, 0); fflush(stdout);
    }
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
#endif
}

void SubSurfaceManager::created(const uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);

    struct SubSurfaceInfo* surfaceInfo = new struct SubSurfaceInfo;
    surfaceInfo->subsurface = std::make_shared<ccos::window::HSubSurface>(surface_id);
    surfaceInfo->subsurfaceListener = new ExampleSubSurfaceListener;
    surfaceInfo->rect = getEmptyRectangle();
    if (!surfaceInfo->rect) {
        fprintf(stdout, "[ObigoParent]::%s::%d::%d ==> not available resource\n", __func__, __LINE__, surface_id); fflush(stdout);
        delete surfaceInfo;
        return;
    }
    surfaceInfo->rect->used = true;
    surfaceInfo->subsurface->setEventListener(surfaceInfo->subsurfaceListener);

    surfaceInfo->subsurface->setSourceRectangle({0, 0, surfaceInfo->rect->width, surfaceInfo->rect->height});
    surfaceInfo->subsurface->setDestRectangle({surfaceInfo->rect->x, surfaceInfo->rect->y,
         surfaceInfo->rect->width, surfaceInfo->rect->height});

    m_subSurfaceList[surface_id] = surfaceInfo;

    if (!m_activeSurface) {
       surfaceInfo->isShow = true;
       show(m_winId);
    }
}

void SubSurfaceManager::initializeRectangle() {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, MAX_SURFACE_COUNT); fflush(stdout);
    for (int i=0; i<MAX_SURFACE_COUNT; i++) {
        m_rectResource[i].x = 300 + 300*i;
        m_rectResource[i].y = 250;
        m_rectResource[i].width = 250;
        m_rectResource[i].height = 250;
        m_rectResource[i].used = false;
    }
}

struct SubSurfaceManager::Rectangle* SubSurfaceManager::getEmptyRectangle() const {
    for (int i=0; i<MAX_SURFACE_COUNT; i++) {
        if (!m_rectResource[i].used) {
            fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, i); fflush(stdout);
            return const_cast<struct SubSurfaceManager::Rectangle*>(&m_rectResource[i]);
        }
    }
    return nullptr;
}

