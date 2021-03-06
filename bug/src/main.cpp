#include "bug_event.h"
#include "client_bug_event.h"
#include "logger.h"
#include "mbed.h"
#include "tracker_position.h"
#include "wifi.h"

class App : public WIFI, public BugEventClient, public PositionTracker {
 public:
  App() : WIFI(), BugEventClient(this), PositionTracker(this) {
    log_infoln("app inited");
  }

  ~App() {
    // join each thread (in reverse order)
    PositionTracker::join();
    BugEventClient::join();
    WIFI::join();

    log_infoln("app stopped");
  }

  void run() {
    // start each thread
    WIFI::start();
    BugEventClient::start();
    PositionTracker::start();

    log_infoln("app started");
  }
};

int main() {
  App app;
  app.run();
}
