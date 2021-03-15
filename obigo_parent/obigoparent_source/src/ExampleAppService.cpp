#define LOG_TAG "ExampleAppService"

#include "ExampleAppService.h"
#include "window/ExampleFrontWindow.h"
#include <Logger.h>

using namespace ccos::system;
using namespace ccos::lifecycle;


REGISTER_APP_SERVICE(ExampleAppService)
ExampleAppService::ExampleAppService(const std::string& serviceType) : HmiAppServiceBase(serviceType) {}

ccos::HBool ExampleAppService::onStart() {
    HDebug() << "adding windows for ExampleAppService";

    registerSession(HLifecycleSession::SESSION_ITEM_BOOTCOMPLETE,
                    HNsmSessionState::NSM_SESSION_STATE_INACTIVE);

    return true;
}

void ExampleAppService::onIACMessageReceived(const std::string& senderId, const std::string& msgId,
                                                    const std::vector<ccos::HByte>& msgData) {
    (void)(senderId);

    if (msgId == "SYSTEM_NOTIFY_AGREEMENT_READY_USERPROFILE") {
         HInfo() << "agreement_ready_ExampleAPP";  
      }
  
    HInfo() << "SendMessage_ExampleAPP";

    ccos::HByte val1 = 0x01;
    std::vector<ccos::HByte> _msgData;
    _msgData.push_back(val1);

    sendMessage("VEHICLESTATEMANAGER", "ExampleApp_to_ExampleManagerApp", _msgData);
}

void ExampleAppService::onSessionStateChanged(const ccos::lifecycle::HLifecycleSession& sessionName,
                                                  const ccos::lifecycle::HNsmSessionState& sessionState) {
    HInfo() << "onSessionStateChanged_ExampleApp";

    if (sessionState == HNsmSessionState::NSM_SESSION_STATE_ACTIVE) {
        HInfo() << "AEM changelayout to home";
    } else {   
        HInfo() << "registerd BOOT_COMPLETE Session";
    }
}


HResult ExampleAppService::onReady() {
    return HResult::OK;
}

HResult ExampleAppService::onRun() {
    HInfo() << "Runeeeeee";
   
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
