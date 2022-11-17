#include <unistd.h>
#include <pthread.h>
#include <httpserver.hpp>
#include "nlohmann/json.hpp"

#include "probe-model.h"

#define SIMULATION_RESOLUTION_US 500000 // us = 500 ms

using namespace httpserver;

class TstResource : public httpserver::http_resource {
public:
  std::shared_ptr<http_response> render(const http_request&) {
            return std::shared_ptr<http_response>(new string_response("Hello, World!"));
        }
};

void http_server_thread(int a){

  return;
}

int main(int argc, char* argv[]){

  webserver ws = create_webserver(8080);

  TstResource rsrc;

  ws.register_resource("/test", &rsrc);

  ws.start(true);

  /*

  bool run = true;

  Probe probe_model;

  // launch comm- thread

  while(run){

    probe_model.simulate_step();

    usleep(SIMULATION_RESOLUTION_US);
    }*/
  return 0;
}
