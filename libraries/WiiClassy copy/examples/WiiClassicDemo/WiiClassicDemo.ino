/*
WiiClassic Test Code

This code prints the current controller status to the serial port.
Button pressed calls poll whether the button was pressed since the last update call.
as a result, it will just briefly print the last button pressed once.

Tim Hirzel May 2008

*/

#include <Wire.h>       //include the Wire/I2C Library
#include <WiiClassy.h>  //include the WiiClassy Libary

WiiClassy classy = WiiClassy(); //start an instance of the WiiClassy Library

void setup() 
{
  Serial.begin(9600); //sstart serial port at 9600bps
  delay(100);
  classy.init();  //start classy library
  delay(100);
  classy.update();  //read data from the classic controller
}

void loop() 
{
  classy.update();//read data from the classic controller
  
  /* 
  //left shoulder pressure not used by Robotgeek system
  Serial.print(" left shoulder: ");
  Serial.print(classy.leftShoulderPressure);
  
  Serial.print(" right shoulder: ");
  Serial.print(classy.rightShoulderPressure);
  */
  Serial.print(" left stick x: ");
  Serial.print(classy.leftStickX);
  
  Serial.print(" left stick y: ");
  Serial.print(classy.leftStickY);
  
  Serial.print(" right stick x: ");
  Serial.print(classy.rightStickX);
  
  Serial.print(" right stick y: ");
  Serial.print(classy.rightStickY);
  
  
  Serial.print("Buttons:");
  
  
  
  if (classy.leftShoulderPressed == true) {
  Serial.print("LS.");
  }
  if (classy.rightShoulderPressed == true) {
  Serial.print("RS.");
  }
  if (classy.lzPressed == true) {
  Serial.print("lz.");
  }
  if (classy.rzPressed == true) {
  Serial.print("rz.");
  }
  if (classy.leftDPressed == true) {
  Serial.print("LD.");
  }
  
  if (classy.rightDPressed == true) {
  Serial.print("RD.");
  }
  
  if (classy.upDPressed == true) {
  Serial.print("UD.");
  }
  if (classy.downDPressed == true) {
  Serial.print("DD.");
  }
  
  if (classy.selectPressed == true) {
  Serial.print("select.");
  }
  
  if (classy.homePressed == true) {
  Serial.print("home.");
  }
  if (classy.startPressed == true) {
  Serial.print("start.");
  }
  
  if (classy.xPressed == true) {
  Serial.print("x.");
  }
  
  if (classy.yPressed == true) {
  Serial.print("y.");
  }
  
  if (classy.aPressed == true) {
  Serial.print("a.");
  }
  
  if (classy.bPressed == true) {
  Serial.print("b.");
  }
  
  
  Serial.println("---");
  
  
  
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
  
  delay(500); // delay to ease the serial terminal output


}
