#include <Servo.h>

Servo servo0 , servo1 , servo2;

unsigned long timer1 = millis(); // delay = 15
unsigned long timer2 = millis();
unsigned long timer3 = millis();

int servo0pin = A0;
int servo1pin = A1;
int servo2pin = A2;

int val0;
int val1;
int val2;

int pre_vr0 = 0;
int pre_vr1 = 0;
int pre_vr2 = 0;

bool vr0_update = false;
bool vr1_update = false;
bool vr2_update = false;

void setup() {
  servosetup();
  Serial.begin(9600);
}

void loop() {
  tolerance_vr(1);
  servo0write(180,0,15);
  servo1write(180,0,15);
}

void servosetup(){
  servo0.attach(9);
  servo1.attach(10);
  servo2.attach(11);
}

void tolerance_vr(int tolerance){
      
    val0 = map(analogRead(servo0pin), 0, 1023, 0, 180);  // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
    val1 = map(analogRead(servo1pin), 0, 1023, 0, 180);
    val2 = map(analogRead(servo2pin), 0, 1023, 0, 180);
    
    Serial.print("val0 = ");           
    Serial.print(val0);              // พิมพ์ค่าของตัวแปร val
    Serial.print("      val1 = ");           
    Serial.println(val1);              // พิมพ์ค่าของตัวแปร val

    if ((val0  >  pre_vr0 + tolerance)
      || (val0 <  pre_vr0 - tolerance)) {
    vr0_update = true;
    pre_vr0 = val0;
  }
  
  if ((val1  >  pre_vr1 + tolerance)
      || (val1 <  pre_vr1 - tolerance)) {
    vr1_update = true;
    pre_vr1 = val1;
  }
  
  if ((val2  >  pre_vr2 + tolerance)
      || (val2 <  pre_vr2 - tolerance)) {
    vr2_update = true;
    pre_vr2 = val2;
  }
}

void servo0write(int maximum0 , int minimum0 , int delay_0){
  if (vr0_update == true  && pre_vr0 < maximum0 && pre_vr0 > minimum0 ){
    if(millis() - timer1 >= delay_0){
      servo0.write(val0);               // นำค่าที่แปลงค่ามาจากตัวต้านทานรับค่าได้ มาควบคุมการหมุน Servo
      timer1 = millis();
  }
  }
}
  
void servo1write(int maximum1 , int minimum1 , int delay_1){
  if (vr1_update == true  && pre_vr1 < maximum1 && pre_vr1 > minimum1 ){
    if(millis() - timer2 >= delay_1){
      servo1.write(val1);               // นำค่าที่แปลงค่ามาจากตัวต้านทานรับค่าได้ มาควบคุมการหมุน Servo
      timer2 = millis();
  }
  }
}

void servo2write(int maximum2 , int minimum2 , int delay_2){
  if (vr2_update == true  && pre_vr2 < maximum2 && pre_vr2 > minimum2 ){
    if(millis() - timer3 >= delay_2){
      servo2.write(val2);               // นำค่าที่แปลงค่ามาจากตัวต้านทานรับค่าได้ มาควบคุมการหมุน Servo
      timer3 = millis();
  }
  }
}
