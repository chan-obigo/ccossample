#ifndef _OBIGO_SURFACEMANAGER_H_
#define _OBIGO_SURFACEMANAGER_H_

#include <map>

#include <HSubSurface.h>
#include <WindowBase.h>
#include "subsurface/ExampleSubSurfaceListener.h"

#define MAX_SURFACE_COUNT           4

class SubSurfaceManager {
 public:
    static SubSurfaceManager* getInstance();

    struct Rectangle {
        uint32_t x;
        uint32_t y;
        uint32_t width;
        uint32_t height;
        bool used;
    };

    struct SubSurfaceInfo {
        std::shared_ptr<ccos::window::HSubSurface> subsurface;
        ExampleSubSurfaceListener *subsurfaceListener;
        struct Rectangle* rect;
        bool isShow;

        SubSurfaceInfo();
        ~SubSurfaceInfo();
    };

    void initializeRectangle();
    struct Rectangle* getEmptyRectangle() const;
    void makeEmptyRectangle(struct Rectangle* rect) { rect->used = false; }

    void created(const uint32_t surface_id);    // registered
    void destroyed(const uint32_t surface_id);    // unregistered
    void showed(const uint32_t surface_id);    // connect
    void hided(const uint32_t surface_id);    // disconnect

    void create();
    void show(const ccos::window::HWindowId& a_winID);
    void raiseIssue(const ccos::window::HWindowId& a_winID);
    void setWinID(ccos::window::HWindowId id);

 private:
    SubSurfaceManager();
    ~SubSurfaceManager();

    static SubSurfaceManager* m_pThis;

    std::map<uint32_t, struct SubSurfaceInfo*> m_subSurfaceList;

    uint32_t m_activeSurface;
    struct Rectangle m_rectResource[MAX_SURFACE_COUNT];
    ccos::window::HWindowId m_winId;
};

#endif  // _OBIGO_SURFACEMANAGER_H_
