#include <Servo.h>
#include <SoftwareSerial.h>

// char command;

Servo SG90; 
Servo MG996R; 
int ball_counter=8;

int angle_MG996R[16] = {  0,  0, 10, 20, 40, 60, 80,100,110,120,130,140,130,120,110,100};
int angle_SG90[16] = {  180,170,160,160,160,140,120,105, 95, 80, 75, 70, 75, 80, 95,105};

int anaPin = A2;
int anaValue = 0;
int laser = 7;

volatile long encoderCount = 0; // 編碼器計數值
volatile int lastEncoded = 0; // 上一次編碼器的狀態

int en_A1   = 4;
int in_A1_1 = 24;
int in_A1_2 = 26;

double Kp = 0.3; // 比例係數0.52
double Ki = 0.0001; // 積分係數
double Kd = 0; // 微分係數

double setPoint = 0;
double input, output;
double lastInput;
double integral;
int bucket_NUM=0;
// int bucket_number=0;

void setup() {
  // put your setup code here, to run once:
  //finger
  Serial.begin(115200);
  SG90.attach(9);
  MG996R.attach(10);
  MG996R.write(0);   
  SG90.write(175);
  delay(500); // 等待馬達到達初始位置
  //Laser
  pinMode(laser,OUTPUT);
  digitalWrite(laser, HIGH); 
  //UART
  Serial1.begin(9600);
  //ROTATe
  pinMode(en_A1, OUTPUT);
  pinMode(in_A1_1, OUTPUT);
  pinMode(in_A1_2, OUTPUT);

  Serial.begin(115200); // 初始化串口通信bn
  pinMode(2, INPUT); // 設置引腳2為輸入
  pinMode(3, INPUT); // 設置引腳3為輸入

  // 啟用外部中斷，檢測引腳2和3的變化
  attachInterrupt(digitalPinToInterrupt(2), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), updateEncoder, CHANGE);

  // 初始化馬達停止
  analogWrite(en_A1, 0); 
  digitalWrite(in_A1_1, LOW);
  digitalWrite(in_A1_2, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(ball_counter<12){
    anaValue = analogRead(anaPin);
    delay(100);
    Serial.print("laser value is: ");
    Serial.println(anaValue);

    if(anaValue <= 250){
      Serial1.write(0x01);
      finger();
      delay(1000);  // delay看會不會滑出來

      if (anaValue >= 250){
        Serial1.write(0x02);
      }
      else{
        finger();
        delay(100);
        Serial1.write(0x02);
      }
      ball_counter++;
    }
  }
  else{
    ball_counter=0;
    if (bucket_NUM < 3){
      bucket_NUM++;
      rotate_bucket(bucket_NUM);//旋轉球桶
      Serial.println("BUCKET+1");
      delay(1000);
    }
    else{
      Serial.println("滿了你這87");
    }
  
  }
  Serial.println(ball_counter);
}

//收球
void finger(){
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
  Serial.println("finger check");
}

void updateEncoder(){
  int MSB = digitalRead(2); // 讀取引腳2的狀態
  int LSB = digitalRead(3); // 讀取引腳3的狀態

  int encoded = (MSB << 1) | LSB; // 組合當前的A和B信號狀態
  int sum = (lastEncoded << 2) | encoded; // 組合當前和上一次的狀態

  // 根據狀態變化更新編碼器計數值
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderCount++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderCount--;

  lastEncoded = encoded; // 更新上一次的編碼器狀態
}

void rotate_bucket(int bucket_number) {
  // 更新目标位置（setPoint）以旋转桶
  switch (bucket_number) {
    case 0:
      setPoint = 0;
      break;
    case 1:
      setPoint = 672;
      break;
    case 2:
      setPoint = 1313;
      break;
    case 3:
      setPoint = 1993;
      break;
    default:
      Serial.println("无效的桶号");
      return;
  }
        Serial.println("1");

  


  input = encoderCount;
  lastInput=0;
  double error = setPoint - input;
  double derivative = error;

  Serial.println(error);
  Serial.println(derivative);
  while(abs(error)>25||abs(derivative)>5){

    lastInput = input;
     // 更新PID控制器
  input = encoderCount;
  error = setPoint - input;
  integral += error;
  derivative = input - lastInput;

  // PID计算
  output = Kp * error + Ki * integral - Kd * derivative;

  // 控制馬達
        Serial.println("2");

  if (output > 0) {
    digitalWrite(in_A1_1, LOW);
    digitalWrite(in_A1_2, HIGH);
  } else {
    digitalWrite(in_A1_1, HIGH);
    digitalWrite(in_A1_2, LOW);
    output = -output; // 确保PWM值为正
  }

  // 限制输出到0-255之间
  output +=50;
  output = constrain(output, 0, 255);
  analogWrite(en_A1, output);

  

  // 打印当前的计数值和控制输出
  Serial.print("Encoder Count: ");
  Serial.print(encoderCount);
  Serial.print(" Output: ");
  Serial.println(output);
  Serial.println(setPoint);
  }
  analogWrite(en_A1, 0); 
  digitalWrite(in_A1_1, LOW);
  digitalWrite(in_A1_2, LOW);
  
}