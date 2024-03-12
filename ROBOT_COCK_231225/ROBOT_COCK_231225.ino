#include <Servo.h>
#include <SoftwareSerial.h>

char command;
SoftwareSerial BT(9, 10); //(接收腳,傳送腳)
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  BT.begin(9600);//藍芽鮑率
}

void loop() {
  // put your main code here, to run repeatedly:
  if (BT.available()){
    command = BT.read();
    Serial.println( command );
  }
  switch ( command ){
  
  }
}
