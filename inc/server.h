#include <httpserver.hpp>
#include <semaphore.h>

#include "nlohmann/json.hpp"

#include "probe-model.h"

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

  std::shared_ptr<http_response> render_GET(const http_request&) {
    return std::shared_ptr<http_response>(new string_response(msg.dump()));
  }
};

/** @class Probestatusresource
 *  @brief This class is a resource for the http server, and servers as an interface to querry the probes status. It stores a reference for the probe object.
 *
 */
class ProbeStatusResource : public httpserver::http_resource {
private:
  Probe* sim_model;
public:
  ProbeStatusResource(Probe* p_m_arg) : sim_model(p_m_arg) {}

  std::shared_ptr<http_response> render_GET(const http_request&) {
    return std::shared_ptr<http_response>(new string_response(sim_model->serialize().dump()));
  }
};

class ProbeStopResource : public httpserver::http_resource {
private:
  Probe* sim_model;
public:
  ProbeStopResource(Probe* p_m_arg) : sim_model(p_m_arg) {}

  std::shared_ptr<http_response> render_POST(const http_request&) {
    sim_model->stop_simulation();
    return std::shared_ptr<http_response>(new string_response("Shutting down!"));
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
  Probe* sim_model;
};

/**
 * @brief This function is a thread responsible for running a webserver.
 *
 * @argument thread_arg is a pointer, pointing to an existing thread_args struct, which is to be created  and initialized before invoking this function.
 *
 * @return This function returns NULL always
 */
void* http_server_thread(void * thread_arg);
