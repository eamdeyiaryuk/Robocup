#include <Servo.h>

Servo servo0 , servo1 , servo2;

unsigned long timer1 = millis();
unsigned long timer2 = millis();
unsigned long timer3 = millis();

int servo0pin = 0;
int servo1pin = 1;
int servo2pin = 2;

int val0;
int val1;
int val2;

int pre_vr0;
int pre_vr1;
int pre_vr2;

bool vr0_update = false;
bool vr1_update = false;
bool vr2_update = false;

void setup() {
  servosetup();
  Serial.begin(9600);
}

void loop() {
  tolerance_vr(1);
  servo0write(180,50,15);

}
void servosetup(){
  servo0.attach(9);
}

void tolerance_vr(int tolerance){
  
    val0 = analogRead(servo0pin);         // อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
    val1 = analogRead(servo0pin);
    val2 = analogRead(servo0pin);
    
    val0 = map(val0, 0, 1023, 0, 180);  // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
    val1 = map(val0, 0, 1023, 0, 180);
    val2 = map(val0, 0, 1023, 0, 180);
    
//    Serial.print("val0 = ");           
//    Serial.println(val0);              // พิมพ์ค่าของตัวแปร val

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
  if (vr1_update == true  && pre_vr0 < maximum1 && pre_vr0 > minimum1 ){
    if(millis() - timer2 >= delay_1){
      servo0.write(val1);               // นำค่าที่แปลงค่ามาจากตัวต้านทานรับค่าได้ มาควบคุมการหมุน Servo
      timer2 = millis();
  }
  }
}

void servo2write(int maximum2 , int minimum2 , int delay_2){
  if (vr2_update == true  && pre_vr0 < maximum2 && pre_vr0 > minimum2 ){
    if(millis() - timer3 >= delay_2){
      servo0.write(val2);               // นำค่าที่แปลงค่ามาจากตัวต้านทานรับค่าได้ มาควบคุมการหมุน Servo
      timer3 = millis();
  }
  }
}
