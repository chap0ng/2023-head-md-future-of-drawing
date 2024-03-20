//ESP32_COLOR_SENSING_TUTORIAL_DIY_CHEAP_PERFECT

const int s0 = 19;  
const int s1 = 18;
const int out = 15;  
const int s2 = 2;  
const int s3 = 4;  

int red,blue,green,white;

//DIY_CHEAP_PERFECT

void setup()   
{  
  Serial.begin(9600); 
  Serial.println("ESP32 COLOR SENSING TUTORIAL By- DIY CHEAP PERFECT");
  pinMode(s0, OUTPUT);  
  pinMode(s1, OUTPUT);  
  pinMode(s2, OUTPUT);  
  pinMode(s3, OUTPUT);  
  pinMode(out, INPUT);  
  digitalWrite(s0, HIGH);  
  digitalWrite(s1, HIGH);  
}  

//DIY_CHEAP_PERFECT

void loop() 
{  
  color();
  delay(500);
  Serial.println();
}

//DIY_CHEAP_PERFECT

void color()  
{    
  //red
  digitalWrite(s2, LOW);  
  digitalWrite(s3, LOW);   
  delay(50); 
  red = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  //blue
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH); 
  delay(50);  
  blue = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  //green
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);  
  delay(50);  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);

  //white
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);  
  delay(50);  
  green = pulseIn(out, digitalRead(out) == HIGH ? LOW : HIGH);
  
  //color_recognition
  if(red<blue && red<green)
  Serial.println("color: Red");
  else if(blue<red && blue<green)
  Serial.println("color: Blue");
  else if(green<red && green<blue)
  Serial.println("color: Green");
  else if(white<10)
  Serial.println("color: White");
  else
  Serial.println("color: Not Defined");

}

//DIY_CHEAP_PERFECT
