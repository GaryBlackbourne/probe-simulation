#include <iostream>
#include <semaphore.h>

#include "server.h"

void* http_server_thread(void * thread_arg){

  // get arguments
  webserver* ws = ((thread_args*)thread_arg)->ws_handle;
  sem_t* sync_sem = ((thread_args*)thread_arg)->sem_handle;
  Probe* sim_model = ((thread_args*)thread_arg)->sim_model;

  // allocating resources
  ProbeStatusResource probe_status_resource{sim_model};
  probe_status_resource.set_allowing("GET", true);
  ProbeStopResource probe_stop_resource{sim_model};
  probe_stop_resource.set_allowing("POST", true);
  TstResource tst_resource{};
  tst_resource.set_allowing("POST", true);
  tst_resource.allow_all();
  

  // registering resources
  ws->register_resource("/get-probe-status", &probe_status_resource);
  ws->register_resource("/stop", &probe_stop_resource);
  ws->register_resource("/test", &tst_resource);

  // synchronise with siulation
  //sem_wait(sync_sem);

  std::cout << "Webserver started!" << std::endl;

  // run webserver
  ws->start(true);

  pthread_exit(NULL);
}
