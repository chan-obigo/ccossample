#include <unistd.h>
#include <ctime>
#include <csignal>
#include <cstdint>
#include <list>

#include "obigo/ObigoTestController.h"

#include "obigo/SubSurfaceManager.h"


// commonly used

std::vector<std::string> split(const std::string& str, const std::string& delimiters) {
    std::vector<std::string> result;
    std::string token;

    if (delimiters.empty()) {
        result.push_back(str);
        return result;
    }

    size_t current = str.find(delimiters);
    size_t previous = 0U;

    while (current != std::string::npos) {
        token = str.substr(previous, current - previous);
        result.push_back(token);
        previous = current + delimiters.length();
        current = str.find(delimiters, previous);
    }
    result.push_back(str.substr(previous, current - previous));

    return result;
}






ObigoTestController::ObigoTestController(SubSurfaceManager* surfaceManager) {

	m_host = surfaceManager;
	initActionList();
	initHistory();
}


ObigoTestController::~ObigoTestController() {


}


void ObigoTestController::initActionList() {
	m_actionList.insert(std::pair<std::string, bool (*)(uint32_t , void *)>("create_application", create_application));
	m_actionList.insert(std::pair<std::string, bool (*)(uint32_t , void *)>("destroy_application", destroy_application));
	m_actionList.insert(std::pair<std::string, bool (*)(uint32_t , void *)>("waiting", waiting));
}

void ObigoTestController::initHistory() {
#if 0
	FILE *stream;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	stream = fopen("history.txt", "r");
	if (stream == nullptr) {
		return;
	}

	while (getline(&line, &len, stream) != -1) {
	   std::vector<std::string> elem = split(line, " ");
	   if (elem.size() > 1) {
			m_controlHistory.push_back(std::pair<std::string, uint32_t>(elem[0], strtol(elem[1].c_str(), nullptr, 10)));
	   }
	}

    free(line);
    fclose(stream);
#else	
	m_controlHistory.push_back(std::pair<std::string, uint32_t>("create_application", 0));
	m_controlHistory.push_back(std::pair<std::string, uint32_t>("waiting", 3000));
	m_controlHistory.push_back(std::pair<std::string, uint32_t>("destroy_application", 0));
#endif	
}

void ObigoTestController::run() {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d <-- size\n", __func__, __LINE__, m_controlHistory.size()); fflush(stdout);
    if (m_controlHistory.empty()){
        fprintf(stdout, "[ObigoParent]::%s::%d === finished history\n", __func__, __LINE__); fflush(stdout);
    	return;
    }

	std::pair<std::string, uint32_t> command = m_controlHistory.front();
    m_controlHistory.erase(m_controlHistory.begin());

	bool (*func)(uint32_t, void * ) =  m_actionList[command.first];
	uint32_t surface_id = command.second;
	bool ret = func(surface_id, this);
}

bool ObigoTestController::create_application(uint32_t index, void *data) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
	ObigoTestController *pThis = reinterpret_cast<ObigoTestController *>(data);
	pThis->getHost()->create_application(index);
}

bool ObigoTestController::destroy_application(uint32_t index, void *data) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, index); fflush(stdout);
	ObigoTestController *pThis = reinterpret_cast<ObigoTestController *>(data);
	pThis->getHost()->destroy_application(index);
}

static void TimerExpired(sigval const sv) noexcept {
	ObigoTestController *pThis = reinterpret_cast<ObigoTestController *>(sv.sival_ptr);
	pThis->run();
}

bool ObigoTestController::waiting(uint32_t ms, void *data) {
    fprintf(stdout, "[ObigoParent]::%s::%d::%d\n", __func__, __LINE__, ms); fflush(stdout);

    timer_t timerID;
    struct sigevent sev;
    struct itimerspec its;

    sev.sigev_notify = SIGEV_THREAD;
    sev.sigev_notify_function  = &TimerExpired;
    sev.sigev_value.sival_ptr = data;
    sev.sigev_notify_attributes = nullptr;

    if (-1 == timer_create(CLOCK_REALTIME, &sev, &timerID)) {
        return false;
    }

    /* Start the timer */
    its.it_value.tv_sec = static_cast<int32_t>(ms / 1000);
    its.it_value.tv_nsec = static_cast<int32_t>((ms % 1000) * 1000 * 1000);
    its.it_interval.tv_sec = 0;
    its.it_interval.tv_nsec = 0;

    if (-1 == timer_settime((timerID), 0, &its, nullptr)) {
        return false;
    }
}

