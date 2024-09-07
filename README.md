# LED_BLINKING_AT_DIFFERENT_RATES_USING_FREERTOS
This code controls an LED on an ESP32, allowing it to blink with a delay specified by serial input. The delay is read from the serial port, converted to an integer, and used to adjust the LED blink rate. It uses FreeRTOS tasks pinned to a specific core for real-time multitasking and efficient resource management.
