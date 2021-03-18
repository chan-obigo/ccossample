#include <QQuickWindow>
#include <QtGui/QGuiApplication>
#include <wayland-client-protocol.h>
#include "QtGui/5.15.1/QtGui/qpa/qplatformnativeinterface.h"

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
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);

    return true;
}

void ExampleFrontWindow::onLoaded() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    m_qquickWindow = const_cast<QQuickWindow*>(&getQWindow());

    QObject::connect(m_qquickWindow->findChild<QObject*>("MyBtn1"), SIGNAL(createSignal()), this, SLOT(createSlot()));
    QObject::connect(m_qquickWindow->findChild<QObject*>("MyBtn2"), SIGNAL(showSignal()), this, SLOT(showSlot()));
    QObject::connect(m_qquickWindow->findChild<QObject*>("MyBtn3"), SIGNAL(raiseIssueSignal()), this, SLOT(raiseIssueSlot()));

    ccos::window::HWindowId hWindowId = const_cast<ccos::window::HWindow&>(getHWindow()).getWindowId();
    SubSurfaceManager::getInstance()->setWinID(hWindowId);
}

void ExampleFrontWindow::onUnLoaded() { m_qquickWindow = nullptr; }

void ExampleFrontWindow::onBindScene() {
    bindScene<SceneExampleMain>("EXAMPLE.Main");

    std::vector<std::string> sceneIDs;
    getSceneIDs(sceneIDs);
    for (const auto &scene : sceneIDs) {
        fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
    }
}

void ExampleFrontWindow::onShow() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
}

void ExampleFrontWindow::onHide() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
}


ccos::HBool ExampleFrontWindow::onControllerTouchEvent(const std::vector<ccos::common::HTouchEvent> &events) {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
}


void ExampleFrontWindow::createSlot() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);

    SubSurfaceManager::getInstance()->create();
}

void ExampleFrontWindow::showSlot() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);

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

void ExampleFrontWindow::raiseIssueSlot() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);

    ccos::window::HWindowId hWindowId = const_cast<ccos::window::HWindow&>(getHWindow()).getWindowId();
    SubSurfaceManager::getInstance()->raiseIssue(hWindowId);
}
