// const int LED = 6;
int anaPin = A2;
int anaValue = 0;
void setup() {
  Serial.begin(115200);
  // put your setup code here, to run once:
  pinMode(7,OUTPUT);
  // pinMode(6,OUTPUT);
  // pinMode(8,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);  // 打開鐳射頭
  anaValue = analogRead(anaPin);   //讀取類比輸入的值會得到0~1023
  Serial.println(anaValue);
  //sensorValue = map(sensorValue,0,1023,0,255);  //將0~1023轉化成0~255
  delay(1000);           
}
