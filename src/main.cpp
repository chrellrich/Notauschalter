/**
 * This example turns the ESP32 into a Bluetooth LE keyboard that writes the words, presses Enter, presses a media key and then Ctrl+Alt+Delete
 */
#include <Arduino.h>
#include <BleKeyboard.h>

#define pushButton_pin 14

BleKeyboard bleKeyboard("Notauschalter", "C.Ellrich", 100);

bool buttonPressed = false;

void IRAM_ATTR sendLockCommand()
{
  buttonPressed = true;
}

void setup() {
  pinMode(pushButton_pin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(pushButton_pin, sendLockCommand, FALLING);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();
}

void loop() {
  if (buttonPressed)
  {
    Serial.println("Sending WIN+L");
    bleKeyboard.press(KEY_LEFT_GUI);
    bleKeyboard.press('l');
    bleKeyboard.releaseAll();
    buttonPressed = false;
  }
  
}