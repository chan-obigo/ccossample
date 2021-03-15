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

    // v1::commonapi::examples::ObigoStub::getInstance()->Connect();

    appcommon::AppEngine engine;

    if (engine.init() == false) {
        fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
        return -1;
    }

    if (engine.start() == false) {
        fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
        return -1;
    }

    return app.exec();
}
