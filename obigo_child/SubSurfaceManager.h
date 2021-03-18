#ifndef _OBIGO_SUBSURFACEMANAGER_H_
#define _OBIGO_SUBSURFACEMANAGER_H_

#include <map>

#include "SubSurface.h"

class SubSurfaceManager {
 public:
    SubSurfaceManager();
    ~SubSurfaceManager();

    void Initiailze();
    void CreateSubSurface();
    void DestroySubSurface(int surface_id);
    void Draw();
    int GetEmptySurfaceId() { return m_currentSurfaceIndex++; }
    SubSurface* GetActiveSurface() { return m_activeSurface; }
    SubSurface* GetLatestCreatedSurface();

 private:
    std::map<int, SubSurface*> m_subSurfaces;
    static constexpr int m_startSurfaceIndex = 10000;
    int m_currentSurfaceIndex;
    SubSurface* m_activeSurface;
    SubSurface* m_createdSurface;
};

#endif  // _OBIGO_SUBSURFACEMANAGER_H_
