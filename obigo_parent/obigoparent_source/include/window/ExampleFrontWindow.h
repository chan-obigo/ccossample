#ifndef __EXAMPLE_EXAMPLEFRONTWINDOW_H__
#define __EXAMPLE_EXAMPLEFRONTWINDOW_H__

#include <memory>

#include <WindowBase.h>

class QQuickWindow;
class ExampleFrontWindow : public appcommon::WindowBase {
    Q_OBJECT
 public:
    DECLARE_WINDOW(ExampleFrontWindow)
    explicit ExampleFrontWindow(const appcommon::HmiAppServiceBaseRef& parent, const ccos::HScreenType& screenType,
                                const std::string& layer,
                                const ccos::app::common::appcommontype::WindowType& windowType);
    ~ExampleFrontWindow();

    ccos::HBool onCreate() override;
    void onLoaded() override;
    void onUnLoaded() override;

    void onBindScene() override;
    void onShow() override;
    void onHide() override;
    ccos::HBool onControllerTouchEvent(const std::vector<ccos::common::HTouchEvent> &events) override;

 public slots:
    void createSlot();
    void showSlot();
    void hideSlot();

 private:
    QQuickWindow* m_qquickWindow = nullptr;
};

#endif  // __EXAMPLE_EXAMPLEFRONTWINDOW_H__
