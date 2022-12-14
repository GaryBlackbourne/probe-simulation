#include <iostream>
#include <memory>
#include <unistd.h>
#include <pthread.h>
#include <httpserver.hpp>
#include <semaphore.h>
#include <signal.h>

#include "nlohmann/json.hpp"

#include "probe-model.h"
#include "server.h"
//#include "signal_handler.h"

#define SIMULATION_RESOLUTION_US 1000000 // us = 500 ms
#define DEBUG true

using namespace httpserver;
using namespace nlohmann::literals;
using json = nlohmann::json;

    
int main(int argc, char* argv[]){
  
  Probe probe_model;                                        // create model for simulation

  webserver ws = create_webserver(8080);                    // webserver instance for communication

  // auto sig_handler = SignalHandler{&ws};
  
  sem_t sync_sem;                                           // synchronise semaphore
  sem_init(&sync_sem, 0, 0);                                // initialize semaphore

  pthread_t server_thread_id;                               // thread id for communication
  thread_args thread_arg = {&ws, &sync_sem, &probe_model};  // set thread arguments
  
  // start thread
  if(pthread_create(&server_thread_id, NULL, http_server_thread, &thread_arg) != 0){
    return 1;
  }

  //sem_post(&sync_sem);
  std::cout << "Simulation started!" << std::endl;

  bool first_loop = true;
  while(probe_model.is_sim_running()){
    probe_model.simulate_step();
    std::cout << probe_model.serialize().dump(4) << std::endl;
    usleep(SIMULATION_RESOLUTION_US);
    if(first_loop){
      first_loop = false;
      sem_post(&sync_sem);
    }
  }
  
  ws.stop();                                // stop webserver
  pthread_join(server_thread_id, NULL);     // wait for server to stop
  sem_destroy(&sync_sem);
  
  return 0;
}

