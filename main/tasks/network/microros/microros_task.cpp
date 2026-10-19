#include "microros_runtime.h"
#include "system_globals.h"

void microros_task(void *p) {
    (void)p;
    microros_runtime_loop();
}
