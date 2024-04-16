★中央氣象開放資料平台
https://opendata.cwa.gov.tw/user/authkey
法蘭斯/台灣天氣預報：
nas/金鑰

官網測試：
https://opendata.cwa.gov.tw/dist/opendata-swagger.html#/%E9%A0%90%E5%A0%B1/get_v1_rest_datastore_F_D0047_071
要選HTTPS，然後選「GET/v1/rest/datastore/F-D0047-071鄉鎮天氣預報-新北市未來1週天氣預報」

地區參考https://opendata.cwa.gov.tw/opendatadoc/Opendata_City.pdf

取得五股區預報：
https://opendata.cwa.gov.tw/api/v1/rest/datastore/F-D0047-071?Authorization=金鑰&format=JSON&locationName=%E4%BA%94%E8%82%A1%E5%8D%80

線上測試：
https://base64.guru/tools/http-request-online
將json格式化：
https://jsoneditoronline.org/#left=local.relafo


======================================================
OpenWeatherMap
缺點：只能抓大範圍地區，無法依縣市鄉鎮抓資料，
      例如德音國小25.072027, 121.434602，
      輸入後沒有用，只會抓新北市唯一觀測站-板橋。

免費版API：每3小時預報5天
https://openweathermap.org/price

https://api.openweathermap.org/data/2.5/forecast?lat=25.07202704139029&lon=121.43460220516009&cnt=7&appid=金鑰

今天：
doc["list"][0]["main"]["temp_min"].as<char*>()
doc["list"][0]["main"]["temp_max"].as<char*>()
doc["list"][0]["main"]["humidity"].as<char*>()
doc["list"][0]["main"]["weather"]["main"].as<char*>()


======================================================
Windy：
缺點：只會傳回模擬數據，非真實數據。付費才可以
Windy API key：
nas/金鑰

code測試：
https://wokwi.com/projects/394475291230381057

http測試：
https://reqbin.com/
https://api.windy.com/api/point-forecast/v2
{
    "lat": 25.072085348863467,
    "lon": 121.4346129355219,
    "model": "gfs",
    "parameters": ["temp", "lclouds"],
    "levels": ["surface"],
    "key": "金鑰"
}














