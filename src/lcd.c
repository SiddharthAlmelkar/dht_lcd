#include "lcd.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <stdio.h>
#include "esp_rom_sys.h"
#include <stdint.h>

  uint8_t pins[] = {14, 27, 26, 25, 33, 32, 19, 13};
  uint8_t rs = 4;
  uint8_t rw = 5;
  uint8_t e = 18;

void setpin(void) {
    gpio_reset_pin(rs);
    gpio_reset_pin(rw);
    gpio_reset_pin(e);
    
    gpio_set_direction(rs, GPIO_MODE_OUTPUT);
    gpio_set_direction(rw, GPIO_MODE_OUTPUT);
    gpio_set_direction(e, GPIO_MODE_OUTPUT);
    
    for (uint8_t i = 0; i < 8; i++) {
        gpio_reset_pin(pins[i]);
        gpio_set_direction(pins[i], GPIO_MODE_OUTPUT);
    }
}

void scmd(uint8_t cmd) {
    gpio_set_level(rs, 0);
    gpio_set_level(rw, 0);
    
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_level(pins[i], (cmd >> i) & 0x01);
    }
    
    esp_rom_delay_us(50);
    gpio_set_level(e, 1);
    esp_rom_delay_us(50); 
    gpio_set_level(e, 0);
    esp_rom_delay_us(100);
    
    if (cmd == 0x01 || cmd == 0x02) {
        vTaskDelay(pdMS_TO_TICKS(5));
    } else {
        esp_rom_delay_us(200);
    }
}

void sdata(uint8_t bit) {
    uint8_t byte;
    printf("bit%d\n",bit);
    gpio_set_level(rs, 1);
    gpio_set_level(rw, 0);
    
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_level(pins[i], (bit >> i) & 0x01);
        byte= (bit >> i) & 0x01;
        printf("%d\n",byte);

    }
    
    esp_rom_delay_us(50);
    gpio_set_level(e, 1);
    esp_rom_delay_us(50); 
    gpio_set_level(e, 0);
    esp_rom_delay_us(100);
}

void lcd_init(void) {
    vTaskDelay(pdMS_TO_TICKS(100)); 
    setpin();
    
    gpio_set_level(e, 0);
    gpio_set_level(rs, 0);
    gpio_set_level(rw, 0);
    for (uint8_t i = 0; i < 8; i++) {
        gpio_set_level(pins[i], 0);
    }
    vTaskDelay(pdMS_TO_TICKS(100));
    
    scmd(0x30);
    vTaskDelay(pdMS_TO_TICKS(10));
    scmd(0x30);
    vTaskDelay(pdMS_TO_TICKS(2));
    scmd(0x30);
    vTaskDelay(pdMS_TO_TICKS(2));
    
    scmd(0x38); 
    vTaskDelay(pdMS_TO_TICKS(2));
    scmd(0x0C); 
    vTaskDelay(pdMS_TO_TICKS(2));
    scmd(0x01); 
    vTaskDelay(pdMS_TO_TICKS(15));
    scmd(0x06); 
    vTaskDelay(pdMS_TO_TICKS(2));
}

void lcd_print(const char *str) {
    while (*str) {
        sdata(*str++);
    }
}
void lcd_printint(uint8_t val) {
   sdata(val);
   printf("value%d\n",val);
}

void lcd_create_char(uint8_t location, uint8_t charmap[]) {
    location &= 0x07; 
    scmd(0x40 | (location << 3));
    for (uint8_t i = 0; i < 8; i++) {
        sdata(charmap[i]);
    }
}
