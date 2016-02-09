/*
WiiClassic Test Code

This code prints the current controller status to the serial port.
Button pressed calls poll whether the button was pressed since the last update call.
as a result, it will just briefly print the last button pressed once.

Tim Hirzel May 2008

*/


#include "Wire.h"

#include "WiiClassy.h"

WiiClassy classy = WiiClassy();

void setup() {
Serial.begin(9600);
delay(100);
classy.init();
delay(100);
classy.update();
}

void loop() {
delay(500); // 1ms is enough to not overload the wii Classic, 100ms seems to ease the serial terminal a little
classy.update();

// 
/* 
// PRINT RAW BYTES FOR DEBUG
// STATUS IS FIRST FOUR BYTES
for (int i = 0; i < 4; i ++) {
for (int j = 7; j >= 0; j--) {
if ((classy.getRawStatus()[i] & (1 << j)) == 0) {
Serial.print("0");
}
else{
Serial.print("1");
}
}
Serial.println();
}
// BUTTONS IS NEXT TWO BYTES
for (int i = 0; i < 2; i ++) {
for (int j = 7; j >= 0; j--) {
if ((classy.getRawButtons()[i] & (1 << j)) == 0) {
Serial.print("0");
}
else{
Serial.print("1");
}
}
Serial.println();
}
Serial.println("---");
*/

Serial.print("Buttons:");


if (classy.leftShoulderPressed) {
Serial.print("LS.");
}
if (classy.rightShoulderPressed) {
Serial.print("RS.");
}
if (classy.lzPressed) {
Serial.print("lz.");
}
if (classy.rzPressed) {
Serial.print("rz.");
}
if (classy.leftDPressed) {
Serial.print("LD.");
}

if (classy.rightDPressed) {
Serial.print("RD.");
}

if (classy.upDPressed) {
Serial.print("UD.");
}
if (classy.downDPressed) {
Serial.print("DD.");
}

if (classy.selectPressed) {
Serial.print("select.");
}

if (classy.homePressed) {
Serial.print("home.");
}
if (classy.startPressed) {
Serial.print("start.");
}

if (classy.xPressed) {
Serial.print("x.");
}

if (classy.yPressed) {
Serial.print("y.");
}

if (classy.aPressed) {
Serial.print("a.");
}

if (classy.bPressed) {
Serial.print("b.");
}

Serial.println();
Serial.print("right shoulder: ");
Serial.println(classy.rightShoulderPressure);
Serial.print(" left shoulder: ");

Serial.println(classy.leftShoulderPressure);
Serial.print(" left stick x: ");

Serial.println(classy.leftStickX);
Serial.print(" left stick y: ");

Serial.println(classy.leftStickY);
Serial.print(" right stick x: ");

Serial.println(classy.rightStickX);
Serial.print(" right stick y: ");

Serial.println(classy.rightStickY);
Serial.println("---");

}
