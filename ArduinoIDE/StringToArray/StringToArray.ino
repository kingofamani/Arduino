void setup() {
  Serial.begin(9600);

  //最後還要再加,
  String msgs = "pet,2022-12-7 14:10:12,客廳,5,120,100,";
  String myArray[50];
  int r = 0, t = 0;

  for (int i = 0; i < msgs.length(); i++)
  {
    if (msgs[i] == ',')
    {
      if (i - r > 1)
      {
        myArray[t] = msgs.substring(r, i);
        t++;
      }
      r = (i + 1);
    }
  }

  for (int k = 0 ; k <= t ; k++)
  {
    Serial.println(myArray[k]);
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
