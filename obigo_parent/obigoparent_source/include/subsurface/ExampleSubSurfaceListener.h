#ifndef __EXAMPLE_EXAMPLESUBSURFACELISTENER_H__
#define __EXAMPLE_EXAMPLESUBSURFACELISTENER_H__

#include <HSubSurface.h>

#include "LogContext.h"

class ExampleSubSurfaceListener : public ccos::window::IHSubSurfaceListener {
public:
    void onVisibilityChanged(const ccos::HBool& flag) override {
        HInfo() << "[Example] ExampleSubSurfaceListener::onVisibilityChanged(" << flag << ")";
    }
};

#endif  // __EXAMPLE_EXAMPLESUBSURFACELISTENER_H__
