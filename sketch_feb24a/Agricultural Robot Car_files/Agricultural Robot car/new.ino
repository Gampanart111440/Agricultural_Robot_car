#include <MicroGear.h>
#define D26 26
#define D12 12
#define D32 32
#define D33 33
#define D18 18
#define D19 19
#define D22 22
#define D23 23
//#define D25 25
#define D26 26
#define D35 35
#define D21 21
#define DRILL  D26  
#define WATERING D12
#define SEED D32
#define PIT D33
#define  FORWARD D18
#define  BACKWARD D19
#define  TURNLEFT D22
#define  TURNRIGHT D23
//#define camera1 D25
//#define camera2 D26
//#define camera3 D35
//#define Automatic D21
const char* ssid     = "newnew";
const char* password = "5935512089";

#define APPID       "Robotcar111440"
#define GEARKEY     "vXcEoJnJ609S63z"
#define GEARSECRET  "lcGJMreYG7O6DCFu0IsV2mt70"
#define SCOPE       ""

WiFiClient client;
AuthClient *authclient;

MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
  Serial.print("Incoming message --> ");
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
  for (int i = 0; i < msglen; i++) 
  {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
  Serial.println();

  String stateStr = String(strState).substring(0, msglen);
  static unsigned long last1 = millis();
  if (stateStr == "ONWATERING"){
    digitalWrite(WATERING,LOW);
    microgear.chat("controllerplug1", "ONWATERING");
  }
  else if (stateStr == "OFFWATERING") 
  {
    digitalWrite(WATERING, HIGH);
    microgear.chat("controllerplug1", "OFFWATERING");
  }
  if (stateStr == "ONDRILL") 
  {
    digitalWrite(DRILL,LOW);
    microgear.chat("controllerplug2", "ONDRILL");
  } 
  else if (stateStr == "OFFDRILL") 
  {
    digitalWrite(DRILL,HIGH);
    microgear.chat("controllerplug2", "OFFDRILL");
  }
   
    if (stateStr == "ONSEED"){
    digitalWrite(SEED,LOW);
    microgear.chat("controllerplug3", "ONSEED");
  } 
  else if (stateStr == "OFFSEED") 
  {
    digitalWrite(SEED, HIGH);
    microgear.chat("controllerplug3", "OFFSEED");
  }
  if (stateStr == "ONPIT"){
    digitalWrite(PIT,LOW);
    microgear.chat("controllerplug4", "ONPIT");
  } 
  else if (stateStr == "OFFPIT") 
  {
    digitalWrite(PIT,HIGH);
    microgear.chat("controllerplug4", "OFFPIT");
  }
  
   if (stateStr == "ONFORWARD"){
    
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    microgear.chat("controllerplug5", "ONFORWARD");
  } 
  else if (stateStr == "OFFFORWARD") 
  {
     digitalWrite(18, HIGH);
    digitalWrite(19, LOW);
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
    microgear.chat("controllerplug5", "OFFFORWARD");
  }
  if (stateStr == "ONBACKWARD"){
    digitalWrite(18, LOW);
    digitalWrite(19, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
   
    microgear.chat("controllerplug6", "ONBACKWARD");
  } 
  else if (stateStr == "OFFBACKWARD") 
  {
   digitalWrite(18, LOW);
    digitalWrite(19, HIGH);
    digitalWrite(22, LOW);
    digitalWrite(23, HIGH);
    microgear.chat("controllerplug6", "OFFBACKWARD");
  }
  
   if (stateStr == "ONTURNLEFT"){
   digitalWrite(18, LOW);
    digitalWrite(19, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    microgear.chat("controllerplug7", "ONTURNLEFT");
  } 
  else if (stateStr == "OFFTURNLEFT") 
  {
   //เลี้ยวซ้าย 
     digitalWrite(18, HIGH);
    digitalWrite(19, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, HIGH);
    microgear.chat("controllerplug7", "OFFTURNLEFT");
  }
if (stateStr == "ONTURNRIGHT"){
  //เลี้ยวขวา
   digitalWrite(18, LOW);
    digitalWrite(19, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    microgear.chat("controllerplug8", "ONTURNRIGHT");
  } 
  else if (stateStr == "OFFTURNRIGHT") 
  {
  digitalWrite(18,LOW);
    digitalWrite(19, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
    microgear.chat("controllerplug8", "OFFTURNRIGHT");
  }
  /*
  
  /////////////////////////////////////////////////////////////////////////////////////////////////
  if (stateStr == "ONOpenthecamera1"){
    digitalWrite(camera1, HIGH);
    microgear.chat("controllerplug9", "ONOpenthecamera1");
  } 
  else if (stateStr == "OFFOpenthecamera1") 
  {
   digitalWrite(camera1, LOW);
    microgear.chat("controllerplug9", "OFFOpenthecamera1");
  }
  
if (stateStr == "ONOpenthecamera2"){
    digitalWrite(camera2, HIGH);
    microgear.chat("controllerplug10", "ONOpenthecamera2");
  } 
  else if (stateStr == "OFFOpenthecamera2") 
  {
   digitalWrite(camera2, LOW);
    microgear.chat("controllerplug10", "OFFOpenthecamera2");
  }
  if (stateStr == "ONOpenthecamera3"){
    digitalWrite(camera3, HIGH);
    microgear.chat("controllerplug11", "ONOpenthecamera3");
  } 
  else if (stateStr == "OFFOpenthecamera3") 
  {
   digitalWrite(camera3, LOW);
    microgear.chat("controllerplug11", "OFFOpenthecamera3");
  }*/
  /////////////////////////////////////////////////////////////////////////////////////////////////
  if (stateStr == "ONSTARTAUTOMATIC"){ 
     digitalWrite(18, LOW);
    digitalWrite(19, LOW);
    digitalWrite(22, LOW);
    digitalWrite(23, LOW);
    microgear.chat("controllerplug12", "ONSTARTAUTOMATIC");
  } 
  else if (stateStr == "OFFSTARTAUTOMATIC") 
  {
    microgear.chat("controllerplug12", "OFFSTARTAUTOMATIC");
  }
  
}
  
void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
  Serial.println("Connected to NETPIE...");
  microgear.setName("pieplug");
}
void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
    {
        Serial.print((char)msg[i]);
    }
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
    {
      Serial.print((char)msg[i]);
    }
    Serial.println();
}

void setup() 
{
    /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(PRESENT,onFoundgear);
    microgear.on(ABSENT,onLostgear);
    microgear.on(CONNECTED,onConnected);
    Serial.begin(115200);
    Serial.println("Starting...");

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
       delay(250);
       Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //uncomment the line below if you want to reset token -->
    microgear.resetToken();
    microgear.init(GEARKEY,GEARSECRET,SCOPE);
    microgear.connect(APPID);
    pinMode(DRILL,OUTPUT); 
    pinMode(WATERING,OUTPUT); 
    pinMode(SEED,OUTPUT);
    pinMode(PIT,OUTPUT);
    pinMode(FORWARD,OUTPUT);
    pinMode(BACKWARD,OUTPUT);
     pinMode(TURNLEFT,OUTPUT);
     pinMode(TURNRIGHT,OUTPUT);
 //pinMode(camera1,OUTPUT);
 //pinMode(camera2,OUTPUT);
// pinMode(camera3,OUTPUT);
// pinMode(Automatic,OUTPUT);
digitalWrite(WATERING,LOW);
 digitalWrite(DRILL,LOW);
 digitalWrite(SEED,LOW);
 digitalWrite(PIT,LOW);
 digitalWrite(FORWARD, HIGH);
 digitalWrite(BACKWARD, HIGH);
 digitalWrite(TURNLEFT, HIGH);
 digitalWrite(TURNRIGHT, HIGH);
 //digitalWrite(camera1, HIGH);
 //digitalWrite(camera3, HIGH);
 //digitalWrite(Automatic, HIGH);
}
void loop() 
{
  if (microgear.connected()) 
  {
    microgear.loop();
    Serial.println("connect...");
  } 
  else 
  {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
  }
  delay(1000);
}
