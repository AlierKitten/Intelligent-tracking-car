// 引入必要的库
#include <PID_v1.h>

// 设置灰度传感器的引脚
const int sensorPin1 = A0;   // 左边的传感器
const int sensorPin2 = A1;   // 左边的中心传感器
const int sensorPin3 = A2;   // 中间的传感器
const int sensorPin4 = A3;   // 右边的中心传感器
const int sensorPin5 = A4;   // 右边的传感器

// 设置小车的马达引脚
const int leftMotor = 5;
const int rightMotor = 6;

// 设置 PID 控制参数
double kp = 1;
double ki = 0;
double kd = 0;

PID pid(&input, &output, &setpoint, kp, ki, kd, DIRECT);

// 定义灰度传感器的读数变量
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3 = 0;
int sensorValue4 = 0;
int sensorValue5 = 0;

// 定义 PID 控制使用的变量
double input, output, setpoint;
unsigned long currentTime, previousTime;
unsigned long sensorDelay = 50;

void setup() {
  // 初始化串口
  Serial.begin(9600);

  // 设置灰度传感器引脚为输入模式
  pinMode(sensorPin1, INPUT);
  pinMode(sensorPin2, INPUT);
  pinMode(sensorPin3, INPUT);
  pinMode(sensorPin4, INPUT);
  pinMode(sensorPin5, INPUT);

  // 设置马达引脚为输出模式
  pinMode(leftMotor, OUTPUT);
  pinMode(rightMotor, OUTPUT);

  // 设置 PID 控制参数
  pid.SetMode(AUTOMATIC);
  pid.SetSampleTime(20);
  pid.SetOutputLimits(-255, 255);

  // 设置小车的起始位置和期望值
  input = 0;
  output = 0;
  setpoint = 2.5;
}

void loop() {
  // 读取灰度传感器的值
  sensorValue1 = analogRead(sensorPin1);
  sensorValue2 = analogRead(sensorPin2);
  sensorValue3 = analogRead(sensorPin3);
  sensorValue4 = analogRead(sensorPin4);
  sensorValue5 = analogRead(sensorPin5);

  // 计算传感器中心的位置
  double position = (double)(sensorValue1 * 1 + sensorValue2 * 2 + sensorValue3 * 3 + sensorValue4 * 2 + sensorValue5 * 1) / (sensorValue1 + sensorValue2 + sensorValue3 + sensorValue4 + sensorValue5);

  // 将位置值放入 PID 控制器中
  pid.Compute();

  // 获取小车马达的速度
  int leftSpeed = output + 180;
  int rightSpeed = 180 - output;

  // 控制小车的马达转速
  analogWrite(leftMotor, leftSpeed);
  analogWrite(rightMotor, rightSpeed);

  // 打印一些调试信息
  Serial.print("sensor1: ");
  Serial.print(sensorValue1);
  Serial.print("  sensor2: ");
  Serial.print(sensorValue2);
  Serial.print("  sensor3: ");
  Serial.print(sensorValue3);
  Serial.print("  sensor4: ");
  Serial.print(sensorValue4);
  Serial.print("  sensor5: ");
  Serial.print(sensorValue5);
  Serial.print("  position: ");
  Serial.print(position);
  Serial.print("  output: ");
  Serial.print(output);
  Serial.print("  leftSpeed: ");
  Serial.print(leftSpeed);
  Serial.print("  rightSpeed: ");
  Serial.println(rightSpeed);

  // 等待一段时间以减缓循环速度
  delay(sensorDelay);
}

// 这个示例代码中，我们使用了 analogRead() 函数读取灰度传感器的值，
// 并使用了一个简单的加权平均来计算传感器中心的位置。
// 然后，我们将这个位置值输入到一个 PID 控制器中，并计算输出，
// 这个输出代表了左右马达的转速之间的差异。
// 最后，我们使用 analogWrite() 函数控制小车的左右马达转速以使其跟随线路。
// 请注意，这个示例代码只是代码的一部分，
// 您需要添加其他的基本功能，如前进、后退、停止等操作来完善代码。
// 同时，您还需要根据实际情况对 PID 控制参数进行调整以获得更好的表现。
// 希望这个示例代码可以帮助您开始编写自己的基于Arduino Mega 2560和5路灰度传感器的寻迹小车代码。