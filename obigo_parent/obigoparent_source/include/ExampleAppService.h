#ifndef __EXAMPLE_EXAMPLEAPPSERVICE_H__
#define __EXAMPLE_EXAMPLEAPPSERVICE_H__

#include <HmiAppServiceBase.h>

using namespace ccos;
using namespace appcommon;
using namespace ccos::appcore;
using namespace ccos::lifecycle;
using namespace ccos::system;

class ExampleAppService : public appcommon::HmiAppServiceBase {
    Q_OBJECT
public:
    DECLARE_APP_SERVICE(ExampleAppService)
    explicit ExampleAppService(const std::string& serviceType);

    ccos::HBool onStart() override;

    void onIACMessageReceived(const std::string& senderId, const std::string& msgId,
                              const std::vector<ccos::HByte>& msgData) override;
    void onSessionStateChanged(const ccos::lifecycle::HLifecycleSession& sessionName,
                                           const ccos::lifecycle::HNsmSessionState& sessionState) override;

    HResult onReady() override;
    HResult onRun() override;
    HResult onSuspend() override;
    HResult onTerminate() override;
    void onLightWeightGC() override;
    void onHeavyWeightGC() override;

    void onLanguageChanged(const HLanguageType& language) override;
    void onThemeChanged(const std::string& theme) override;
    void onFontSizeChanged(const HFontSize& size) override;

    HBool onSystemShutdownRequested(const HUInt32& request, const HUInt32& requestId) override;

protected:
    void onIACSendComplete(const std::string& completeMsgID, const ccos::HResult& ret,
                           const std::vector<ccos::HByte>& resultData) override;
    void onIACPublisherStateUpdated(const std::string& msgID, const ccos::appcore::HIACPublisherState& publisherState) override;
    void onIACServiceStateUpdated(const ccos::appcore::iac::HIACStatckStateType& state) override;

    void onUserPreferenceValueChanged(const std::string& section, const std::string& key, const std::string& value) override;
    void onUserPreferenceReset() override;
    void onUserInactivated(const std::string& strUserKey) override;
    void onUserActivated(const std::string& strUserKey) override;
    void onUserChangeCompleted() override;
};

#endif  // __EXAMPLE_EXAMPLEAPPSERVICE_H__
