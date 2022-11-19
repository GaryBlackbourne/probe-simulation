#include <iostream>
#include <memory>
#include <unistd.h>
#include <pthread.h>
#include <httpserver.hpp>
#include <semaphore.h>

#include "nlohmann/json.hpp"

#include "probe-model.h"

#define SIMULATION_RESOLUTION_US 1000000 // us = 500 ms
#define DEBUG true

using namespace httpserver;
using namespace nlohmann::literals;
using json = nlohmann::json;


/** @class TstResource
 *  @brief This class is a resource for the http server, and implements a get response
 *
 *  @var msg is a json object which stores data for testing
 *
 */
class TstResource : public httpserver::http_resource {
private:
  json msg;
public:
  TstResource(){
    msg = json::parse(R"({ "address" : "0x07", "data" : "0x55" })");
  }

  std::shared_ptr<http_response> render(const http_request&) {
    return std::shared_ptr<http_response>(new string_response(msg.dump()));
  }
};

/** @class Probestatusresource
 *  @brief This class is a resource for the http server, and servers as an interface to querry the probes status. It stores a reference for the probe object.
 *
 */
class ProbeStatusResource : public httpserver::http_resource {
private:
  Probe& probe_model;
public:
  ProbeStatusResource(Probe& p_m_arg) : probe_model(p_m_arg) {}

  std::shared_ptr<http_response> render(const http_request&) {
    return std::shared_ptr<http_response>(new string_response(probe_model.serialize().dump()));
  }
};

/**@struct thread_args
 * @brief This struct encapsulates the arguments for the webserver thread
 *
 * @var ws_handle is a pointer to a webserver object
 *
 * @var sem_handle is a POSIX semaphore handle 
 */
struct thread_args{
  webserver* ws_handle;
  sem_t* sem_handle;
};


/**
 * @brief This function is a thread responsible for running a webserver.
 *
 * @argument thread_arg is a pointer, pointing to an existing thread_args struct, which is to be created  and initialized before invoking this function.
 *
 * @return This function returns NULL always
 */
void* http_server_thread(void * thread_arg){

  // get arguments
  webserver* ws = ((thread_args*)thread_arg)->ws_handle;
  sem_t* sync_sem = ((thread_args*)thread_arg)->sem_handle;

  // allocating resources
  TstResource rsrc;

  // registering resources
  ws->register_resource("/test", &rsrc);

  // synchronise with siulation
  sem_wait(sync_sem);

  // run webserver
  ws->start(true);

  pthread_exit(NULL);
}

int main(int argc, char* argv[]){

  webserver ws = create_webserver(8080);      // webserver instance for communication
  sem_t sync_sem;                             // synchronise semaphore
  sem_init(&sync_sem, 0, -1);                 // initialize semaphore

  pthread_t server_thread_id;                 // thread id for communication
  thread_args thread_arg = {&ws, &sync_sem};  // set thread arguments
  
  // start thread
  /*
  if(pthread_create(&server_thread_id, NULL, http_server_thread, &thread_arg) != 0){
    return 1;
  }
  */
  bool run = true;
  Probe probe_model;

  // sem_post(&sync_sem);
  while(run){
    
    probe_model.simulate_step();
    std::cout << probe_model.serialize() << std::endl;
    usleep(SIMULATION_RESOLUTION_US);
    
  }
  /*
  ws.stop();                                // stop webserver
  pthread_join(server_thread_id, NULL);     // wait for server to stop
  */
  return 0;
}
