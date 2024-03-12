#include <Servo.h>

Servo SG90; 
Servo MG996R; 

int angle_MG996R[16] = {  0,40,60,80,100,110,120,130,140,150,155,160,165,170,175,180};
int angle_SG90[16] = {  150,180,180,180,180,178,173,165,150,145,140,135,130,128,125,120};

int angle_MG996R11[16] = {  0,40,60,80,100,110,120,130,140,150,155,160,165,160,160,180};
int angle_SG9011[16] = {  150,160,170,180,180,178,173,165,150,140,130,130,125,120,120,120};
char cmd='0';
char last_cmd='0';

void setup() {
  // put your setup code here, to run once:
  SG90.attach(9);
  MG996R.attach(11);
  Serial.begin(9600);
  MG996R.write(0);   
  SG90.write(150);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    last_cmd = cmd;
    cmd = Serial.read();   
    //Serial.println(cmd);
    //Serial.println(last_cmd);

    if(cmd =='1'&& cmd!=last_cmd){
        Serial.println("in");
        for(int i=0; i<16; i++){
          MG996R.write(angle_MG996R[i]);   
          SG90.write(angle_SG90[i]);   
          delay(100); 
        }
      }
      else if(cmd =='0'&&cmd!=last_cmd){
        Serial.println("out");
        for(int i=16; i>0; i--){
          MG996R.write(angle_MG996R[i-1]);   
          SG90.write(angle_SG90[i-1]);   
          delay(50); 
        }
    }
  }
  
  
}
