#include <Servo.h>
Servo SG90; 
Servo MG996R; 
int angle_MG996R[16] = {  0,  0, 10, 20, 40, 60, 80,100,110,120,130,140,130,120,110,100};
int angle_SG90[16] = {  180,170,160,160,160,140,120,105, 95, 80, 75, 70, 75, 80, 95,105};


void setup() {
  // put your setup code here, to run once:
   // put your setup code here, to run once:
  // Serial.begin();
  SG90.attach(9);
  MG996R.attach(10);
  MG996R.write(0);   
  SG90.write(175);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<16; i++){
    MG996R.write(angle_MG996R[i]);   
    SG90.write(angle_SG90[i]);   
    delay(150); 
    }
  for(int i=16; i>0; i--){
    MG996R.write(angle_MG996R[i-1]);   
    SG90.write(angle_SG90[i-1]);   
    delay(50); 
  }
}
