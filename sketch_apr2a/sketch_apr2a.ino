//寻迹小车

//定义L298N链接的针脚
int Left_motor_go = 8;        //左电机前进 AIN1
int Left_motor_back = 7;      //左电机后退 AIN2

int Right_motor_go = 2;       //右电机前进 BIN1
int Right_motor_back = 4;     //右电机后退 BIN2

int Left_motor_pwm = 6;       //左电机控速 PWMA
int Right_motor_pwm = 5;      //右电机控速 PWMB

int key = A0;                 //定义按键为arduino的模拟口A0

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

  //定义5路循迹传感器为输入接口
  pinMode(TrackSensorLeftPin1, INPUT);
  pinMode(TrackSensorLeftPin2, INPUT);
  pinMode(TrackSensorRightPin1, INPUT);
  pinMode(TrackSensorRightPin2, INPUT);
  pinMode(TrackSensorcenter, INPUT);
	
	// 关闭电机 定义初始状态
	//digitalWrite(Left_motor_go, LOW);
	//digitalWrite(Left_motor_back, LOW);
	//digitalWrite(Right_motor_go, LOW);
	//digitalWrite(Right_motor_back, LOW);

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
    analogWrite(Left_motor_pwm, left_speed );

    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    analogWrite(Right_motor_pwm, right_speed);
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
    analogWrite(Left_motor_pwm, left_speed);

    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    analogWrite(Right_motor_pwm, right_speed);
}

//小车右转（小转
void right(int left_speed, int right_speed)
{
   //左电机前进
    digitalWrite(Left_motor_go, HIGH);   //左电机前进使能
    digitalWrite(Left_motor_back, LOW);  //左电机后退禁止
    analogWrite(Left_motor_pwm, left_speed);

   //右电机停止
    digitalWrite(Right_motor_go, LOW);   //右电机前进禁止
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    analogWrite(Right_motor_pwm, right_speed);
}

//小车左转（原地
void spin_left(int left_speed, int right_speed)
{
    //左电机后退
    digitalWrite(Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Left_motor_back, HIGH);  //左电机后退使能
    analogWrite(Left_motor_pwm, left_speed);

    //右电机前进
    digitalWrite(Right_motor_go, HIGH);  //右电机前进使能
    digitalWrite(Right_motor_back, LOW); //右电机后退禁止
    analogWrite(Right_motor_pwm, right_speed);
}

//小车右转（原地
void spin_right(int left_speed, int right_speed)
{
   //左电机前进
    digitalWrite(Left_motor_go, HIGH);    //左电机前进使能
    digitalWrite(Left_motor_back, LOW);   //左电机后退禁止
    analogWrite(Left_motor_pwm, left_speed);

    //右电机后退
    digitalWrite(Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Right_motor_back, HIGH); //右电机后退使能
    analogWrite(Right_motor_pwm, right_speed);
}

//小车后退
void back(int time)
{
    //左电机后退
    digitalWrite(Left_motor_go, LOW);     //左电机前进禁止
    digitalWrite(Left_motor_back, HIGH);  //左电机后退使能
    analogWrite(Left_motor_pwm, 40);

    //右电机后退
    digitalWrite(Right_motor_go, LOW);    //右电机前进禁止
    digitalWrite(Right_motor_back, HIGH); //右电机后退使能
    analogWrite(Right_motor_pwm, 40);

    delay(time *100);
}

void count_line(int i = 0)//记录遇到长直线
{
  if (TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 ==HIGH && TrackSensorRightValue2 ==HIGH && TrackSensorcenter == HIGH)
  {
    i++;
  }
  switch (i)
  {
    case 0:case 1:case 2:case 3: run(255,255);//正常前进
      break;
    case 4: spin_left(250, 250);//十字路口左转
      break;
    case 5: brake(10);//终点停车
      break;
  }
}

void count_rhombus(int j = 0)//记录菱形
{
  if (TrackSensorLeftValue1 == HIGH && TrackSensorRightValue1 ==HIGH)
  {
    j++;
  }
  switch (j)
  {
  case 1: right(220, 0);
      break;
  case 2: right(220, 0);
      break;
  }
}

void loop()//小车逻辑判断
{
    //检测到黑线时循迹模块相应的指示灯灭，端口电平为HIGH
    //未检测到黑线时循迹模块相应的指示灯亮，端口电平为LOW
    TrackSensorLeftValue1  = digitalRead(TrackSensorLeftPin1);
    TrackSensorLeftValue2  = digitalRead(TrackSensorLeftPin2);
    TrackSensorRightValue1 = digitalRead(TrackSensorRightPin1);
    TrackSensorRightValue2 = digitalRead(TrackSensorRightPin2);
    TrackSensorcenter = digitalRead(TrackSensorcenter);

                        //直角弯

  // 0 0 x X 0
  // 1 0 x X 0
  // 0 1 x X 0
  // 1 1 1 0 0 
  //处理右锐角和右直角的转动
if ( (TrackSensorLeftValue1 == LOW || TrackSensorLeftValue2 == LOW) &&  TrackSensorRightValue2 == LOW || (TrackSensorRightValue1 ==HIGH && TrackSensorRightValue2 ==HIGH && TrackSensorcenter == HIGH))
    {
    spin_right(150, 150);
    delay(80);
    }
  // 0 X x 0 0       
  // 0 X x 0 1 
  // 0 X x 1 0
  // 0 0 1 1 1       
  //处理左锐角和左直角的转动
else if ( TrackSensorLeftValue1 == LOW && (TrackSensorRightValue1 == LOW ||  TrackSensorRightValue2 == LOW) ||(TrackSensorLeftValue1 == HIGH && TrackSensorLeftValue2 == HIGH &&TrackSensorcenter ==HIGH))
    {
    spin_left(150, 150);
    delay(80);
    }

                        //出轨判断

  // 0 X x X X
  //最左边检测到
else if ( TrackSensorLeftValue1 == LOW)
    {
    spin_left(150, 150);
    delay(2);
    }
  // X x X X 0
  //最右边检测到
else if ( TrackSensorRightValue2 == LOW )
    {
    spin_right(150, 150);
    delay(2);
    }

                        //小弧度弯和姿态校正

  // X 0 x 1 X
  //处理左小弯
else if ( TrackSensorLeftValue2 == LOW && TrackSensorRightValue1 == HIGH)
    {
    left(0, 220);
    }
  // X 1 x 0 X  
  //处理右小弯
else if (TrackSensorLeftValue2 == HIGH && TrackSensorRightValue1 == LOW)
    {
    right(220, 0);
    }

                        //小车直走

  // X 0 1 0 X
else if (TrackSensorLeftValue1 == LOW && TrackSensorRightValue1 == LOW && TrackSensorcenter == HIGH)
    {
    run(250, 250);
    }
}