#include <cstdint>
#include <httpserver.hpp>
#include <memory>
#include <semaphore.h>
#include <string>

#include "battery.h"
#include "nlohmann/json.hpp"
#include "probe-model.h"
#include "solar-panel.h"

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

  std::shared_ptr<http_response> render_POST(const http_request& param) {
    const std::string data = param.get_content();
    return std::shared_ptr<http_response>(new string_response(data.c_str()));
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

class ProbeBatteryResource : public httpserver::http_resource {
private:
  Probe* sim_model;
public:
  ProbeBatteryResource(Probe* p_m_arg) : sim_model(p_m_arg) {}

  std::shared_ptr<http_response> render_PUT(const http_request& request) {

    std::string response = "Ok";
    int response_code = 200;
    
    json msg = json::parse(request.get_content());
    std::string name = msg["name"];
    std::string command = msg["command"];

    if(name.empty() || command.empty()){
      response = "Invalid JSON";
      response_code = 400;
      return std::shared_ptr<http_response>(new string_response(response, response_code));
    }

    bool exist = false;
    if(command == "charging"){
      if(!sim_model->power_manager().set_battery_charging(name, msg["value"])){
	response = "No battery with this name present";
	response_code = 400;
      }
    } else if(command == "enabled"){
      if(!sim_model->power_manager().enable_battery(name)){
	response = "No battery with this name present";
	response_code = 400;
      }
    } else if(command == "rename"){
      if(!sim_model->power_manager().rename_battery(name, msg["value"])){
	response = "No battery with this name present";
	response_code = 400;
      }
    } else {
      response = "Invalid command";
      response_code = 400;
    }
    
    return std::shared_ptr<http_response>(new string_response(response, response_code));
  }

  std::shared_ptr<http_response> render_POST(const http_request& request) {
    std::string response = "Ok";
    int response_code = 200;

    json msg = json::parse(request.get_content());
    std::string bat_name = msg["name"];
    uint32_t charge_level = msg["charge_level"];

    if(bat_name.empty() || !msg.contains("charge_level")){
      response = "Invalid JSON";
      response_code = 400;
      return std::shared_ptr<http_response> (new string_response(response, response_code));
    }

    sim_model->power_manager().add_battery(Battery{
	charge_level,
	bat_name
      });

    return std::shared_ptr<http_response> (new string_response(response, response_code));
  }

  std::shared_ptr<http_response> render_DELETE(const http_request& request) {
    std::string response = "Ok";
    int response_code = 200;

    json msg = json::parse(request.get_content());

    if(!msg.contains("name")){
      response = "Invalid JSON";
      response_code = 400;
      return std::shared_ptr<http_response> (new string_response(response, response_code));
    }

    std::string name = msg["name"];

    bool success = sim_model->power_manager().remove_battery(name);
    if(!success){
      response = "No such battery";
      response_code = 400;
      return std::shared_ptr<http_response> (new string_response(response, response_code));
    }

    return std::shared_ptr<http_response> (new string_response(response, response_code));
  }
};

class ProbeSolarPanelResource : public httpserver::http_resource {
private:
  Probe* sim_model;
public:
  ProbeSolarPanelResource(Probe* p_m_arg) : sim_model(p_m_arg) {}

  std::shared_ptr<http_response> render_POST(const http_request& request) { 
    std::string response = "Ok";
    int response_code = 200;

    json msg = json::parse(request.get_content());
    std::string sol_name = msg["name"];
    uint8_t extract_level = msg["extract_level"];

    if(sol_name.empty() || !msg.contains("extract_level")){
      response = "Invalid JSON";
      response_code = 400;
      return std::shared_ptr<http_response> (new string_response(response, response_code));
    }

    sim_model->power_manager().add_solar_panel(SolarPanel{
	sol_name,
	extract_level
      });

    return std::shared_ptr<http_response> (new string_response(response, response_code));
  }

  std::shared_ptr<http_response> render_PUT(const http_request& request) {

    /*TODO*/

    
  }

  std::shared_ptr<http_response> render_DELETE(const http_request& request) {
    
    std::string response = "Ok";
    int response_code = 200;

    json msg = json::parse(request.get_content());

    if(!msg.contains("name")){
      response = "Invalid JSON";
      response_code = 400;
      return std::shared_ptr<http_response> (new string_response(response, response_code));
    }

    std::string name = msg["name"];

    bool success = sim_model->power_manager().remove_solar_panel(name);
    if(!success){
      response = "No such battery";
      response_code = 400;
      return std::shared_ptr<http_response> (new string_response(response, response_code));
    }

    return std::shared_ptr<http_response> (new string_response(response, response_code));
  }

};

class ProbeStopResource : public httpserver::http_resource {
private:
  Probe* sim_model;
public:
  ProbeStopResource(Probe* p_m_arg) : sim_model(p_m_arg) {}

  std::shared_ptr<http_response> render_POST(const http_request& param) {
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
