#include <iostream>
#include <microhttpd.h>
#include <semaphore.h>

#include "server.h"
#include "solar-panel.h"

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





TstResource::TstResource() {
  msg = json::parse(R"({ "address" : "0x07", "data" : "0x55" })");
}

std::shared_ptr<http_response> TstResource::render_POST(const http_request& param) {
  const std::string data = param.get_content();
  return std::shared_ptr<http_response>(new string_response(data.c_str()));
}


std::shared_ptr<http_response> ProbeBatteryResource::render_PUT(const http_request &request) {

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
  
  if(command == "charge"){
    if(!sim_model->power_manager().set_battery_charging(name, true)){
      response = "No battery with this name present";
      response_code = 400;
    }
  }  else if(command == "stop-charge"){
    if(!sim_model->power_manager().set_battery_charging(name, false)){
      response = "No battery with this name present";
      response_code = 400;
    }
  } else if(command == "enable"){
    if(!sim_model->power_manager().enable_battery(name)){
      response = "No battery with this name present";
      response_code = 400;
    }
  }  else if(command == "disable"){
    if(!sim_model->power_manager().disable_battery(name)){
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

std::shared_ptr<http_response> ProbeBatteryResource::render_POST(const http_request& request) {
  std::string response = "Ok";
  int response_code = 200;
  
  json msg = json::parse(request.get_content());
  std::string bat_name = msg["name"];
  uint32_t charge_level = msg["charge-level"];
  
  if(bat_name.empty() || !msg.contains("charge-level")){
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

std::shared_ptr<http_response> ProbeBatteryResource::render_DELETE(const http_request& request) {
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

std::shared_ptr<http_response> ProbeSolarPanelResource::render_POST(const http_request& request) { 
  std::string response = "Ok";
  int response_code = 200;
  
  json msg = json::parse(request.get_content());
  std::string sol_name = msg["name"];
  uint8_t extract_level = msg["extract-level"];
  
  if(sol_name.empty() || !msg.contains("extract-level")){
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

std::shared_ptr<http_response> ProbeSolarPanelResource::render_PUT(const http_request &request) {

  std::string response = "Ok";
  int response_code = 200;
  json msg = json::parse(request.get_content());

  if(!msg.contains("command") || !msg.contains("value") || !msg.contains("name")){
    response = "Invalid JSON";
    response_code = 400;
    return std::shared_ptr<http_response> (new string_response(response, response_code));
  }

  std::string command = msg["command"];
  std::string name = msg["name"];
  
  if(command == "rename") {
    if(!sim_model->power_manager().rename_battery(name, msg["value"])){
      response = "No Solar panel with this name present";
      response_code = 400;
    }
  } else if (command == "extract") {
    if(!sim_model->power_manager().extract_solar_panel(name, msg["value"])){
      response = "No Solar panel with this name present";
      response_code = 400;
    }
  } else {
    response = "Invalid JSON";
    response_code = 400;
  }

  return std::shared_ptr<http_response> (new string_response(response, response_code));
}

std::shared_ptr<http_response> ProbeSolarPanelResource::render_DELETE(const http_request &request) {

  std::string response = "Ok";
  int response_code = 200;

  json msg = json::parse(request.get_content());

  if (!msg.contains("name")) {
    response = "Invalid JSON";
    response_code = 400;
    return std::shared_ptr<http_response>(
        new string_response(response, response_code));
  }

  std::string name = msg["name"];

  bool success = sim_model->power_manager().remove_solar_panel(name);
  if (!success) {
    response = "No such battery";
    response_code = 400;
    return std::shared_ptr<http_response>(
        new string_response(response, response_code));
  }

  return std::shared_ptr<http_response>(
      new string_response(response, response_code));
}

std::shared_ptr<http_response> ProbeStopResource::render_POST(const http_request &param) {
  sim_model->stop_simulation();
  return std::shared_ptr<http_response>(new string_response("Shutting down!"));
}

std::shared_ptr<http_response> ProbePwrManagerResource::render_PUT(const http_request &request) {

  std::string response = "Ok";
  int response_code = 200;

  json msg = json::parse(request.get_content());

  if(!msg.contains("value")){
    response = "Invalid JSON";
    response_code = 400; 
    return std::shared_ptr<http_response>(new string_response(response, response_code));
  }

  sim_model->power_manager().set_pwr_draw(msg["value"]);

  return std::shared_ptr<http_response>(new string_response(response, response_code));
}
