/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Fri, 01 Apr 2022 05:52:49 GMT
 */
/*  部份程式由吉哥積木產生  */
/*  https://sites.google.com/jes.mlc.edu.tw/ljj/linkit7697  */


int my[5] = {4, 1, 3, 6, 2};

void bubbleSort() {
  int len = sizeof(my)/sizeof(my[0]);
  for (int i = 0; i <= len - 1; i++) {
    for (int j = 0; j <= (len - 2) - i; j++) {
      if (my[j] > my[j + 1]) {
        int temp = my[j];
        my[j] = my[j + 1];
        my[j + 1] = temp;
      }
    }
  }
}

void setup()
{
  Serial.begin(9600);

  bubbleSort();
  for (int i = 0; i <= (sizeof(my)/sizeof(my[0])) - 1; i++) {
    Serial.println((my[i]));
  }
}


void loop()
{

}