#ifndef _OBIGO_SUBSURFACEMANAGER_H_
#define _OBIGO_SUBSURFACEMANAGER_H_

#include <vector>

#include "SubSurface.h"

class SubSurfaceManager {
 public:
    SubSurfaceManager();
    ~SubSurfaceManager();

    void Initiailze();
    void CreateSubSurface(int32_t surfaceid);
    void Draw();

 private:
    std::vector<SubSurface*> m_subSurfaces;
};

#endif  // _OBIGO_SUBSURFACEMANAGER_H_
