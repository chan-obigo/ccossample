#ifndef __EXAMPLE_EXAMPLESUBSURFACELISTENER_H__
#define __EXAMPLE_EXAMPLESUBSURFACELISTENER_H__

#include <HSubSurface.h>

class ExampleSubSurfaceListener : public ccos::window::IHSubSurfaceListener {
public:
    void onVisibilityChanged(const ccos::HBool& flag) override {
        fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    }
};

#endif  // __EXAMPLE_EXAMPLESUBSURFACELISTENER_H__
