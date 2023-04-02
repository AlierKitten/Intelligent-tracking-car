//寻迹小车

//定义L298N链接的针脚
//M1 motor
int Left_motor_go = 2;//in1
int Left_motor_back = 3;//in2
int Left_motor_pwm = 6;//enA
//M2 motor
int Right_motor_go = 4;//in3
int Right_motor_back = 5;//in4
int Right_motor_pw = 7;//enB

//定义5路灰度模块
const int TrackSensorLeftPin1  =  A1;  //定义左边第一个循迹红外传感器引脚为A1
const int TrackSensorLeftPin2  =  A2;  //定义左边第二个循迹红外传感器引脚为A2
const int TrackSensorRightPin1 =  A3;  //定义右边第一个循迹红外传感器引脚为A3
const int TrackSensorRightPin2 =  A4;  //定义右边第二个循迹红外传感器引脚为A4
const int TrackSensorcenterPin =  A5;  //定义中间循迹红外传感器引脚为A5

//定义各个循迹红外引脚采集的数据的变量
int TrackSensorLeftValue1;
int TrackSensorLeftValue2;
int TrackSensorRightValue1;
int TrackSensorRightValue2;
int TrackSensorcenter;

void setup() 
{
	// 将所有电机控制引脚设置为输出
	pinMode(Left_motor_go, OUTPUT);
	pinMode(Left_motor_back, OUTPUT);
	pinMode(Right_motor_go, OUTPUT);
	pinMode(Right_motor_back, OUTPUT);
	
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
void run(int left_speed, int right_speed)
{
    //左电机前进
    digitalWrite(Left_motor_go, HIGH);   //左电机前进使能
    digitalWrite(Left_motor_back, LOW);  //左电机后退禁止

    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
}

//小车停止 延时100ms
void brake(int time)
{
    digitalWrite(Left_motor_go, LOW);
    digitalWrite(Left_motor_back, LOW);
    digitalWrite(Right_motor_go, LOW);
    digitalWrite(Right_motor_back, LOW);

    delay(time * 100);
}

//小车左转（小转
void left(int left_speed, int right_speed)
{
    //左电机停止
    digitalWrite(Left_motor_go, LOW);    //左电机前进禁止
    digitalWrite(Left_motor_back, LOW);  //左电机后退禁止

    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
}

//小车右转（小转
void right(int left_speed, int right_speed)
{
  //左电机前进
    digitalWrite(Left_motor_go, HIGH);   //左电机前进使能
    digitalWrite(Left_motor_back, LOW);  //左电机后退禁止

  //右电机停止
    digitalWrite(Right_motor_go, LOW);   //右电机前进禁止
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
}

//小车左转（原地
void spin_left(int left_speed, int right_speed)
{
    //左电机后退
    digitalWrite(Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Left_motor_back, HIGH);  //左电机后退使能

    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
}

//小车右转（原地
void spin_right(int left_speed, int right_speed)
{
  //左电机前进
    digitalWrite(Left_motor_go, HIGH);    //左电机前进使能
    digitalWrite(Left_motor_back, LOW);   //左电机后退禁止

    //右电机后退
    digitalWrite(Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Right_motor_back, HIGH); //右电机后退使能
}

//小车后退
void back(int time)
{
    //左电机后退
    digitalWrite(Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Left_motor_back, HIGH);  //左电机后退使能

    //右电机后退
    digitalWrite(Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Right_motor_back, HIGH); //右电机后退使能

    delay(time *100);
}

void loop()
{
    //定义状态
    //检测到黑线时循迹模块相应的指示灯灭，端口电平为HIGH
    //未检测到黑线时循迹模块相应的指示灯亮，端口电平为LOW
    TrackSensorLeftValue1  = digitalRead(TrackSensorLeftPin1);
    TrackSensorLeftValue2  = digitalRead(TrackSensorLeftPin2);
    TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
    TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
    TrackSensorcenter = digitalRead(TrackSensorcenter);

    //逻辑判断

}