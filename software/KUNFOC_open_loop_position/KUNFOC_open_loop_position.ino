// Deng's FOC 开环位置控制例程 测试库：SimpleFOC 2.1.1 测试硬件：KUNFOC控制器
// 串口中输入"T+数字"设定两个电机的位置，如设置电机转到到180度，输入 "T3.14"（弧度制的180度）
// 在使用自己的电机时，请一定记得修改默认极对数，即 BLDCMotor(7) 中的值，设置为自己的极对数数字
// 程序默认设置的供电电压为 7.4V,用其他电压供电请记得修改 voltage_power_supply , voltage_limit 变量中的值

#include <SimpleFOC.h>

BLDCMotor motor = BLDCMotor(7);
BLDCDriver3PWM driver = BLDCDriver3PWM(5, 9, 10, 21);
int jiaodu = 0;


//目标变量
float target_velocity = 0;

//串口指令设置
Commander command = Commander(Serial);
void doTarget(char* cmd) {
  command.scalar(&target_velocity, cmd);
}

void setup() {
  pinMode(2, OUTPUT);
  pinMode(21, INPUT_PULLUP);
  pinMode(15, INPUT_PULLUP);
  driver.voltage_power_supply = 12;
  driver.init();
  motor.linkDriver(&driver);
  motor.voltage_limit = 5;   // [V]
  motor.velocity_limit = 50; // [rad/s]




  //开环控制模式设置
  motor.controller = MotionControlType::angle_openloop;


  //初始化硬件
  motor.init();



  //增加 T 指令
  command.add('T', doTarget, "target velocity");

  Serial.begin(115200);
  Serial.println("Motor ready!");
  Serial.println("Set target velocity [rad/s]");
  motor.move(0);
  _delay(1000);
}

void loop() {

//    if (digitalRead(21) == LOW) {
//      digitalWrite(2, HIGH);
//      jiaodu = jiaodu + 1;
//      delay(100);
//  
//    }
//    if (digitalRead(15) == LOW) {
//      digitalWrite(2, LOW);
//      jiaodu = jiaodu - 1;
//      delay(100);
//    }
//
//
//
//jiaodu = target_velocity / 180 * 3.14;
//
//
//
// motor.move(jiaodu);



motor.move(target_velocity);


  //  Serial.println(jiaodu);

  //用户通讯
  command.run();
}
