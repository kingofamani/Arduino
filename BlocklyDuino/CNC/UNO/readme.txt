http://www.taichi-maker.com/homepage/reference-index/motor-reference-index/arduino-cnc-shield/


外部電源要12V

★CNC擴展板上面的5v或3.3v output腳位電源，是從UNO板來的(而非從12V input而來)，
也就是若UNO沒插電，這些腳位也沒電。

AccelStepper程式庫：
安裝 AccelStepper by Patrick Wasp程式庫
http://www.taichi-maker.com/homepage/reference-index/arduino-library-index/accelstepper-library/

常用函数和操作
setMaxSpeed -设置步进电机最大运行速度
setAcceleration -设置步进电机加速度
setSpeed -设置步进电机运行速度
targetPosition -获取步进电机运行目标位置
currentPosition -获取步进电机运行当前位置
setCurrentPosition -复位步进电机初始位置
move – 设置步进电机运动的相对目标位置
moveTo -设置步进电机运动的绝对目标位置
run -步进电机运行（先加速后减速模式）
runSpeed -步进电机运行（匀速模式）
runToNewPosition – 电机运行到用户指定位置值，目标位置为绝对位置。此函数将“block”程序运行。即电机没有到达目标位置前，Arduino将不会继续执行后续程序内容。这一点很像Arduino官方Stepper库中的step函数。

