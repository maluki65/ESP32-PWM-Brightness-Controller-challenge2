# ESP32-PWM-Brightness-Controller-challenge2
# ESP32 LED Brightness Control via WebSocket

## Overview
This project demonstrates how to control the brightness of three LEDs connected to an ESP32 using a web-based interface. The LEDs' brightness is adjusted in real-time using WebSocket communication between the client (web browser) and the ESP32.

## Features
- Control Red, Blue, and Green LED brightness individually using sliders on a web page.
- Real-time updates using WebSocket communication.
- Simple and responsive web interface for ease of use.

## Hardware Requirements
- ESP32 board
- 3 LEDs (Red, Blue, Green)
- Resistors for the LEDs (220Ω recommended)
- Breadboard and jumper wires
- Wi-Fi network for connectivity

## Software Requirements
- [Arduino IDE](https://www.arduino.cc/en/software)
- ESP32 Board Package (install via Arduino IDE)
- Required Libraries:
  - **WiFi.h**: For Wi-Fi connectivity
  - **ESPAsyncWebServer.h**: For serving the web page and handling WebSocket
  - **AsyncTCP.h**: Required by `ESPAsyncWebServer` for WebSocket support

## Circuit Diagram
Connect the LEDs to the following pins on the ESP32 with resistors:
- Red LED: GPIO 16
- Blue LED: GPIO 20
- Green LED: GPIO 33

Ensure the cathode (short leg) of each LED is connected to the ground (GND).

## Setup and Usage

### 1. Hardware Setup
1. Connect the LEDs and resistors to the specified GPIO pins.
2. Connect the ESP32 to your computer via USB.

### 2. Code Configuration
1. Replace the `ssid` and `password` variables with your Wi-Fi network credentials:
   ```cpp
   const char* ssid = "Your_SSID";      
   const char* password = "Your_PASSWORD"; 
   ```

2. Upload the code to your ESP32 using the Arduino IDE.

### 3. Accessing the Web Interface
1. After uploading the code, open the Serial Monitor to check the IP address assigned to the ESP32.
2. Open a web browser and enter the IP address displayed in the Serial Monitor.
3. Use the sliders to adjust the brightness of each LED in real-time.

### 4. WebSocket Communication
- The web page sends brightness updates to the ESP32 through a WebSocket connection.
- The ESP32 updates the PWM output to adjust the brightness of the LEDs accordingly.

## Code Explanation
- **`setup()`**: Initializes Wi-Fi, sets up the web server, and configures WebSocket.
- **`getHtml()`**: Generates the HTML content for the web interface, including sliders.
- **`onWebSocketEvent()`**: Handles incoming WebSocket messages and updates the LED brightness.
- **`loop()`**: Maintains WebSocket client connections.

## Potential Issues
- Ensure the correct GPIO pins are used.
- Verify Wi-Fi credentials.
- Make sure the required libraries are installed in the Arduino IDE.

## Future Enhancements
- Add authentication for the web interface.
- Enhance the UI for mobile and desktop compatibility.
- Include more LEDs or devices for control.

## License
This project is licensed under the MIT License. You are free to use, modify, and distribute it.
