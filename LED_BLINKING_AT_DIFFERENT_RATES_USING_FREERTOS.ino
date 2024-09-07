#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else 
static const BaseType_t app_cpu = 1;
#endifhhh

char receivedData[100];
static int delayTime = 0; // Initialize delayTime to 0
static const int led_pin = 2;
int i = 0; // Declare i as a global variable to persist its value

void toggleLED(void *parameter)
{
  while(1)
  {
    if(delayTime != 0)
    {
      digitalWrite(led_pin, HIGH);
      vTaskDelay(delayTime / portTICK_PERIOD_MS);
      digitalWrite(led_pin, LOW);
      vTaskDelay(delayTime / portTICK_PERIOD_MS);
    }
    vTaskDelay(1 / portTICK_PERIOD_MS); // Prevent watchdog timer reset
  }
}

void setup() {
  Serial.begin(300);
  pinMode(led_pin, OUTPUT);

  xTaskCreatePinnedToCore(
        toggleLED,
        "Toggle Led", 
        1024,
        NULL,
        1,
        NULL,
        app_cpu);
}

void loop()
{
  while (Serial.available() > 0) {
    char c = Serial.read();
    if (c == '\n' || c == '\r')
    {
      if (i > 0) { // Only process if there is something in receivedData
        receivedData[i] = '\0'; // Null-terminate the string
        delayTime = atoi(receivedData); // Convert to integer
        Serial.println(delayTime); // Print the delay time
        i = 0; // Reset index for next input
      }
    } 
    else 
    {
      if (isdigit(c) && i < sizeof(receivedData) - 1) { // Check if character is numeric and avoid buffer overflow
        receivedData[i++] = c; // Store the character and increment the index
      }
    }
  }

  vTaskDelay(1 / portTICK_PERIOD_MS); // Yield to FreeRTOS tasks
}