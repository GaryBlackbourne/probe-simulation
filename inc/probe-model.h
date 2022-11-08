#ifndef _ROVER_MODEL_H
#define _ROVER_MODEL_H

#define PWR_CONSUMPTION 100

#include <pthread.h>
#include "pwr-mngr.h"

class Probe{
private:

  PowerManager pwr_manager;

  pthread_mutex_t probe_lock;

public:

    Probe();
    ~Probe();

    void simulate_step();
    // void print data() ?
};


#endif
