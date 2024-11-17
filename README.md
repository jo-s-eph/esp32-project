# Arduino Spotify Controller

This project is an Arduino-based Spotify controller that allows you to display the currently playing track on an LCD screen and add the track to your liked songs using a button.

## Components

- Arduino board
- LCD screen (I2C)
- Button
- WiFi module (if not integrated)
- Necessary wiring and breadboard

## Setup

1. **Clone the repository:**
    ```sh
    git clone <repository_url>
    cd <repository_directory>
    ```

2. **Install necessary libraries:**
    - `WiFi.h`
    - `HTTPClient.h`
    - `ArduinoJson.h`
    - `LiquidCrystal_I2C.h`

3. **Configure WiFi:**
    Update the WiFi credentials in `main.ino`:
    ```ino
    const char* ssid = "WIFI_SSID";
    const char* password = "WIFI_PASSWORD";
    ```

4. **Get Spotify Access Token:**
    Update the Client credentials in `get_token.py`:
    ```py
    CLIENT_ID = "CLIENT_ID"
    CLIENT_SECRET = "CLIENT_SECRET"
    ```
    Follow the steps in `get_token.py` to obtain your Spotify access token and update `main.ino`:
    ```ino
    const char* access_token = "PASTE_ACCESS_TOKEN_HERE";
    ```

5. **Upload the code:**
    Upload the `main.ino` file to your Arduino board.

## Usage

1. **Power the Arduino:**
    Connect your Arduino to a power source.

2. **Connect to WiFi:**
    The Arduino will automatically connect to the configured WiFi network.

3. **Display Current Track:**
    The currently playing track will be displayed on the LCD screen.

4. **Like a Track:**
    Press the button to add the currently playing track to your liked songs on Spotify.

## Files

- `main.ino`: Main Arduino code.
- `get_token.py`: Script to obtain Spotify access token.
- `spotify.h`: Header file for Spotify API functions.
- `spotify.cpp`: Implementation of Spotify API functions.

## License

This project is licensed under the MIT License.

## Acknowledgements

- [ArduinoJson](https://arduinojson.org/)
- [LiquidCrystal_I2C](https://github.com/johnrickman/LiquidCrystal_I2C)
