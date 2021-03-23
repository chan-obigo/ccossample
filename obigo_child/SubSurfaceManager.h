#ifndef _OBIGO_SUBSURFACEMANAGER_H_
#define _OBIGO_SUBSURFACEMANAGER_H_

#include <map>

#include "SubSurface.h"

class SubSurfaceManager {
 public:
    SubSurfaceManager();
    ~SubSurfaceManager();

    void Initiailze();
    void Draw();
    int GetEmptySurfaceId() { return m_currentSurfaceIndex++; }
    SubSurface* GetActiveSurface() { return m_activeSurface; }
    SubSurface* GetLatestCreatedSurface();

    // interface api
    void CreateSurface(int index);
    void DestroySurface(int surface_id);
    void ShowSurface(int surface_id);
    void HideSurface(int surface_id);
    void DestroyIviSurface(int surface_id);
    void DestroyWlSurface(int surface_id);
    void DestroyWlEglSurface(int surface_id);
    void DestroyEglSurface(int surface_id);
    void MakeCurrentSurface(int surface_id);

 private:
    std::map<int, SubSurface*> m_subSurfaces;
    static constexpr int m_startSurfaceIndex = 10000;
    int m_currentSurfaceIndex;
    SubSurface* m_activeSurface;
    SubSurface* m_createdSurface;
};

#endif  // _OBIGO_SUBSURFACEMANAGER_H_
