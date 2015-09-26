void setup() {
  Serial.begin(9600);
  
  int a; //integer a, automatically set to 0
  int b = 3; //integer b, manually set to 3
  int c; //intever c, automatically set to 0
  printVariables(a, b, c, 1);
 
  Serial.println("Setting 'a' to '2' ");
   a = 2; //set variable a to 2
  printVariables(a, b, c, 2);

  Serial.println("Adding 'a' and 'b' ");
  c = add(a, b);
  printVariables(a, b, c, 3);  
}

void loop() {
  // put your main code here, to run repeatedly: 
  
}

void printVariables(int variableA, int variableB,  int variableC, int printNumber)
{
  Serial.print("Print # ");
  Serial.print(printNumber);
  Serial.print(": ");
  Serial.print("a = ");
  Serial.print(variableA);
  Serial.print(" b = ");
  Serial.print(variableB);
  Serial.print(" c = ");
  Serial.println(variableC);
  return;
}

int add(int variableA, int variableB)
{
  int variableC = variableA + variableB;
  return(variableC);
}
