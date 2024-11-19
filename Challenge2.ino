#include <WiFi.h>
#include <ESPAsyncWebServer.h>  // For WebSocket server
#include <AsyncTCP.h>           // Required for Async WebSocket on ESP32

const char* ssid = "";        // Replace with your network credentials
const char* password = ""; 

// LED pin assignments
const int Red_pin = 16;
const int Blue_pin = 20;
const int Green_pin = 33;

// Web server and WebSocket server initialization
AsyncWebServer server(80);
AsyncWebSocket ws("/ws");

// Brightness levels for each LED (range 0-255 for PWM)
int Red_brightness = 0;
int Blue_brightness = 0;
int Green_brightness = 0;

void setup() {
  Serial.begin(115200);

  ledcAttach(Red_pin, 5000, 8);     
  ledcAttach(Blue_pin, 5000, 8);
  ledcAttach(Green_pin, 5000, 8);


  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP());

  // Serve the webpage with sliders
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/html", getHtml());
  });

  // WebSocket event handler
  ws.onEvent(onWebSocketEvent);
  server.addHandler(&ws);

  // Start the server
  server.begin();
}

void loop() {
  ws.cleanupClients();  // Maintain WebSocket connections
}

// HTML content with sliders for LED brightness control
String getHtml() {
  String html = "<!DOCTYPE html><html>";
  html += "<head><meta charset='UTF-8'><meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>body{text-align:center;font-family:Arial;} .slider{width:300px;}</style></head><body>";
  html += "<h2>ESP32 LED Brightness Control</h2>";
  html += "<p>Red LED: <input type='range' min='0' max='255' value='" + String(Red_brightness) + "' class='slider' id='RedSlider'></p>";
  html += "<p>Blue LED: <input type='range' min='0' max='255' value='" + String(Blue_brightness) + "' class='slider' id='BlueSlider'></p>";
  html += "<p>Green LED: <input type='range' min='0' max='255' value='" + String(Green_brightness) + "' class='slider' id='GreenSlider'></p>";
  html += "<script>var ws = new WebSocket('ws://' + window.location.hostname + '/ws');";
  html += "function updateBrightness(id) { ws.send(id + ':' + document.getElementById(id).value); };";
  html += "document.getElementById('RedSlider').oninput = function() { updateBrightness('RedSlider'); };";
  html += "document.getElementById('BlueSlider').oninput = function() { updateBrightness('BlueSlider'); };";
  html += "document.getElementById('GreenSlider').oninput = function() { updateBrightness('GreenSlider'); };";
  html += "</script></body></html>";
  return html;
}

// WebSocket event handler to process brightness updates
void onWebSocketEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len) {
  if (type == WS_EVT_DATA) {
    String message = "";
    for (size_t i = 0; i < len; i++) message += (char) data[i];

    // Parse slider ID and brightness value
    int separator = message.indexOf(':');
    String slider = message.substring(0, separator);
    int value = message.substring(separator + 1).toInt();

    // Update brightness based on slider ID
    if (slider == "RedSlider") {
      Red_brightness = value;
      ledcWrite(Red_pin, Red_brightness);  // Adjust Red LED brightness
    } else if (slider == "BlueSlider") {
      Blue_brightness = value;
      ledcWrite(Blue_pin, Blue_brightness);  // Adjust Blue LED brightness
    } else if (slider == "GreenSlider") {
      Green_brightness = value;
      ledcWrite(Green_pin, Green_brightness);  // Adjust Green LED brightness
    }
    Serial.printf("%s brightness set to %d\n", slider.c_str(), value);
  }
}