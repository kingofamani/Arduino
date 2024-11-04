//Generated Date: Mon, 04 Nov 2024 03:36:16 GMT

#include <WiFiClientSecure.h>
#include <WiFi.h>

WiFiClientSecure client;
char _lwifi_ssid[] = "tyes-itc2";
char _lwifi_pass[] = "xxxxxxxxxxx";
String openaiKey = "xxxxxxxxxxxx";
String model = "gpt-3.5-turbo";
String system_content = "{\"role\": \"system\", \"content\":\"assistant\"}";
String historical_messages = system_content;

String openAI_chat_request(String message) {
  client.setInsecure();
  String user_content = "{\"role\": \"user\", \"content\":\""+ message+"\"}";
  historical_messages += ", "+user_content;
  String request = "{\"model\":\""+model+"\",\"messages\":[" + historical_messages + "]}";
  if (client.connect("api.openai.com", 443)) {
    client.println("POST /v1/chat/completions HTTP/1.1");
    client.println("Connection: close");
    client.println("Host: api.openai.com");
    client.println("Authorization: Bearer " + openaiKey);
    client.println("Content-Type: application/json; charset=utf-8");
    client.println("Content-Length: " + String(request.length()));
    client.println();
    for (int i = 0; i < request.length(); i += 1024) {
      client.print(request.substring(i, i+1024));
    }
    String getResponse="",Feedback="";
    boolean state = false;
    int waitTime = 20000;
    long startTime = millis();
    while ((startTime + waitTime) > millis()) {
      //Serial.print(".");
      delay(100);
      while (client.available()) {
          char c = client.read();
          if (state==true)
            getResponse += String(c);
          if (c == '\n')
            Feedback = "";
          else if (c != '\r')
            Feedback += String(c);
          if (Feedback.indexOf("\",\"content\":\"")!=-1)
            state=true;
          if (Feedback.indexOf("\"},")!=-1)
            state=false;
          startTime = millis();
          if (Feedback.indexOf("\",\"content\":\"")!=-1||Feedback.indexOf("\"content\": \"")!=-1)            state=true;          if (getResponse.indexOf("\"},")!=-1&&state==true) {            state=false;            getResponse = getResponse.substring(0,getResponse.length()-3);          } else if (getResponse.indexOf("\"")!=-1&&c == '\n'&&state==true) {            state=false;            getResponse = getResponse.substring(0,getResponse.length()-3);          }       }
       if (getResponse.length()>0) {
          client.stop();
          String assistant_content = "{\"role\": \"assistant\", \"content\":\""+ getResponse+"\"}";
          historical_messages += ", "+assistant_content;
          Serial.println("");
          return getResponse;
       }
    }
    client.stop();
    //Serial.println(Feedback);
    return "error";
  }
  else
    return "Connection failed";
  }

void openAI_chat_reset() {
	historical_messages = system_content;
}
String OpenAI_E5_B0_8D_E8_A9_B1__E5_AD_97_E6_95_B8_E9_99_90_E5_88_B6_(String msg) {
  //限定請求和回應的字數，避免費用超額
  int requestLen = 150;
  int responseLen = 50;
  String myQuestion = "";
  String openaiAnswer = "";
  if (msg.length() >= requestLen) {
    msg = msg.substring(0, requestLen);
  }
  myQuestion = String(msg)+String("，回覆請限定")+String(responseLen)+String("個字以內");
  openaiAnswer = openAI_chat_request(myQuestion);
  //新的對話不會累積之前的上下文，可控制費用
  openAI_chat_reset();
  return (openaiAnswer);
}

void setup()
{
  Serial.begin(9600);

  WiFi.disconnect();
  WiFi.softAPdisconnect(true);
  WiFi.mode(WIFI_STA);
  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  //字數不要超過50個字，儘量不要直接放在「重複執行」區
  Serial.println((OpenAI_E5_B0_8D_E8_A9_B1__E5_AD_97_E6_95_B8_E9_99_90_E5_88_B6_("我想要養寵物，給我一個的方便照顧的寵物種類建議")));
}

void loop()
{

}
