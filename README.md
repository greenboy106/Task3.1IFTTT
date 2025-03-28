1. Hardware Setup Explanation
In this project, I used an ESP32 microcontroller and a Light Dependent Resistor, or LDR, to measure sunlight exposure for a terrarium.

The LDR is connected in a voltage divider circuit with a 10kΩ resistor. One end of the LDR is connected to 3.3V, and the other end is connected to both the analog input pin (GPIO 34) and to a resistor. The other end of the resistor is connected to ground.

This setup allows the ESP32 to read voltage changes caused by varying light levels. When there’s sunlight, the resistance of the LDR decreases, resulting in a higher voltage being read by the ESP32. When it gets darker, the resistance increases and the voltage drops.

2. Software Code Explanation
The software is written in Arduino C++ using the Arduino IDE. The ESP32 first connects to Wi-Fi using the WiFi library. It then continuously reads the analog value from the light sensor pin.

I set a light threshold value to determine when sunlight is considered “on” or “off.” If the light level goes above this threshold and sunlight was previously off, the ESP32 sends a web request to IFTTT to trigger a notification for "sunlight on." If the light level drops below the threshold and sunlight was previously on, it triggers another IFTTT event for "sunlight off."

The HTTPClient library is used to send simple GET requests to IFTTT’s Webhooks service, passing the event name and my personal IFTTT key.

3. Working System Explanation
When the system is running, it checks light levels every 10 seconds. If sunlight is detected, it triggers a notification using IFTTT. This notification can be sent to my phone, email, or any other supported service.

For example, when I shine a light on the sensor, the ESP32 detects the change, prints the light level to the Serial Monitor, and triggers the "sunlight_on" webhook. When I block the light, it sends the "sunlight_off" webhook.

This allows me to monitor how much sunlight my terrarium is getting in real time, helping me make sure the plants receive enough light each day.
