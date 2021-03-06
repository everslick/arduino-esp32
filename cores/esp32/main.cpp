#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "Arduino.h"

#if CONFIG_AUTOSTART_ARDUINO

#if CONFIG_FREERTOS_UNICORE
#define ARDUINO_RUNNING_CORE 0
#else
#define ARDUINO_RUNNING_CORE 1
#endif

void loopTask(void *pvParameters)
{
    setup();
    for(;;) {
        // https://github.com/espressif/arduino-esp32/commit/93c45af25640435f78532cc621ea159f525e502a#diff-94536ff8ccf321f988ffa45f021f7137
        //micros(); //update overflow
        loop();
    }
}

extern "C" void app_main()
{
    initArduino();
    xTaskCreatePinnedToCore(loopTask, "loopTask", 12*1024, NULL, 1, NULL, ARDUINO_RUNNING_CORE);
}

#endif
