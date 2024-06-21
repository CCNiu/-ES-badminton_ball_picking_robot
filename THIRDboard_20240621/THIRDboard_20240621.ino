#include <Servo.h>
#include <SoftwareSerial.h>

int spd = 150;  //PWM 輸出，0~255
char command;
unsigned long Timer1;
unsigned long Timer2;
Servo SG90; 
Servo MG996R; 


int angle_MG996R[16] = {  0,40,60,80,100,110,120,130,140,150,155,160,165,170,175,180};
int angle_SG90[16] = {  150,180,180,180,180,178,173,165,150,145,140,135,130,128,125,120};

char cmd='0';
char last_cmd='0';

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  if(ball_counter<12){
    if(球頭被掃到){
      紀錄雷射斷開時間
      Timer1 = millis();
      回傳給主控
      finger();
      delay(1000);// delay看會不會滑出來
      if (雷射恢復){
        timer2 = millis();//回傳雷射恢復時間
        //收time = Timer2 - Timer1;
      }
      else{
        finger();
      }
      // while(收time>regular time){
      //   紀錄時間
      //   finger;
      //   紀錄時間
      //   計算收time
      //}
      回傳收完
      ball_counter++;
    }
    else{
      rotate_bucket();//旋轉球桶
    }
  }
}

//收球
void finger(){
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

void rotate_bucket(){

}