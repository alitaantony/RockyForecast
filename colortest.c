const int s0 = 5;  // GPIO 5 (D1)
const int s1 = 4;  // GPIO 4 (D2)
const int out = 15; // GPIO 15 (D8)
const int s2 = 0;  // GPIO 0 (D3)
const int s3 = 2;  // GPIO 2 (D4)

int red, blue, green, white;

void setup() {  
  Serial.begin(9600); 
  
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  

  // Set frequency scaling (recommended settings)
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
}  

void loop() {  
  color();
  delay(500);
  Serial.println();
}


void color() {    
  // Read red
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  delay(50); 
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Read blue
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH); 
  delay(50);  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Read green
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);  
  delay(50);  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  // Read white (optional, if needed)
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);  
  delay(50);  
  white = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  
  // Print the RGB values
  Serial.print("Red: ");
  Serial.print(red);
  Serial.print(" | Blue: ");
  Serial.print(blue);
  Serial.print(" | Green: ");
  Serial.print(green);
  Serial.print(" | White: ");
  Serial.println(white);

  // Color recognition (optional, can be removed if not needed)
  if (red < blue && red < green) {
    Serial.println("Detected Color: Red");
  } else if (blue < red && blue < green) {
    Serial.println("Detected Color: Blue");
  } else if (green < red && green < blue) {
    Serial.println("Detected Color: Green");
  } else if (white < 10) {
    Serial.println("Detected Color: White");
  } else {
    Serial.println("Detected Color: Not Defined");
  }
}
