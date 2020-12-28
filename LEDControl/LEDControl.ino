#define GREENPIN 6
#define REDPIN 5
#define BLUEPIN 3
#define ledPin 13

const int FADERATE = 1;
const int BRIGHTNESS = 200;

int FADESPEED;
char data;

const byte numChars = 32;
char receivedChars[numChars];   // an array to store the received data
int RGB[] = {0, 0, 0};

boolean newData = false;

void setup() {
  // put your setup code here, to run once:
  pinMode(GREENPIN, OUTPUT);
  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(ledPin, OUTPUT);

  FADESPEED = 4000 / BRIGHTNESS * FADERATE;

  Serial.begin(9600);
}

void loop() {

  recvRGBWithEndMarker();
  showNewData();
  //parseDataRGB();

  //  if(Serial.available() > 0){
  //
  //    data = Serial.read();
  //    Serial.println(data);
  //
  //    switch(data){
  //      case'0':analogWrite(REDPIN, BRIGHTNESS); break;
  //      case'1':analogWrite(BLUEPIN, BRIGHTNESS); break;
  //      case'2':analogWrite(GREENPIN, BRIGHTNESS); break;
  //      case'3':analogWrite(REDPIN, 0); analogWrite(BLUEPIN, 0); analogWrite(GREENPIN, 0);break;
  //      default: break;
  //      }
  //
  //    }



}

void recvRGBWithEndMarker() {
  static byte ndx = 0;
  char endMarker = '\n';
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (rc != endMarker) {
      receivedChars[ndx] = rc;
      ndx++;
      if (ndx >= numChars) {
        ndx = numChars - 1;
      }
    }
    else {
      receivedChars[ndx] = '\0'; // terminate the string
      ndx = 0;
      newData = true;
    }
  }
}

void showNewData() {
  if (newData == true) {
    Serial.println(receivedChars);
    newData = false;
  }

}

void parseDataRGB() {
  String  curIntString = "";
  int j = 0;
  char n;
  
  while (j < 3) {
    for (int i = 0; i < sizeof(receivedChars) / sizeof(receivedChars[0]); i++) {
      n = receivedChars[i];
      if (n != ',') {
        curIntString += n;
      }else{
        RGB[j] = curIntString.toInt();
        j++;
        }
    }
  }
  String meh = "RED: " + (String)RGB[0] + " BLUE: " + (String)RGB[1] + " GREEN: " + (String)RGB[2];
  Serial.println(meh);

}
