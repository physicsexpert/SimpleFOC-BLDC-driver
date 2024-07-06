/**
  Deng's FOC 闭环位置控制例程 测试库：SimpleFOC 2.1.1 测试硬件：KUNFOC控制器
  在串口窗口中输入：T+位置，就可以使得两个电机闭环转动
  比如让两个电机都转动180°，则输入其弧度制：T3.14
  在使用自己的电机时，请一定记得修改默认极对数，即 BLDCMotor(7) 中的值，设置为自己的极对数数字
  程序默认设置的供电电压为 7.4V,用其他电压供电请记得修改 voltage_power_supply , voltage_limit 变量中的值
  默认PID针对的电机是 Ipower 4008 ，使用自己的电机需要修改PID参数，才能实现更好效果
*/

#include <SimpleFOC.h>
int Angle;

MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);

TwoWire I2Cone = TwoWire(0);


//电机参数
BLDCMotor motor = BLDCMotor(11);
BLDCDriver3PWM driver = BLDCDriver3PWM(17, 5, 18, 19);



//命令设置

float target_velocity = 0;
Commander command = Commander(Serial);
void doTarget(char* cmd) {
  command.scalar(&target_velocity, cmd);
}

void setup() {
  I2Cone.begin(4, 16, 400000);

  sensor.init(&I2Cone);

  //连接motor对象与传感器对象
  motor.linkSensor(&sensor);


  //供电电压设置 [V]
  driver.voltage_power_supply = 12;
  driver.init();


  //连接电机和driver对象
  motor.linkDriver(&driver);


  //FOC模型选择
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;

  //运动控制模式设置
  motor.controller = MotionControlType::angle;


  //速度PI环设置
  motor.PID_velocity.P = 0.2;

  motor.PID_velocity.I = 1;

  //motor.PID_velocity.D = 0.1;

  //角度P环设置
  motor.P_angle.P = 20;
  //motor.P_angle.I = 10;
  motor.P_angle.D = 0.5;

  //最大电机限制电机
  motor.voltage_limit = 5;


  //速度低通滤波时间常数
  motor.LPF_velocity.Tf = 0.01;

  //设置最大速度限制
  motor.velocity_limit = 40;


  Serial.begin(115200);
  motor.useMonitoring(Serial);



  //初始化电机
  motor.init();

  //初始化 FOC
  motor.initFOC();

  command.add('T', doTarget, "target velocity");

  Serial.println(F("Motor ready."));
  Serial.println(F("Set the target velocity using serial terminal:"));
  pinMode(2, OUTPUT);
  pinMode(21, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);


}



void loop() {
  motor.loopFOC();


   motor.move(target_velocity);

  //  Serial.println(target_velocity);
  //  Serial.println(sensor.getAngle());
  if (digitalRead(21) == LOW) {
    digitalWrite(2, HIGH);
    target_velocity = target_velocity + 2;
    delay(200);

  }
  if (digitalRead(15) == LOW) {
    digitalWrite(2, LOW);
    target_velocity = target_velocity - 2;
    delay(200);
  }




//  Serial.println(Angle);

//  Angle = sensor.getAngle();
//    if (10 < Angle < 20) {
//      motor.move(-15);
//  
//    }

  //  if (-4 < sensor.getAngle() <-2) {
  //   target_velocity=-3;
  //
  //  }
  //  if (-6 < sensor.getAngle() <-4) {
  //   target_velocity=-5;
  //
  //  }
  //
  //  if (0 < sensor.getAngle() <2) {
  //   target_velocity=1;
  //
  //  }
  //  if (2 < sensor.getAngle() <4) {
  //   target_velocity=3;
  //
  //  }
  //  if (4 < sensor.getAngle() <6) {
  //   target_velocity=5;
  //
  //  }


  command.run();
}
