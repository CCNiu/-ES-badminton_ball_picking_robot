#include <Servo.h>

Servo SG90;
Servo MG996R;

void setup() {
  Serial.begin(115200);         // 初始化默认串行端口
  SG90.attach(9);               // 将SG90伺服连接到引脚9
  MG996R.attach(10);            // 将MG996R伺服连接到引脚10
  MG996R.write(0);              // 将MG996R初始化到0度
  SG90.write(150);              // 将SG90初始化到150度
}

void loop() {
  Serial.println("輸入角度 1 和 2");
  delay(100);
  if (Serial.available()) {
    finger_test();
  }
}

void finger_test() {
  String input = readSerialInput();  // 读取整个输入行
  if (input.length() > 0) {
    int angles[2] = { -1, -1 };  // 初始化数组以存储角度
    parseAngles(input, angles);  // 从输入字符串中解析角度

    if (angles[0] >= 0 && angles[0] <= 180) { // 确保第一个角度在有效范围内
      MG996R.write(angles[0]);
      delay(100); 
    }

    if (angles[1] >= 0 && angles[1] <= 180) { // 确保第二个角度在有效范围内
      SG90.write(angles[1]);
    }
  }
}

String readSerialInput() {
  String input = "";
  while (Serial.available()) {
    char ch = Serial.read();
    if (ch == '\n') {
      break;  // 遇到换行符时退出循环
    } else {
      input += ch;
    }
  }
  return input;  // 返回输入字符串
}

void parseAngles(String input, int* angles) {
  int index = 0;
  String angle = "";
  for (int i = 0; i < input.length() && index < 2; i++) {
    if (isDigit(input[i])) {
      angle += input[i];
    } else if (input[i] == ' ' || input[i] == ',') {
      if (angle.length() > 0) {
        angles[index++] = angle.toInt();
        angle = "";
      }
    }
  }
  if (angle.length() > 0 && index < 2) {
    angles[index] = angle.toInt();  // 解析最后一个角度（如果有）
  }
}
