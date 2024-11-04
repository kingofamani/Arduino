/*
xxxx利用扩展板上传数据到网站
*/
void setup()
{
//准备传数据
  Serial.begin(9600);
}

void loop()
{  
//开始传数据，可以GET或POST
      Serial.print("GET /get");
     Serial.println(" HTTP/1.1");
     Serial.println("Host: httpbin.org");
     Serial.println("Connection: close");
     Serial.println();
     delay(1000);
//结束传数据
     Serial.flush();
}
