#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANDLER_H

#include <httpserver.hpp>
#include <signal.h>

using namespace httpserver;

class SignalHandler{
private:
  webserver* ws;
  static void stop_webserver();
public:
  SignalHandler(webserver* ws);
  ~SignalHandler();
  static void sigint_handler(int signo);
  
};

#endif
