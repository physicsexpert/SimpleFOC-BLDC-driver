#include <SimpleFOC.h>


MagneticSensorI2C sensor0 = MagneticSensorI2C(AS5600_I2C);

TwoWire I2Cone = TwoWire(0);



void setup() {

  Serial.begin(115200);
  _delay(750);

  I2Cone.begin(4, 16, 400000); 

  sensor0.init(&I2Cone);

}

void loop() {
 // sensor0.update();

  
  //_delay(200);
  Serial.println(sensor0.getAngle()); 

}
