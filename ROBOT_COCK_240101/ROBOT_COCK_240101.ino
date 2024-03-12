#include <Servo.h>
#include <SoftwareSerial.h>

//左前
int en_A1   = 13;      //接前面驅動版的ENA
int in_A1_1 = 12;      //接前面驅動版的IN1
int in_A1_2 = 11;      //接前面驅動版的IN2

//右前
int en_B1   = 10;      //接前面驅動版的ENB
int in_B1_3 = 9;       //接前面驅動版的IN3
int in_B1_4 = 8;       //接前面驅動版的IN4

//左後
int en_A2   = 7;       //接後面驅動版的ENA
int in_A2_1 = 6;       //接後面驅動版的IN1
int in_A2_2 = 5;       //接後面驅動版的IN2

//右後
int en_B2   = 4;       //接後面驅動版的ENB
int in_B2_3 = 3;       //接後面驅動版的IN3
int in_B2_4 = 2;       //接後面驅動版的IN4

int spd = 150;  //PWM 輸出，0~255

char command;

Servo SG90; 
Servo MG996R; 

int angle_MG996R[16] = {  0,40,60,80,100,110,120,130,140,150,155,160,165,170,175,180};
int angle_SG90[16] = {  150,180,180,180,180,178,173,165,150,145,140,135,130,128,125,120};

int angle_MG996R11[16] = {  0,40,60,80,100,110,120,130,140,150,155,160,165,160,160,180};
int angle_SG9011[16] = {  150,160,170,180,180,178,173,165,150,140,130,130,125,120,120,120};
char cmd='0';
char last_cmd='0';

void setup() {

  pinMode(en_A1, OUTPUT);
  pinMode(en_B1, OUTPUT);
  pinMode(in_A1_1, OUTPUT);
  pinMode(in_A1_2, OUTPUT);
  pinMode(in_B1_3, OUTPUT);
  pinMode(in_B1_4, OUTPUT);
  pinMode(en_A2, OUTPUT);
  pinMode(en_B2, OUTPUT);
  pinMode(in_A2_1, OUTPUT);
  pinMode(in_A2_2, OUTPUT);
  pinMode(in_B2_3, OUTPUT);
  pinMode(in_B2_4, OUTPUT);
  Serial.begin(115200);//序列框鮑率
  Serial1.begin(38400);//藍芽鮑率
  SG90.attach(22);
  MG996R.attach(24);
  MG996R.write(0);   
  SG90.write(150);
}

void loop() {
  if (Serial1.available()){
    command = Serial1.read();
    Serial.println( command );
    delay(20);
  }
  switch ( command ){
    case 'A' ://左前
      left_front();
      break;
    case 'B' ://前
      forward();
      break;
    case 'C' ://右前
      right_front();
      break;
    case 'D' ://左
      left();
      break;
    case 'E' ://停
      stop();
      break;
    case 'F' ://右
      right();
      break;
    case 'G' ://左後
      left_back();
      break;
    case 'H' ://後
      backward();
      break;
    case 'I' ://右後
      right_back();
      break;
    case 'J' ://順時針轉
      cclw();
      break;
    case 'K' ://逆時針轉
      clw();
      break;
    case 'L' ://手指 啟動!
      finger();
      break;
    case 'M' ://shotdown!

      break;
  }
  //forward();
  //delay(10000);
  //backward();
  //delay(10000);
  //left();
  //delay(10000);
  //right();
  //delay(10000);


}

void stop() {                   // 停止
  analogWrite(en_A1, 0);        // 馬達A1 的 PWM 輸出
  analogWrite(en_B1, 0);        // 馬達B1 的 PWM 輸出
  analogWrite(en_A2, 0);        // 馬達A2 的 PWM 輸出
  analogWrite(en_B2, 0);        // 馬達B2 的 PWM 輸出
  digitalWrite(in_A1_1, LOW);
  digitalWrite(in_A1_2, LOW);
  digitalWrite(in_B1_3, LOW);
  digitalWrite(in_B1_4, LOW);
  digitalWrite(in_A2_1, LOW);
  digitalWrite(in_A2_2, LOW);
  digitalWrite(in_B2_3, LOW);
  digitalWrite(in_B2_4, LOW);
}

