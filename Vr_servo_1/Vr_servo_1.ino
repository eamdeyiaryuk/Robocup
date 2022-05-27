#include <Servo.h>
Servo servo0;
int servo0pin = 0;
int val0;

unsigned long timer1 = millis();

int pre_vr0;

bool vr0_update = false;

void setup() {
  servosetup();
  Serial.begin(9600);
}

void loop() {
  tolerance_vr(1);
  servo0write(15);

}
void servosetup(){
  servo0.attach(9);
}

void tolerance_vr(int tolerance){
  
    val0 = analogRead(servo0pin);         // อ่านค่า Analog ขาA0 เก็บไว้ในตัวแปร Val
    val0 = map(val0, 0, 1023, 0, 180);  // แปลงค่า ระหว่าง 0-1023 เป็น 0-180
    Serial.print("val0 = ");           
    Serial.println(val0);              // พิมพ์ค่าของตัวแปร val

    if ((val0  >  pre_vr0 + tolerance)
      || (val0 <  pre_vr0 - tolerance)) {
    vr0_update = true;
    pre_vr0 = val0;
  }

  
}

void servo0write(int delay_){
  if (vr0_update == true  && pre_vr0 <  100 && pre_vr0 >  80){
    if(millis() - timer1 >= delay_){
      servo0.write(val0);               // นำค่าที่แปลงค่ามาจากตัวต้านทานรับค่าได้ มาควบคุมการหมุน Servo
      timer1 = millis();
  }
  }
}
