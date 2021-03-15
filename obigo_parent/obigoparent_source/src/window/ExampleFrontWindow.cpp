#include <QQuickWindow>
#include <QtGui/QGuiApplication>
#include <wayland-client-protocol.h>
#include "QtGui/5.15.1/QtGui/qpa/qplatformnativeinterface.h"

#include "LogContext.h"
#include "window/ExampleFrontWindow.h"

#include "scene/SceneExampleMain.h"
#include "obigo/SubSurfaceManager.h"

using namespace ccos;

REGISTER_WINDOW(ExampleFrontWindow)
ExampleFrontWindow::ExampleFrontWindow(const appcommon::HmiAppServiceBaseRef& parent,
                                       const ccos::HScreenType& screenType,
                                       const std::string& layer,
                                       const ccos::app::common::appcommontype::WindowType& windowType)
    : WindowBase(parent, screenType, layer, windowType) {}

ExampleFrontWindow::~ExampleFrontWindow() {}

HBool ExampleFrontWindow::onCreate() {
    HInfo() << "[Example] ExampleFrontWindow::onCreate";
    return true;
}

void ExampleFrontWindow::onLoaded() {
    HInfo() << "[Example] ExampleFrontWindow::onLoaded";
    m_qquickWindow = const_cast<QQuickWindow*>(&getQWindow());
}

void ExampleFrontWindow::onUnLoaded() { m_qquickWindow = nullptr; }

void ExampleFrontWindow::onBindScene() {
    bindScene<SceneExampleMain>("EXAMPLE.Main");

    std::vector<std::string> sceneIDs;
    getSceneIDs(sceneIDs);
    for (const auto &scene : sceneIDs) {
        HInfo() << "[Example]" << scene;
    }
}

void ExampleFrontWindow::onShow() {
    HInfo() << "ExampleFrontWindow onShow()";
}

void ExampleFrontWindow::onHide() {
    HInfo() << "ExampleFrontWindow onHide()";
}


ccos::HBool ExampleFrontWindow::onControllerTouchEvent(const std::vector<ccos::common::HTouchEvent> &events) {
    HInfo() << "ExampleFrontWindow::onControllerTouchEvent ++++++++++++++++++++" << __func__ << "::" << __LINE__;
}


void ExampleFrontWindow::createSlot() {
    HInfo() << "ExampleFrontWindow:: ++++++++++++++++++ " << __func__ << "::" << __LINE__;

    SubSurfaceManager::getInstance()->create();
}

void ExampleFrontWindow::showSlot() {
    HInfo() << "ExampleFrontWindow:: ++++++++++++++++++ " << __func__ << "::" << __LINE__;

    QPlatformNativeInterface *native = QGuiApplication::platformNativeInterface();
    struct wl_surface *surface = static_cast<struct wl_surface *>(native->nativeResourceForWindow("surface", m_qquickWindow));
    struct wl_compositor *compositor = static_cast<struct wl_compositor *>(native->nativeResourceForIntegration("compositor"));

    struct wl_region *region = wl_compositor_create_region(compositor);
    wl_region_add(region, 0, 0, 1920, 106);
    wl_surface_set_input_region(surface, region);
    wl_region_destroy(region);

    ccos::window::HWindowId hWindowId = const_cast<ccos::window::HWindow&>(getHWindow()).getWindowId();

    SubSurfaceManager::getInstance()->show(hWindowId);
}

void ExampleFrontWindow::hideSlot() {
    HInfo() << "ExampleFrontWindow:: ++++++++++++++++++ " << __func__ << "::" << __LINE__;

    ccos::window::HWindowId hWindowId = const_cast<ccos::window::HWindow&>(getHWindow()).getWindowId();
    SubSurfaceManager::getInstance()->hide(hWindowId);
}
