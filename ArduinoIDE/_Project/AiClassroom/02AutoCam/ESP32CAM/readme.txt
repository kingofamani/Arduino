積木：法蘭斯/Server模組/ESP-32 CAM

=============範例01BlockyEspCamUpdateToGoogleDrive==============
ESP32-CAM上傳Google Drive

教學：
https://www.youtube.com/watch?v=ZFYjtieMZfc

arduino程式：
https://github.com/fustyles/Arduino/tree/master/ESP32-CAM_GoogleDrive_Linenotify

GAS程式：
https://github.com/fustyles/webduino/blob/gs/SendCapturedImageToGoogleDriveAndLinenotify_doPost.gs

我的GAS：
https://script.google.com/home/projects/1zO4DbjMxW3Y3l9-3OZei8i1xVydiP6W-HjJUE1Iz_j-k4dJyfkJg9SJS/edit
網頁應用程式
https://script.google.com/macros/s/ 【金鑰/Apps Script ID】/exec
將s/至/exec之間的id貼至積木的Apps Script ID



=============範例02Esp32CamMQTT==============
開發時不用BlocklyDuino，改用locklyDuino內建的Arduino IDE 1.8.19
★★★Arduino IDE/右鍵/以系統管理員身份執行

Adafruit IO不能用原始的Adafruit_MQTT_Wifi，否則會和CAM搶WIFI，要用Adafruit_MQTT_Client 

接著開啟 草稿碼/匯入程式庫/Base64_tool，程式會新增一行#include <Base64_tool.h>
手動將舊的#include "Base64_tool.h" 刪除

★記得電腦與 ESP32-CAM 要在同一個WIFI網路區域問題
http://192.168.2.109/


=============範例03Esp32CamMQTTGoogleDrive==============
結合自動照像上傳至Google Drive