void forward() {                // 前進
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, LOW);
digitalWrite(in_A1_2, HIGH);
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, HIGH);
digitalWrite(in_B1_4, LOW);
analogWrite(en_A2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_A2_1, LOW);
digitalWrite(in_A2_2, HIGH);
analogWrite(en_B2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_B2_3, HIGH);
digitalWrite(in_B2_4, LOW);
}

void backward() {               // 後退
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, HIGH);
digitalWrite(in_A1_2, LOW);
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, LOW);
digitalWrite(in_B1_4, HIGH);
analogWrite(en_A2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_A2_1, HIGH);
digitalWrite(in_A2_2, LOW);
analogWrite(en_B2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_B2_3, LOW);
digitalWrite(in_B2_4, HIGH);
}

void left() {                   // 左移
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, HIGH);
digitalWrite(in_A1_2, LOW);
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, HIGH);
digitalWrite(in_B1_4, LOW);
analogWrite(en_A2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_A2_1, LOW);
digitalWrite(in_A2_2, HIGH);
analogWrite(en_B2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_B2_3, LOW);
digitalWrite(in_B2_4, HIGH);
}

void right() {                  // 右移
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, LOW);
digitalWrite(in_A1_2, HIGH);
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, LOW);
digitalWrite(in_B1_4, HIGH);
analogWrite(en_A2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_A2_1, HIGH);
digitalWrite(in_A2_2, LOW);
analogWrite(en_B2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_B2_3, HIGH);
digitalWrite(in_B2_4, LOW);
}

void left_front() {             // 左前
analogWrite(en_A1, 0);          // 馬達A1 的 PWM 輸出
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, HIGH);
digitalWrite(in_B1_4, LOW);
analogWrite(en_B2, 0);          // 馬達A2 的 PWM 輸出
analogWrite(en_A2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_A2_1, LOW);
digitalWrite(in_A2_2, HIGH);
}

void left_back() {              // 左後
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, HIGH);
digitalWrite(in_A1_2, LOW);
analogWrite(en_B1, 0);          // 馬達B1 的 PWM 輸出
analogWrite(en_B2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_B2_3, LOW);
digitalWrite(in_B2_4, HIGH);
analogWrite(en_A2, 0);          // 馬達B2 的 PWM 輸出
}

void right_front() {            // 右前
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, LOW);
digitalWrite(in_A1_2, HIGH);
analogWrite(en_B1, 0);          // 馬達B1 的 PWM 輸出
analogWrite(en_B2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_B2_3, HIGH);
digitalWrite(in_B2_4, LOW);
analogWrite(en_A2, 0);          // 馬達B2 的 PWM 輸出
}

void right_back() {             // 右後
analogWrite(en_A1, 0);          // 馬達A1 的 PWM 輸出
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, LOW);
digitalWrite(in_B1_4, HIGH);
analogWrite(en_B2, 0);          // 馬達A2 的 PWM 輸出
analogWrite(en_A2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_A2_1, HIGH);
digitalWrite(in_A2_2, LOW);
}

void clw() {                    // 順時轉
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, LOW);
digitalWrite(in_A1_2, HIGH);
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, LOW);
digitalWrite(in_B1_4, HIGH);
analogWrite(en_A2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_A2_1, LOW);
digitalWrite(in_A2_2, HIGH);
analogWrite(en_B2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_B2_3, LOW);
digitalWrite(in_B2_4, HIGH);
}

void cclw() {                   // 逆時轉
analogWrite(en_A1, spd);        // 馬達A1 的 PWM 輸出
digitalWrite(in_A1_1, HIGH);
digitalWrite(in_A1_2, LOW);
analogWrite(en_B1, spd);        // 馬達B1 的 PWM 輸出
digitalWrite(in_B1_3, HIGH);
digitalWrite(in_B1_4, LOW);
analogWrite(en_A2, spd);        // 馬達A2 的 PWM 輸出
digitalWrite(in_A2_1, HIGH);
digitalWrite(in_A2_2, LOW);
analogWrite(en_B2, spd);        // 馬達B2 的 PWM 輸出
digitalWrite(in_B2_3, HIGH);
digitalWrite(in_B2_4, LOW);
}

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
