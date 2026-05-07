#include <Arduino.h>
#include "driver/twai.h"
#include <math.h>

void setup() {
  Serial.begin(115200);

  twai_general_config_t g_config = TWAI_GENERAL_CONFIG_DEFAULT((gpio_num_t)5, (gpio_num_t)17, TWAI_MODE_NORMAL);
  twai_timing_config_t t_config = TWAI_TIMING_CONFIG_500KBITS();
  twai_filter_config_t f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();

  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK){
    Serial.println("CAN Driver Installed");
  }

  if(twai_start() == ESP_OK){
    Serial.println("CAN Driver Started");
  }
}

void loop() {
  twai_message_t message;

  if (twai_receive(&message, pdMS_TO_TICKS(1000)) == ESP_OK){
    uint32_t received_time = (message.data[0] << 24) | (message.data[1] << 16) | (message.data[2] << 8) | (message.data[3]);
    Serial.printf("ID: 0x%03X | Data: ", message.identifier);
    for (int i=0; i<message.data_length_code; i++){
      Serial.printf("%02X ", message.data[i]);
    }
    static uint8_t cnt = 0;
    uint32_t real_time = 256*cnt + message.data[0];
  
    if(message.data[0] == 0xFF){
      cnt = cnt+1;
    }
    

    Serial.println("");

    uint32_t pwm = ((uint32_t)message.data[1] << 8) | (message.data[2]);
    uint32_t set_temp = ((uint32_t)message.data[3] << 8) | (message.data[4]);
    uint32_t temp = ((uint32_t)message.data[5] << 8) | (message.data[6]);
    Serial.printf("t=%.0fs |pwm = %.2f |set_temp=%.2f |temp=%.2f |fault=%u", (float)(real_time/10.0f), (float)(pwm/100.0f), (float)(set_temp/100.0f), (float)(temp/100.0f), message.data[7]);
    Serial.println("");

  }else {
    Serial.println("Waiting for CAN data...");
  }
}

