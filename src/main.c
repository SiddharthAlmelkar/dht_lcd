#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "dht11.h"
#include "lcd.h"
int pin =23;
char valhum[16];
char valtemp[16];
void app_main(void)
{

   inp(pin);
   lcd_init(); 
   uint8_t humint,humdec,tempint,tempdec;


    while (true) {
        
        
        data(&humint,&humdec,&tempint,&tempdec); 
        
            
    
    sprintf(valhum,"Damp:%d.%d",humint,humdec);
    sprintf(valtemp,"Temp:%d.%d",tempint,tempdec);
    

    scmd(0x80);
    lcd_print(valhum);
    lcd_print("%");
    scmd(0xC0);

    lcd_print(valtemp);
    lcd_print("C");

        
    
    
    vTaskDelay(pdMS_TO_TICKS(200));

    

    
}
}