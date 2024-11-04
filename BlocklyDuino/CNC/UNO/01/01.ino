/*
Arduino CNC电机扩展板驱动NEMA17步进电机示例程序-1
By 太极创客（http://www.taichi-maker.com）
2019-03-10
 
本示例程序旨在演示如何使用Arduino Uno开发板通过Arduino CNC电机扩展板来驱动NEMA17步进电机（42步进电机）。
 
如需获得更多关于本示例程序的电路连接以及CNC电机扩展板的资料信息，
请参考太极创客网站（http://www.taichi-maker.com），并在首页搜索栏中搜索关键字：CNC扩展板
*/
#include <AccelStepper.h>  //本示例程序使用AccelStepper库

// 定义电机控制用常量
 
// A4988连接Arduino引脚号
const int xdirPin = 5;     // 方向控制引脚
const int xstepPin = 2;    // 步进控制引脚
const int xenablePin = 8;  // 使能控制引脚

const int moveSteps = 200;    //运行步数

AccelStepper stepper1(1,xstepPin,xdirPin);//建立步进电机对象

void setup() {
  
  pinMode(xstepPin,OUTPUT);     // Arduino控制A4988步进引脚为输出模式
  pinMode(xdirPin,OUTPUT);      // Arduino控制A4988方向引脚为输出模式
  pinMode(xenablePin,OUTPUT);   // Arduino控制A4988使能引脚为输出模式
  digitalWrite(xenablePin,LOW); // 将使能控制引脚设置为低电平从而让
                                // 电机驱动板进入工作状态

  stepper1.setMaxSpeed(300.0);     // 设置电机最大速度300 
  stepper1.setAcceleration(20.0);  // 设置电机加速度20.0  
}

void loop() {
  // 控制步进电机往复运动
  if ( stepper1.currentPosition() == 0 ){ 
    stepper1.moveTo(moveSteps);              
  } else if ( stepper1.currentPosition() == moveSteps  ){
    stepper1.moveTo(0);            
  }         
  
  stepper1.run();   // 1号电机运行

}
