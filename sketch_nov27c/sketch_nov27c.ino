const int clkPin = 12; //连接到CLK引脚2
const int dtPin = 13; //在DT引脚连接到引脚3
const int swPin = 14 ; //SW引脚连接到引脚4
int encoderVal = 0;
void setup()
{
  //设置clkpin，depin，swpin作为输入
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);
  Serial.begin(115200); // 初始化串行通信在9600bps
}
void loop()
{
  int change = getEncoderTurn();//
  encoderVal = encoderVal + change;
  if (digitalRead(swPin) == LOW) ////如果转动 按钮
  {
    encoderVal = 0;
  }
  Serial.println(encoderVal);
}
int getEncoderTurn(void)
{
  static int oldA = HIGH; //标志为高
  static int oldB = HIGH;
  int result = 0;
  int newA = digitalRead(clkPin);//读取旋转编码器的值
  int newB = digitalRead(dtPin);//读取旋转编码器的值
  if (newA != oldA || newB != oldB) //如果发生改变
  {
    if (oldA == HIGH && newA == LOW)
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;
  return result;
}
