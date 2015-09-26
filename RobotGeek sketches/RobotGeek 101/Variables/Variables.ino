void setup() {
  Serial.begin(9600);
  
  int a; //integer a, automatically set to 0
  int b = 3; //integer b, manually set to 3
  int c; //intever c, automatically set to 0
  Serial.print("Print # 1: ");
  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);
  
  
  Serial.println("Setting 'a' to '2' ");
  a = 2; //set variable a to 2
  Serial.print("Print # 2: ");
  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);
  
  
  Serial.println("Adding 'a' and 'b' ");
  c = a + b;
  Serial.print("Print # 3: ");
  Serial.print("a = ");
  Serial.print(a);
  Serial.print(" b = ");
  Serial.print(b);
  Serial.print(" c = ");
  Serial.println(c);
    

}

void loop() {
  // put your main code here, to run repeatedly: 
  
}
