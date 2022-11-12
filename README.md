# ESP2866-Open-Meteo
Using a simple Microcontroller based on the ESP-12F to read the weather using https://open-meteo.com

## Example output from serial
`
[HTTPS] begin...
[HTTPS] GET...
[HTTPS] GET... code: 200
{"latitude":52.52,"longitude":13.419998,"generationtime_ms":0.28896331787109375,"utc_offset_seconds":0,"timezone":"GMT","timezone_abbreviation":"GMT","elevation":38.0,"current_weather":{"temperature":9.0,"windspeed":4.1,"winddirection":105.0,"weathercode":2,"time":"2022-11-12T17:00"}}
Wait 10s before next round...
`