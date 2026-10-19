#include "provision_portal.h"
#include "system_globals.h"
#include "freertos/task.h"

void wifi_provision_task(void *p) {
    (void)p;
    provision_portal_start();
    vTaskDelete(NULL);
}
