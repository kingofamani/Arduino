安裝Node-RED後，執行start-node-red.ps1
瀏覽器 http://127.0.0.1:1880/

安裝 vlc media player

selenium-script.js複製至C:\Users\user\.node-red


在postman發送mqtt主題消息(其實是發送http GET)：
GET https://api.thingspeak.com/update?api_key= 【thingspeak Write API Key】&field4=https://taira-komori.jpn.org/sound_os2/anime01/blackout_piano1.mp3
Headers：
	Content-Type:text/plain

Node-RED：
	Mqtt In元件(接收mqtt)：
	主題：channels/2726035/subscribe/fields/field4
	服務端：mqtt://mqtt3.thingspeak.com
	使用端ID：金鑰/thingspeak/Client ID
	使用者名稱：金鑰/thingspeak/Client ID
	密碼：金鑰/thingspeak/pwd	

	如果寫在Inject元件：
	"C:\Program Files\VideoLAN\VLC\vlc.exe"  --play-and-exit "https://taira-komori.jpn.org/sound_os2/anime01/blackout_piano1.mp3"

	如果寫在function元件：
	msg.payload = `"C:\\Program Files\\VideoLAN\\VLC\\vlc.exe" --play-and-exit "${msg.payload}"`;
	return msg;
