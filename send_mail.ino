

#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>

const char *ssid = "Wi-fi Name";
const char *password = "Password";

const int echoPin = D5;
const int trigPin = D3;

long duration;
double distance;
unsigned long previousMillis = 0;
int seconds = 0;

const char *host = "Server URL";
const char *mail = "putyour@address.here";

void connectToWiFi()
{
  Serial.println("Connecting to the WiFi");

  WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, password);

  Serial.println("Waiting for connection");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup()
{
  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  Serial.begin(115200);

  delay(1000);

  connectToWiFi();
}

void loop()
{
  unsigned long currentMillis = millis();

  if ((unsigned long)(currentMillis - previousMillis) >= 1000)
  {
    digitalWrite(trigPin, LOW);

    delayMicroseconds(2);

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    if (distance < 35)
    {
      seconds++;
    }
    else
    {
      seconds = 0;
    }
    if (seconds > 3)
    {
      httpGETRequest();
    }
    previousMillis = currentMillis;
  }
}

void httpGETRequest()
{
  HTTPClient http;

  http.begin(host, 5000, "/send_mail?mail=" + mail);

  int httpResponseCode = http.GET();

  http.end();
}
