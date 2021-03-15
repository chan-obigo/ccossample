#define LOG_TAG "Example"


#include <AppEngine.h>
#include <Logger.h>
#include <HCommon.h>

#include <QGuiApplication>
#include <QQmlContext>

#include "ExampleAppService.h"
#include "LogContext.h"
#include "obigo/ObigoStub.h"

using namespace ccos;
using namespace ccos::appcore;

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    Logger::initialize("EXAM", "Example Application");

    v1::commonapi::examples::ObigoStub::getInstance()->Connect();

    appcommon::AppEngine engine;

    if (engine.init() == false) {
        HError() << "AppEngine init failed";
        return -1;
    }

    if (engine.start() == false) {
        HError() << "AppEngine start failed";
        return -1;
    }

    return app.exec();
}
