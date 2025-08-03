#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

// Ganti dengan informasi WiFi Anda
const char* ssid = "W KOST BAWAH";
const char* password = "bayardulu";

// Token dari bot Telegram Anda
#define BOT_TOKEN "7053219173:AAF4ri7xiqyU0unc5kUFEnQ7dvROOs4B-js"

// Waktu interval untuk pengecekan pesan baru (milisecond)
#define BOT_CHECK_INTERVAL 500

WiFiClientSecure client;
UniversalTelegramBot bot(BOT_TOKEN, client);

unsigned long lastTimeBotRan;
const int ledPin = D6;  // Pin LED

void setup() {
  Serial.begin(9600);
  
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Mulai dengan LED mati

  // Koneksi ke WiFi
  Serial.print("Connecting to WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");

  client.setInsecure();  // Koneksi tanpa verifikasi SSL
}

void loop() {
  if (millis() - lastTimeBotRan > BOT_CHECK_INTERVAL) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}

void handleNewMessages(int numNewMessages) {
  Serial.print("handleNewMessages ");
  Serial.println(numNewMessages);
  
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (text == "/mulai") {
      String welcome = "Welcome to the LED Bot.\n";
      welcome += "Use the following commands to control the LED:\n";
      welcome += "on - Turn on the LED\n";
      welcome += "off - Turn off the LED\n";
      bot.sendMessage(chat_id, welcome, "");
    }

    if (text == "on") {
      bot.sendMessage(chat_id, "Turning on the LED!", "");
      digitalWrite(ledPin, HIGH);
    }

    if (text == "off") {
      bot.sendMessage(chat_id, "Turning off the LED!", "");
      digitalWrite(ledPin, LOW);
    }
  }
}
