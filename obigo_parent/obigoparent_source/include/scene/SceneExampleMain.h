#ifndef __EXAMPLE_SCENEEXAMPLEMAIN_H__
#define __EXAMPLE_SCENEEXAMPLEMAIN_H__

#include <SceneBase.h>

class SceneExampleMain : public appcommon::SceneBase {
    Q_OBJECT
public:
    SceneExampleMain(const std::string& sceneId, const appcommon::WindowBaseRef& parent);

private:
};

#endif  // __EXAMPLE_SCENEEXAMPLEMAIN_H__
