void setup() {
  // 初始化 Serial 用于与 PC 通信
  Serial.begin(115200);
  
  // 初始化 Serial1 用于与其他设备通信
  Serial1.begin(115200);

  // 打印初始化信息
  Serial.println("Serial1 已初始化，波特率115200");
}

void loop() {
  // // 检查是否有来自 Serial1 的数据
  // if (Serial1.available()) {
  //   char inByte = Serial1.read();
  //   // 将收到的数据通过 Serial 打印到 PC
  //   Serial.print("从 Serial1 收到数据: ");
  //   Serial.println(inByte);
  // }

  // 检查是否有来自 PC 的数据
  if (Serial.available()) {
    char outByte = Serial.read();
    // 将字符转换为字符串，然后转换为整数
    String outString = String(outByte);
    int outInt = outString.toInt();
    
    // 将收到的数据通过 Serial1 发送出去
    // Serial.print("从 Serial 发送数据到 Serial1: ");
    
  }

  Serial1.write(1);
  // 延迟以避免过于频繁地读取数据
  delay(100);
}
