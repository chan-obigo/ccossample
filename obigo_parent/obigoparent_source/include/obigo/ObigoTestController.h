#ifndef _OBIGO_TEST_CONTROLLER_H_
#define _OBIGO_TEST_CONTROLLER_H_

#include <map>
#include <vector>

class SubSurfaceManager;

class ObigoTestController {
 public:

    ObigoTestController(SubSurfaceManager* surfaceManager);
    void initActionList();
#if 0
    void Connect();
    void fireCreateApplicationEvent();
    void fireDestroyApplicationEvent(uint32_t surface_id);
    void fireDestroyIviSurfaceEvent(uint32_t surface_id);
    void fireDestroyWlSurfaceEvent(uint32_t surface_id);
    void fireDestroyWlEglSurfaceEvent(uint32_t surface_id);
    void fireDestroyEglSurfaceEvent(uint32_t surface_id);
    void fireMakeCurrentNoSurfaceEvent(uint32_t surface_id);
#endif    

    void initHistory();
    void run();
    SubSurfaceManager* getHost() { return m_host; }


    //  action list (from parent to child) - async
    static bool create_application(uint32_t index, void *data);
    static bool destroy_application(uint32_t index, void *data);

    //  action list (from parent to child) - sync
    static bool waiting(uint32_t ms, void *data);


 private:
    ~ObigoTestController();

    SubSurfaceManager* m_host;
    std::map<std::string, bool (*)(uint32_t, void * )> m_actionList;
    std::vector<std::pair<std::string, uint32_t>> m_controlHistory;
};

#endif  // _OBIGO_TEST_CONTROLLER_H_
