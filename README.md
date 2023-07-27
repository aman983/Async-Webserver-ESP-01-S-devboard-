# Async-Webserver for [ESP 01 S devboard](https://github.com/aman983/ESP-01S_Relay_Module)

This project demonstrates how to control relays using an [ESP 01 S devboard](https://github.com/aman983/ESP-01S_Relay_Module) that runs Asynchronous web server. The code allows you to toggle the relays' state through a web interface, making it easy to control devices remotely.

## Requirements

- Arduino IDE
- [ESP 01 S devboard](https://github.com/aman983/ESP-01S_Relay_Module)
- Two-channel relay module

## Device and web GUI
<h3 align="center">Ip address from Serial terminal</h3>
<p align="center">
  <img src="https://github.com/aman983/Async-Webserver-ESP-01-S-devboard-/blob/main/Assets/Terminal.png" height = 150 width = 400 >
</p>
<h3 align="center">GUI</h3>
<p align="center">
   Access the web server using the IP address shown in the Serial Monitor. The web page will display two toggle switches for each relay. You can toggle the switches to turn the relays on or off.</p>
   <p align="center">
      <img src="https://github.com/aman983/Async-Webserver-ESP-01-S-devboard-/blob/main/Assets/webserver.jpeg" height = 480 width = 222 >
   </p>
<h3 align="center">ESP 01 S Relay Development board</h3>
<p align="center">
  <img src="https://github.com/aman983/Async-Webserver-ESP-01-S-devboard-/blob/main/Assets/board.jpeg" height = 480 width = 347 >
</p>


## Getting Started

1. Connect your [ESP 01 S devboard](https://github.com/aman983/ESP-01S_Relay_Module) to your computer.
2. Open the Arduino IDE and install the required libraries:
   - Arduino Core for ESP8266 (should be installed by default for ESP8266 boards)
   - ESP8266WiFi library
   - ESPAsyncTCP library
   - ESPAsyncWebServer library
3. Replace the placeholders in the code with your Wi-Fi credentials (`ssid` and `password`).
4. Upload the sketch to your ESP8266 board.
5. Open the Serial Monitor to see the connection status and IP address.
6. Connect your relays to the respective GPIO pins (Relay1 -> GPIO 2, Relay2 -> GPIO 0).

## How It Works

The code sets up an asynchronous web server on port 80, allowing you to access it through your web browser. The server serves an HTML page with two toggle switches, one for each relay. When you toggle the switches on the web page, it sends a request to the ESP8266 to update the relay state. The relays' output pins are set to either HIGH or LOW, depending on the state received from the web page.

## Functions

- `connectify(const char* network, const char* pass)`: Connects the device to the specified Wi-Fi network.
- `outputState(int output)`: Checks the state of the given output (relay) and returns the corresponding "checked" or empty string for HTML rendering.
- `processor(const String& var)`: Custom processor function to render the HTML page with the relay status switches.
- `setup()`: Initializes the output pins, connects to Wi-Fi, and starts the web server to serve the HTML page.
- `loop()`: Empty loop as the server operates asynchronously.




## Author

- Aman Shaikh
- Contact: amanshaikhw@gmail.com

## License

This project is licensed under the [MIT License](LICENSE).
