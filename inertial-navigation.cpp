#include "vex.h"

class locator{
  public:
    float locX;
    float locY;
    float locZ;
    int updateLocation(vex::inertial sensor){ // sensor is the reference to the inertial sensor
      refreshData(sensor);
      velocity();
      locX = locX + spdX;
      locY = locY + spdY;
      locZ = locZ + spdZ;
      return 0;
    }
  private:
    double accX;
    double accY;
    double accZ;
    float spdX;
    float spdY;
    float spdZ;
    double roll;
    double pitch;
    double yaw;
    float abs(float input){
      if (input < 0){
        return -1 * input;
      }
      else{
        return input;
      }
    }
    float contribution(double axis1, double axis2){ // finds out how much the acceleration would impact the speed
      float impactFactor1;
      float impactFactor2;
      impactFactor1 = (abs(axis1 - 180)/90) - 1;
      impactFactor2 = (abs(axis2 - 180)/90) - 1;
      return impactFactor1 * impactFactor2;
    }
    int velocity(){ // derives velocity on axises based on orientation and acceleration
      spdX = spdX + accX * contribution(yaw, pitch);
      spdY = spdY + accY * contribution(roll, yaw);
      spdZ = spdZ + accZ * contribution(pitch, roll);
      return 0;
    }
    int refreshData(vex::inertial sensor){ // acquires data from inertial sensor
      accX = sensor.acceleration(xaxis);
      accY = sensor.acceleration(yaxis);
      accZ = sensor.acceleration(zaxis);
      roll = sensor.roll();
      pitch = sensor.pitch();
      yaw = sensor.yaw();
      return 0;
    }
};