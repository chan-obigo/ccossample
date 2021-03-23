#include "obigo/SubSurfaceManager.h"

#include "obigo/ObigoTestController.h"
#include "obigo/ObigoStub.h"

#include <unistd.h>

SubSurfaceManager* SubSurfaceManager::m_pThis = nullptr;


SubSurfaceManager::SubSurfaceInfo::SubSurfaceInfo() {
    subsurface = nullptr;
    subsurfaceListener = nullptr;
    rect = nullptr;
    isShow = false;
}

SubSurfaceManager::SubSurfaceInfo::~SubSurfaceInfo() {
    if (subsurface) {
        delete subsurface;
        fprintf(stdout, "[ObigoParent]::%s::%d::%d <== subsurface is detroyed\n", __func__, __LINE__, rect->surface_id); fflush(stdout);
    }
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
    m_testController = new ObigoTestController(this);
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

    m_testController->run();
    return;

    v1::commonapi::examples::ObigoStub::getInstance()->fireCreateApplicationEvent(1);
}



void SubSurfaceManager::show(const ccos::window::HWindowId& a_winID) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%ld\n", __func__, __LINE__, m_subSurfaceList.size()); fflush(stdout);
    std::vector<ccos::window::HSubSurfaceHandle> zOrder;
    ccos::window::HSubSurfaceHandle activeHandle = 0;

    disconnect();   // our code, disconnect before connect
    for (auto item : m_subSurfaceList) {
        struct SubSurfaceManager::SubSurfaceInfo* surfaceInfo = item.second;
        if (surfaceInfo->isShow) {
            zOrder.push_back(surfaceInfo->subsurface->getHandle());
        }
    }
    ccos::window::HSubSurfaceController::getInstance()->connect(a_winID, zOrder);
}

void SubSurfaceManager::show() {
    show(m_winId);
}

void SubSurfaceManager::disconnect() {
    fprintf(stdout, "[ObigoParent]::%s::%d <== make disconnect\n", __func__, __LINE__); fflush(stdout);
    ccos::window::HSubSurfaceController::getInstance()->disconnect(m_winId);
}

bool SubSurfaceManager::release_resource(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);

    struct Rectangle* rect = getIndexedRectangle(index);
    reply_destroy_application(rect->surface_id);
    return true;
}


void SubSurfaceManager::raiseIssue(const ccos::window::HWindowId& a_winID) {

    m_testController->run();
    return;

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

void SubSurfaceManager::initializeRectangle() {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, MAX_SURFACE_COUNT); fflush(stdout);
#if 1
    for (int i=0; i<MAX_SURFACE_COUNT; i++) {
        m_rectResource[i].x = 280;
        m_rectResource[i].y = 120;
        m_rectResource[i].width = 1000;
        m_rectResource[i].height = 600;
        m_rectResource[i].used = false;
    }
#else    
    for (int i=0; i<MAX_SURFACE_COUNT; i++) {
        m_rectResource[i].x = 300 + 300*i;
        m_rectResource[i].y = 250;
        m_rectResource[i].width = 250;
        m_rectResource[i].height = 250;
        m_rectResource[i].used = false;
    }
#endif    
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

struct SubSurfaceManager::Rectangle* SubSurfaceManager::getIndexedRectangle(uint32_t index) const {
    return const_cast<struct SubSurfaceManager::Rectangle*>(&m_rectResource[index]);
}

void SubSurfaceManager::run() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    getController()->run();
}

bool SubSurfaceManager::create_application(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    set_creating_index(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireCreateApplicationEvent(index);
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    return true;
}

bool SubSurfaceManager::destroy_application(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireDestroyApplicationEvent(rect->surface_id);
    return true;
}

bool SubSurfaceManager::show_application(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireShowApplicationEvent(rect->surface_id);
    return true;
}

bool SubSurfaceManager::hide_application(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireHideApplicationEvent(rect->surface_id);
    return true;
}

bool SubSurfaceManager::destroy_ivi_surface(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireDestroyIviSurfaceEvent(rect->surface_id);
    return true;
}

bool SubSurfaceManager::destroy_wl_surface(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireDestroyWlSurfaceEvent(rect->surface_id);
    return true;
}

bool SubSurfaceManager::destroy_wl_egl_surface(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireDestroyWlEglSurfaceEvent(rect->surface_id);
    return true;
}

bool SubSurfaceManager::destroy_egl_surface(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireDestroyEglSurfaceEvent(rect->surface_id);
    return true;
}

bool SubSurfaceManager::make_current_surface(uint32_t index) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
    struct Rectangle* rect = getIndexedRectangle(index);
    v1::commonapi::examples::ObigoStub::getInstance()->fireMakeCurrentSurfaceEvent(rect->surface_id);
    return true;
}

void SubSurfaceManager::reply_create_application(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);

    struct SubSurfaceInfo* surfaceInfo = new struct SubSurfaceInfo;
    surfaceInfo->subsurface = new ccos::window::HSubSurface(surface_id);
    surfaceInfo->subsurfaceListener = new ExampleSubSurfaceListener;
    surfaceInfo->rect = getIndexedRectangle(get_creating_index());
    if (!surfaceInfo->rect || surfaceInfo->rect->used ) {
        fprintf(stdout, "[ObigoParent]::%s::%d::%d ==> not available resource\n", __func__, __LINE__, surface_id); fflush(stdout);
        delete surfaceInfo;
        run();
        return;
    }

    surfaceInfo->rect->used = true;
    surfaceInfo->rect->surface_id = surface_id;
    surfaceInfo->subsurface->setEventListener(surfaceInfo->subsurfaceListener);

    surfaceInfo->subsurface->setSourceRectangle({0, 0, surfaceInfo->rect->width, surfaceInfo->rect->height});
    surfaceInfo->subsurface->setDestRectangle({surfaceInfo->rect->x, surfaceInfo->rect->y,
         surfaceInfo->rect->width, surfaceInfo->rect->height});
#if 1 // SACH_SPECIFIC (make current test)
    if (surface_id == 10000) {
        surfaceInfo->isShow = true;
    }
#endif

    m_subSurfaceList[surface_id] = surfaceInfo;
    run();
}

void SubSurfaceManager::reply_destroy_application(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    delete m_subSurfaceList[surface_id];
    m_subSurfaceList.erase(surface_id);
    show(m_winId);
    run();
}

void SubSurfaceManager::reply_show_application(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    struct SubSurfaceInfo* surfaceInfo = m_subSurfaceList[surface_id];
    surfaceInfo->isShow = true;
    show(m_winId);
    run();
}

void SubSurfaceManager::reply_hide_application(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    struct SubSurfaceInfo* surfaceInfo = m_subSurfaceList[surface_id];
    surfaceInfo->isShow = false;
    show(m_winId);
    run();
}

void SubSurfaceManager::reply_destroy_ivi_surface(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    run();
}

void SubSurfaceManager::reply_destroy_wl_surface(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    run();
}

void SubSurfaceManager::reply_destroy_wl_egl_surface(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    run();
}

void SubSurfaceManager::reply_destroy_egl_surface(uint32_t surface_id) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, surface_id); fflush(stdout);
    run();
}

