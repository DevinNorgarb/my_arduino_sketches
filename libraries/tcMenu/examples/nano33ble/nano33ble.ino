/**
 * @file nano33ble.ino
 * An example of using tcMenu with the Nano33BLE Sense. This example uses some of the sensors on-board the device
 * along with an I2C LCD backpack based display and a rotary encoder. Although this is pre-generated for you, you
 * can load the example's emf file into TcMenu Designer and take a look around or re-build it.
 *
 * You can get or adjust the pin configurations by loading the emf file into the designer
 */

#include "nano33ble_menu.h"
#include "SensorManager.h"
#include "MotionDetection.h"
#include <AnalogDeviceAbstraction.h>

// on the analog menu, we both have an analog input and an analog output (PWM). You can configure those pins here.
const int analogInputPin = A0;
const int pwmOutputPin = 2;

// We work with analog input and output here, so we use an analog device to make it easier. It provides the ability
// to treat analog values as floats between 0..1 on any supported platform.
ArduinoAnalogDevice analogDevice;

// We create a class extending Executable for the temprature, humidity, and pressure sensors that are built in
SensorManager sensorManager;

// We create an event class extending BaseEvent to manage the motion detection
MotionDetection motionDetection;

void setup() {
    // First we set up the analog pins
    analogDevice.initPin(pwmOutputPin, DIR_OUT);
    analogDevice.initPin(analogInputPin, DIR_IN);

    // and set up the menu itself, so it starts displaying and accepting input
    setupMenu();

    // then we initialise our sensor and motion detection and register with task manager.
    sensorManager.initialise();
    motionDetection.initialise();
    taskManager.registerEvent(&motionDetection);
    taskManager.scheduleFixedRate(1, &sensorManager, TIME_SECONDS);

    // lastly we set up something simple to read from analog in
    taskManager.scheduleFixedRate(100, [] {
       menuAnalogReadingsInA0.setFloatValue(analogDevice.getCurrentFloat(analogInputPin));
    });
}

// All TaskManager sketches must call runLoop very often from the loop method, you should not use any delays.
void loop() {
    taskManager.runLoop();
}

// And something to change the PWM output when the PWM menu item changes
void CALLBACK_FUNCTION onPWMChanged(int id) {
    auto newPwm = menuAnalogReadingsOutputPWM.getCurrentValue() / 100.0F;
    analogDevice.setCurrentFloat(pwmOutputPin, newPwm);
}
