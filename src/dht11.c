#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdio.h>
#include <stdint.h>
#include "esp_rom_sys.h"
#include "dht11.h"

int x;

void inp(int b){
    x = b;
    gpio_set_direction(x, GPIO_MODE_INPUT);
    gpio_set_pull_mode(x, GPIO_PULLUP_ONLY);
}

void start(){
    gpio_set_direction(x, GPIO_MODE_OUTPUT);
    gpio_set_level(x, 0);                 
    vTaskDelay(pdMS_TO_TICKS(20));        
    gpio_set_level(x, 1);                 
    esp_rom_delay_us(40);  
     
    
}

int detect(){ 
    gpio_set_direction(x, GPIO_MODE_INPUT);
    gpio_set_pull_mode(x, GPIO_PULLUP_ONLY);
    esp_rom_delay_us(10);//to send a singal to the dht11 for detection and start sending signals
    int timeout = 0;
    while(gpio_get_level(x) == 1) {
        esp_rom_delay_us(1);
        if(timeout++ > 200) {
            printf("%d",timeout);
            printf("detect error ");
            return 0;     
    }
}
    
    int y = 0;
    while(gpio_get_level(x) == 0){
        esp_rom_delay_us(1);
        y++;
        if(y > 200){
            printf("Check detect function (delay low >200 micros)\n");
            return 0;                     
        }
    }
    
    y = 0;
    while(gpio_get_level(x) == 1){
        esp_rom_delay_us(1);
        y++;
        if(y > 200){
            printf("Check detect function (delay high >200 micros)\n");
            return 0;                     
        }
    }
    return 1;
}

int readbit(){
    int time = 0;
    int timeout = 0;
    
    while(gpio_get_level(x) == 1) {
        esp_rom_delay_us(1);
        if(timeout++ > 200) return -1;    
    }
    
    timeout = 0;
    while(gpio_get_level(x) == 0) {
        esp_rom_delay_us(1);
        if(timeout++ > 200) return -1;    
    }
    
    while(gpio_get_level(x) == 1){
        esp_rom_delay_us(1);
        time++;
        if(time > 200) return -1;         
    }
    
    if(time < 40){
        return 0;
    }
    return 1;
}

uint8_t byte_creation(){
    uint8_t byte = 0;
    for(int i = 0; i < 8; i++){
        byte = byte << 1;
        int bit = readbit();
        if (bit == -1) return 0;          // Breakout if timeout was triggered
        byte = byte | bit;
    }
    return byte;
}

void data(uint8_t *humint,uint8_t *humdec,uint8_t *tempint,uint8_t *tempdec){
    
    uint8_t bytes[5];
    uint8_t check_sum;
    
    start();
    if(detect()==0){
        printf("Sensor detection failed! Check wiring on GPIO %d\n", x);
        return;
    }

    
    for(int i = 0; i < 5; i++){
        bytes[i] = byte_creation();
    }
     *humint=bytes[0];
     *humdec=bytes[1];
     *tempint=bytes[2];
     *tempdec=bytes[3];
    check_sum = bytes[0] + bytes[1] + bytes[2] + bytes[3];
    if(check_sum == bytes[4] && bytes[4] != 0){
        printf("Humidity is: %d.%d%%\n", bytes[0], bytes[1]);
        printf("Temperature is: %d.%d°C\n", bytes[2], bytes[3]);
    } else {
        printf("Checksum mismatch or corrupt data read.\n");
    }
}