#include "signal_handler.h"
#include <signal.h>

SignalHandler::SignalHandler(webserver* ws_arg) : ws(ws_arg) {
  signal(SIGINT, SignalHandler::sigint_handler);
}

void SignalHandler::sigint_handler(int signo){
  if(signo == SIGINT){
    ws->stop();
  }
}
