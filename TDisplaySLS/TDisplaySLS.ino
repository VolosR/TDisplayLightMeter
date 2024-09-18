#include "LV_Helper.h"
#include <ESP32Time.h>  // https://github.com/fbiego/ESP32Time  verison 2.0.6
#include "ui.h"

#define ledPin 21
ESP32Time rtc(0);

void setup() {

    pinMode(0,INPUT_PULLUP);
    pinMode(14,INPUT_PULLUP);

    pinMode(ledPin,OUTPUT);
    pinMode(15,OUTPUT);
    digitalWrite(15,1);

   
    Serial.begin(115200);
    Serial.println("Lets Start");

    rtc.setTime(0, 0, 0, 17, 1, 2021); 

    lv_helper();
    ui_init();

    analogWrite(38,120);

}

int number=0;
int deb1=0;
int deb2=0;
bool output=1;

void loop() {
int light_value=map(analogRead(10),0,4095,100,0);
int sound_value=map(analogRead(11),0,2095,0,100);
 _ui_label_set_property(ui_numberLBL, _UI_LABEL_PROPERTY_TEXT, String(light_value).c_str());
 _ui_label_set_property(ui_batLBL, _UI_LABEL_PROPERTY_TEXT, String(sound_value*3).c_str());
 _ui_label_set_property(ui_timeLBL, _UI_LABEL_PROPERTY_TEXT, rtc.getTime().substring(0,5).c_str());
 _ui_label_set_property(ui_secLBL, _UI_LABEL_PROPERTY_TEXT, rtc.getTime().substring(6,8).c_str());
 lv_arc_set_value(ui_Arc1, light_value); 
 lv_arc_set_value(ui_Arc2, sound_value*3); 



 if(digitalRead(14)==0)
  {
    if(deb2==0)
      {
        deb2=1;
        output=!output;

        digitalWrite(ledPin,output);

        lv_obj_add_state(ui_Button2, LV_STATE_PRESSED);
        if(!output)
        lv_obj_add_flag(ui_Panel11, LV_OBJ_FLAG_HIDDEN);
        else
        lv_obj_clear_flag(ui_Panel11, LV_OBJ_FLAG_HIDDEN);
      }
  }else
  { deb2=0;
  lv_obj_clear_state(ui_Button2, LV_STATE_PRESSED);
  }


 lv_task_handler();
 delay(5);
}