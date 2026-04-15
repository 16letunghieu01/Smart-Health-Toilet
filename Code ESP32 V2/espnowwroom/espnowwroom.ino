#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>
// #include <Adafruit_PWMServoDriver.h>

//define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701
#define waterpump 27

// Replace with your network credentials
const char* ssid = "Hello";
const char* password = "Hieuthao";

// Define sensor
const int trigPin = 5;
const int echoPin = 18;

WiFiServer server(80);
Servo servo1;
Servo servo2;

int checkCam;
int checkSensor;

int servo1Pin = 13;
int servo2Pin = 14;

// Sensor
long duration;
float distanceCm;
float distanceInch;

String header;

// Auxiliar variables to store the current output state
String Button = "off";

// Assign output variables to GPIO pins
const int sentsignal = 2;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// REPLACE WITH YOUR ESP RECEIVER'S MAC ADDRESS
uint8_t broadcastAddress1[] = {0xec, 0x64, 0xc9, 0xac, 0xe0, 0x4c};
// uint8_t broadcastAddress2[] = {0xFF, , , , , };
// uint8_t broadcastAddress3[] = {0xFF, , , , , };

typedef struct test_struct {
  int captureValue;
} test_struct;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  Serial.print("Packet to: ");
  // Copies the sender mac address to a string
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print(macStr);
  Serial.print(" send status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 
void sendsignal() {

  test_struct test;
  test.captureValue = 10;
 
  esp_err_t result1 = esp_now_send(
    broadcastAddress1, 
    (uint8_t *) &test,
    sizeof(test_struct));
   
  if (result1 == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
}

void espnowConnect() {
  int retryCount = 0;
  const int maxRetries = 5; // Số lần thử lại tối đa
 
  // Thử khởi tạo ESP-NOW nhiều lần
  while (esp_now_init() != ESP_OK) {
    retryCount++;
    Serial.println("Error initializing ESP-NOW, retrying...");
    delay(1000); // Chờ một chút trước khi thử lại

    if (retryCount >= maxRetries) {
      Serial.println("Failed to initialize ESP-NOW after multiple attempts.");
      return; // Thoát nếu vượt quá số lần thử lại
    }
  }

  Serial.println("ESP-NOW initialized successfully");
  esp_now_register_send_cb(OnDataSent);

  // register peer
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  memcpy(peerInfo.peer_addr, broadcastAddress1, 6);

  retryCount = 0; // Đặt lại bộ đếm thử lại

  // Thử thêm peer nhiều lần
  while (esp_now_add_peer(&peerInfo) != ESP_OK) {
    retryCount++;
    Serial.println("Failed to add peer, retrying...");
    delay(1000);

    if (retryCount >= maxRetries) {
      Serial.println("Failed to add peer after multiple attempts.");
      return; // Thoát nếu không thêm được peer
    }
  }

  Serial.println("Peer added successfully");
}

void wifiConnect() {
  //Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // uint8_t channel = WiFi.channel(); // Lấy kênh Wi-Fi
  // esp_wifi_set_channel(channel, WIFI_SECOND_CHAN_NONE); // Đồng bộ kênh với ESP-NOW

  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
/*
void receivesignal() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /button/on") >= 0) {
              Serial.println("Capture Mode ON");
              Button = "on";
              checkCam = 1;
              digitalWrite(sentsignal, HIGH);
            } else if (header.indexOf("GET /button/off") >= 0) {
              Serial.println("Capture Mode OFF");
              Button = "off";
              checkCam = 0;
              digitalWrite(sentsignal, LOW);
            } 
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ECOFLUSH TOILET</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Capture - Mode " + Button + "</p>");
            // If the output26State is off, it displays the ON button       
            if (Button=="off") {
              client.println("<p><a href=\"/button/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/button/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}*/
void receivesignal() {
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // If a new client connects,
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            
            // Add CORS headers
            client.println("Access-Control-Allow-Origin: *");
            client.println("Access-Control-Allow-Methods: GET, POST");
            client.println("Access-Control-Allow-Headers: Content-Type");
            
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /button/on") >= 0) {
              Serial.println("Capture Mode ON");
              Button = "on";
              checkCam = 1;
              digitalWrite(sentsignal, HIGH);
            } else if (header.indexOf("GET /button/off") >= 0) {
              Serial.println("Capture Mode OFF");
              Button = "off";
              checkCam = 0;
              digitalWrite(sentsignal, LOW);
            } 
            
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ECOFLUSH TOILET</h1>");
            
            // Display current state, and ON/OFF buttons for GPIO 26  
            client.println("<p>Capture - Mode " + Button + "</p>");
            if (Button=="off") {
              client.println("<p><a href=\"/button/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/button/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            
            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
  }
}

void closelid() {
  servo1.write(90);
  delay(2000);
}

void openlid() {
  servo1.write(0);
  delay(2000);
}

void closelid_little() {
  servo2.write(0);
  delay(2000);
}

void openlid_little() {
  servo2.write(95);
  delay(2000);
}

void clear() {
  digitalWrite(waterpump, HIGH);
  delay(5000);
  digitalWrite(waterpump, LOW);
  delay(200);
}

void water_plus() {
  digitalWrite(waterpump, HIGH);
  delay(1000);
  digitalWrite(waterpump, LOW);
  delay(200);
}

void Capture() {
  if (checkCam == 1) {
    Serial.println("Chụp ảnh");
    WiFi.disconnect();
    // espnowConnect();
    sendsignal();
    // checkCam = 0;
    wifiConnect();
  }
}

bool checkSafety() {
  // Đo khoảng cách
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  if (duration > 0) {
    distanceCm = duration * SOUND_SPEED / 2;

    if (distanceCm < 4) {  // Phát hiện kẹt tay (khoảng cách < 5cm)
      Serial.println("Phát hiện vật cản! Dừng vệ sinh.");
      openlid();  // Mở nắp bồn cầu để đảm bảo an toàn
      return true;  // Báo hiệu dừng hoạt động
    }
  }
  return false;  // Không phát hiện vấn đề
}

void Autoclean() {
  closelid();
  Serial.println("Đóng nắp bồn cầu");

  for (int i = 0; i < 5; i++) {  // Kiểm tra liên tục trong 5 giây
    if (checkSafety()) return;  // Nếu phát hiện vật cản, dừng ngay lập tức
    delay(100);  // Kiểm tra mỗi giây
  }

  if (checkCam == 1) {
    Capture();  // Chụp ảnh nếu cần
    delay(5000);
  }

  openlid_little();
  Serial.println("Xả chất thải");
  clear();
  Serial.println("Bơm nước");

  for (int i = 0; i < 5; i++) {  // Kiểm tra liên tục trong 5 giây
    if (checkSafety()) return;  // Nếu phát hiện vật cản, dừng ngay lập tức
    delay(1000);
  }

  closelid_little();
  water_plus();
  Serial.println("Xả nước");

  openlid();
  Serial.println("Mở nắp bồn cầu");
  checkSensor = 0;
}

void setup() {
 
  Serial.begin(115200);

  servo1.write(0);
  servo1.attach(servo1Pin);

  servo2.write(0);
  servo2.attach(servo2Pin);

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(waterpump, OUTPUT);

  checkCam = 0;

  pinMode(sentsignal, OUTPUT);
  // Set outputs to LOW
  digitalWrite(sentsignal, LOW);
  digitalWrite(waterpump, LOW);

  WiFi.mode(WIFI_AP_STA);

  wifiConnect(); 
  espnowConnect(); 
}

void loop() {
  receivesignal();

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  if (duration > 0) {  // Kiểm tra nếu có tín hiệu
    distanceCm = duration * SOUND_SPEED / 2;
    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

    if (distanceCm < 15) {
      checkSensor = 1;  // Người dùng có mặt
      Serial.println("User detected!");
    }

    if (distanceCm > 15 && checkSensor == 1) {
      Autoclean();  // Dọn vệ sinh khi người dùng rời đi
    }
  } else {
    Serial.println("No signal from sensor");
  }

  delay(2000);
}