1、偏好設定：
https://dl.espressif.com/dl/package_esp32_index.json
2、工具/開發板/開發板管理員，安裝esp32

教學：
https://sites.google.com/site/wenyuwebbit/22-esp32-cam/01-%E8%AA%8D%E8%AD%98esp32-cam
https://sites.google.com/site/wenyuwebbit/22-esp32-cam/01-ren-shiesp32-cam
範例/ESP23/camera/CameraWebServer：
	L.14選用#define CAMERA_MODEL_AI_THINKER	
燒錄：
	要接IO0和GND，按「上傳」鈕後，馬上按ESP32Cam的Reset鍵
執行：
	IO0和GND拔除，開啟Serial後，馬上按Reset鍵
讀取ip後，開啟網頁即可
	