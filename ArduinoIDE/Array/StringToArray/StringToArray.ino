//最後還要再加,
String msgs = "pet,2022-12-7 14:10:12,客廳,5,120,100,";
String myArray[50];
int arrayLen=0;

void setup() {
  Serial.begin(9600);
  arrayLen = stringToArray(msgs,myArray);

  for (int i = 0 ; i < arrayLen ; i++)
  {
    Serial.println(myArray[i]);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}

int stringToArray(String str,String (& tmpArray) [50] ) {
  int r = 0, t = 0;

  for (int i = 0; i < str.length(); i++)
  {
    if (str[i] == ',')
    {
      if (i - r > 1)
      {
        tmpArray[t] = str.substring(r, i);
        t++;
      }
      r = (i + 1);
    }
  }

  return t;
}
