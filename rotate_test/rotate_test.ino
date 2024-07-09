volatile long encoderCount = 0; // 編碼器計數值
volatile int lastEncoded = 0; // 上一次編碼器的狀態

int en_A1   = 4;
int in_A1_1 = 24;
int in_A1_2 = 26;

double Kp = 0.52; // 比例係數
double Ki = 0.015385; // 積分係數
double Kd = 0; // 微分係數

// double setPoint[4] = {  0,660,1343,1993}; // 目標位置
double setPoint = 0;
double input, output;
double lastInput;
double integral;
int i=0;

void setup() {
  pinMode(en_A1, OUTPUT);
  pinMode(in_A1_1, OUTPUT);
  pinMode(in_A1_2, OUTPUT);

  Serial.begin(115200); // 初始化串口通信
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
  // 在主循環中可以讀取並處理編碼器計數值
  // Serial.println("請輸入桶子");
  
  if (Serial.available()){
    char ch =Serial.read();
    if (ch=='1'){
      setPoint = 0;
    }
    else if(ch=='2'){
      setPoint = 672;
    }
    else if(ch=='3'){
      setPoint = 1313;
    }
    else if(ch=='4'){
      setPoint = 1993;
    }
  }
  Serial.println(setPoint);
  input = encoderCount;
  double error = setPoint - input;
  integral += error;
  double derivative = input - lastInput;

  // PID計算
  output = Kp * error + Ki * integral - Kd * derivative;

  // 控制馬達
  if (abs(error) < 10) { // 如果误差在10以内，停止电机
    analogWrite(en_A1, 0); 
    digitalWrite(in_A1_1, LOW);
    digitalWrite(in_A1_2, LOW);
  } else if (output > 0) {
    digitalWrite(in_A1_1, LOW);
    digitalWrite(in_A1_2, HIGH);
  } else {
    digitalWrite(in_A1_1, HIGH);
    digitalWrite(in_A1_2, LOW);
    output = -output; // 确保PWM值为正
  }

  // 限制輸出到0-255之間
  output = constrain(output, 0, 255);
  analogWrite(en_A1, output);

  lastInput = input;

  // 打印當前的計數值和控制輸出
  Serial.print("Encoder Count: ");
  Serial.print(encoderCount);
  Serial.print(" Output: ");
  Serial.println(output);

  delay(100);
}

void updateEncoder() {
  int MSB = digitalRead(2); // 讀取引腳2的狀態
  int LSB = digitalRead(3); // 讀取引腳3的狀態

  int encoded = (MSB << 1) | LSB; // 組合當前的A和B信號狀態
  int sum = (lastEncoded << 2) | encoded; // 組合當前和上一次的狀態

  // 根據狀態變化更新編碼器計數值
  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) encoderCount++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) encoderCount--;

  lastEncoded = encoded; // 更新上一次的編碼器狀態
}
