//定义引脚
#define L1 A0   //左1
#define L2 A1   //左2
#define M A2    //中间
#define R1 A3   //右1
#define R2 A4   //右2
#define ENA 11  //左电机输入
#define ENB 10  //右电机输入
#define IN1 9   //左电机正转
#define IN2 8   //左电机反转
#define IN3 7   //右电机正转
#define IN4 6   //右电机反转

int Left_motor_go = 8;    //左电机前进 AIN1
int Left_motor_back = 7;  //左电机后退 AIN2

int Right_motor_go = 2;    //右电机前进 BIN1
int Right_motor_back = 4;  //右电机后退 BIN2

int Left_motor_pwm = 6;   //左电机控速 PWMA
int Right_motor_pwm = 5;  //右电机控速 PWMB

const int TrackSensorLeftPin1 = A1;   //定义左边第一个循迹红外传感器引脚为A1
const int TrackSensorLeftPin2 = A2;   //定义左边第二个循迹红外传感器引脚为A2
const int TrackSensorRightPin1 = A3;  //定义右边第一个循迹红外传感器引脚为A3
const int TrackSensorRightPin2 = A4;  //定义右边第二个循迹红外传感器引脚为A4
const int TrackSensorcenterPin = A5;  //定义中间循迹红外传感器引脚为A5

//定义各个循迹红外引脚采集的数据的变量
int TrackSensorLeftValue1;
int TrackSensorLeftValue2;
int TrackSensorRightValue1;
int TrackSensorRightValue2;
int TrackSensorcenter;

void setup() {
  // 将所有电机控制引脚设置为输出
  pinMode(Left_motor_go, OUTPUT);
  pinMode(Left_motor_back, OUTPUT);
  pinMode(Right_motor_go, OUTPUT);
  pinMode(Right_motor_back, OUTPUT);

  //定义5路循迹传感器为输入接口
  pinMode(TrackSensorLeftPin1, INPUT);
  pinMode(TrackSensorLeftPin2, INPUT);
  pinMode(TrackSensorRightPin1, INPUT);
  pinMode(TrackSensorRightPin2, INPUT);
  pinMode(TrackSensorcenter, INPUT);

  // 关闭电机 定义初始状态
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);

  //初始化5路寻迹模块为高电平
  //灯灭为高电平
  digitalWrite(TrackSensorLeftPin1, HIGH);
  digitalWrite(TrackSensorLeftPin2, HIGH);
  digitalWrite(TrackSensorRightPin1, HIGH);
  digitalWrite(TrackSensorRightPin2, HIGH);
  digitalWrite(TrackSensorcenter, HIGH);
}

//小车前进
void forward(int left_speed, int right_speed) {
  digitalWrite(Left_motor_go, HIGH);
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_pwm, left_speed);
  digitalWrite(Right_motor_go, HIGH);
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_pwm, right_speed);
}

//小车停止
void stop() {
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, LOW);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, LOW);
}

//小车后退
void backward(int left_speed, int right_speed) {
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_pwm, left_speed);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_pwm, right_speed);
}

//小车左转
void left(int left_speed, int right_speed) {
  digitalWrite(Left_motor_go, LOW);
  digitalWrite(Left_motor_back, HIGH);
  analogWrite(Left_motor_pwm, left_speed);
  digitalWrite(Right_motor_go, HIGH);
  digitalWrite(Right_motor_back, LOW);
  analogWrite(Right_motor_pwm, right_speed);
}

//小车右转
void right(int left_speed, int right_speed) {
  digitalWrite(Left_motor_go, HIGH);
  digitalWrite(Left_motor_back, LOW);
  analogWrite(Left_motor_pwm, left_speed);
  digitalWrite(Right_motor_go, LOW);
  digitalWrite(Right_motor_back, HIGH);
  analogWrite(Right_motor_pwm, right_speed);
}

void loop() {
  //读取灰度传感器数据
  int TrackSensorLeftValue1 = digitalRead(TrackSensorLeftPin1);
  int TrackSensorLeftValue2 = digitalRead(TrackSensorLeftPin2);
  int TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
  int TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
  int TrackSensorcenterValue = digitalRead(TrackSensorcenter);

  //如果中间传感器检测到白色区域，小车直行
  if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == LOW && TrackSensorcenterValue == HIGH) {
    forward(250, 250);
  }
  //如果左边传感器检测到黑线，小车向左转
  else if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == LOW && TrackSensorcenterValue == HIGH) {
    left(200, 250);
  }
  //如果右边传感器检测到黑线，小车向右转
  else if (TrackSensorRightValue1 == HIGH && TrackSensorRightValue2 == LOW && TrackSensorcenterValue == HIGH) {
    right(250, 200);
  }
  //如果小车偏离黑线，则小车右转
  else {
    right(250, 200);
  }
}
