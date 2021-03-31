#define LOG_TAG "ExampleAppService"

#include "ExampleAppService.h"
#include "window/ExampleFrontWindow.h"
#include <Logger.h>

using namespace ccos::system;
using namespace ccos::lifecycle;


REGISTER_APP_SERVICE(ExampleAppService)
ExampleAppService::ExampleAppService(const std::string& serviceType) : HmiAppServiceBase(serviceType) {}

ccos::HBool ExampleAppService::onStart() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);

    registerSession(HLifecycleSession::SESSION_ITEM_BOOTCOMPLETE,
                    HNsmSessionState::NSM_SESSION_STATE_INACTIVE);

    return true;
}

void ExampleAppService::onIACMessageReceived(const std::string& senderId, const std::string& msgId,
                                                    const std::vector<ccos::HByte>& msgData) {
    (void)(senderId);
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);

    if (msgId == "SYSTEM_NOTIFY_AGREEMENT_READY_USERPROFILE") {
        fprintf(stdout, "[ObigoParent]::%s::%d::SYSTEM_NOTIFY_AGREEMENT_READY_USERPROFILE\n", __func__, __LINE__); fflush(stdout);
    }

    if (msgId == "APP_REQUEST_SHOW_IF_AVAILABLE") {
        fprintf(stdout, "[ObigoParent]::%s::%d::APP_REQUEST_SHOW_IF_AVAILABLE\n", __func__, __LINE__); fflush(stdout);
        auto userDataJson = nlohmann::json::from_cbor(msgData);
        if (userDataJson["data"]["type"] == "intent") {
            if (userDataJson["data"]["screen"] == "FRONT_CENTER") {
                fprintf(stdout, "[ObigoParent]::%s::%d::APP_REQUEST_SHOW_IF_AVAILABLE\n", __func__, __LINE__); fflush(stdout);
                std::string appServiceToShow = userDataJson["service_type"];
                std::string intentToShow = userDataJson["data"]["id"];
                requestShowApplication(ccos::HScreenType::FRONT_CENTER, "voicememohmi", appServiceToShow,
                                       ccos::app::manager::appeventmanager::AppLayerIdType::INTENT,
                                       intentToShow, std::string());
            }
        }
    }
}

void ExampleAppService::onSessionStateChanged(const ccos::lifecycle::HLifecycleSession& sessionName,
                                                  const ccos::lifecycle::HNsmSessionState& sessionState) {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);

    if (sessionState == HNsmSessionState::NSM_SESSION_STATE_ACTIVE) {
        fprintf(stdout, "[ObigoParent]::%s::%d::AEM changelayout to home\n", __func__, __LINE__); fflush(stdout);
    } else {
        fprintf(stdout, "[ObigoParent]::%s::%d::registerd BOOT_COMPLETE Session\n", __func__, __LINE__); fflush(stdout);
    }
}


HResult ExampleAppService::onReady() {
    return HResult::OK;
}

HResult ExampleAppService::onRun() {
    fprintf(stdout, "[ObigoParent]::%s::%d\n", __func__, __LINE__); fflush(stdout);
   
    return HResult::OK;
}

HResult ExampleAppService::onSuspend() {
    return HResult::OK;
}

HResult ExampleAppService::onTerminate() {
    return HResult::OK;
}

void ExampleAppService::onLightWeightGC() {
}

void ExampleAppService::onHeavyWeightGC() {
}

void ExampleAppService::onLanguageChanged(const HLanguageType& language) {
    UNUSED(language)
}

void ExampleAppService::onThemeChanged(const std::string& theme) {
    UNUSED(theme)
}

void ExampleAppService::onFontSizeChanged(const HFontSize& size) {
    UNUSED(size)
}

HBool ExampleAppService::onSystemShutdownRequested(const HUInt32& request, const HUInt32& requestId) {
    UNUSED(request)
    UNUSED(requestId)
    return false;
}


void ExampleAppService::onIACSendComplete(const std::string& completeMsgID,
    const ccos::HResult& ret, const std::vector<ccos::HByte>& resultData) {
    UNUSED(completeMsgID)
    UNUSED(ret)
    UNUSED(resultData)
}

void ExampleAppService::onIACPublisherStateUpdated(const std::string& msgID,
    const ccos::appcore::HIACPublisherState& publisherState) {
    UNUSED(msgID)
    UNUSED(publisherState)
}

void ExampleAppService::onIACServiceStateUpdated(const ccos::appcore::iac::HIACStatckStateType& state) {
    UNUSED(state)
}

void ExampleAppService::onUserPreferenceValueChanged(const std::string& section,
    const std::string& key, const std::string& value) {
    UNUSED(section)
    UNUSED(key)
    UNUSED(value)
}

void ExampleAppService::onUserPreferenceReset() {
}

void ExampleAppService::onUserInactivated(const std::string& strUserKey) {
    UNUSED(strUserKey)
}

void ExampleAppService::onUserActivated(const std::string& strUserKey) {
    UNUSED(strUserKey)
}

void ExampleAppService::onUserChangeCompleted() {
}
