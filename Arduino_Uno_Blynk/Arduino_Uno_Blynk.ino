// LED Blink example for ESP8266 (ESP-01) module
 
#define LED        2               // LED is connected to GPIO2
 
void setup() {
 
  pinMode(LED, OUTPUT);            // Configure LED pin as output
 
}
 
void loop() {
 
  digitalWrite(LED, HIGH);          // Turn the LED on
  delay(500);                       // wait 1/2 second
  digitalWrite(LED, LOW);           // turn the LED off
  delay(500);                       // wait 1/2 second
 
}
