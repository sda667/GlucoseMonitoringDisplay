#include <UTFTGLUE.h>

UTFTGLUE myGLCD(0, A2, A1, A3, A4, A0); // all dummy args

void setup()
{
  randomSeed(analogRead(0));
  myGLCD.InitLCD();
  Serial.begin(9600);
}
void drawScale()
{
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawLine(27, 220, 27, 20); // Vertical line

  // Draw scale lines and labels
  for (int i = 0; i <= 20; i++)
  {
    int y = 220 - i * 10;
    myGLCD.drawLine(20, y, 25, y);  
    myGLCD.printNumI(i * 10, 5, y - 4); // Label
  }
}
void drawBox(int x, int y, int width, int height, int value, const char *qualifier) {
  // Draw the box
  if (strcmp(qualifier,"High")){
      myGLCD.setColor(0,255, 0);
  }
  else{
    myGLCD.setColor(255, 0, 0);
  }
  //myGLCD.fillRect(x, y, x + width, y + height);

  // Draw the value
  
  
  myGLCD.setFont(BigFont);
  myGLCD.printNumI(value, x + 60, y + 40);
  myGLCD.print("mg/dl", x + 110, y + 40);

  // Draw the qualifier
  myGLCD.setFont(SmallFont);
  myGLCD.print(qualifier, x + 100, y + 80);
  myGLCD.setFont(SmallFont);
}

void loop()
{
  myGLCD.setFont(SmallFont);
  int numPoints = 10;
  int xScale = 35;
  int yScale = 1;
  int threshold = 120;

  int data[numPoints];

  // Generate random glucose level data (replace this with your actual data source)
  for (int i = 0; i < numPoints; i++)
  {
    data[i] = random(80, 150); // Random values between 80 and 120 (adjust as needed)
  }

  myGLCD.clrScr();
  myGLCD.setColor(255, 255, 255);
  drawScale();
  //myGLCD.drawLine(10, 120, 310, 120);
  //myGLCD.drawLine(10, 10, 10, 120);
  

  for (int i = 0; i < numPoints - 1; i++)
  {
    int x1 = 26 + i * xScale;
    int y1 = 120 - (data[i]-100) * yScale;
    int x2 = 26 + (i + 1) * xScale;
    int y2 = 120 - (data[i + 1]-100) * yScale;
      if ((data[i] + data[i + 1]) / 2 < threshold -5)
    {
      myGLCD.setColor(0, 255, 0); // Green if under the threshold
    }
    else if ((data[i] + data[i + 1]) / 2 <= threshold+5 &&   threshold -5 <=(data[i] + data[i + 1]) / 2 )
    {
      myGLCD.setColor(255, 255, 0); // Yellow if within the threshold
    }
    else // if ((data[i] + data[i + 1]) / 2 > threshold)
    {
      myGLCD.setColor(255, 0, 0); // Red if over the threshold
    }
    

    myGLCD.drawLine(x1, y1, x2, y2);

    Serial.print("data ");
    Serial.println(data[i]);
    
  }

  delay(5000);
  myGLCD.clrScr();
  myGLCD.setColor(255, 255, 255);
  int currentValue = data[numPoints - 1]; // Get the last value for demonstration
  const char *qualifier = (currentValue < threshold+5) ? "Normal" : "High"; // Adjust as needed

  // Draw the box with the value and qualifier
  drawBox(40, 40, 240, 160, currentValue, qualifier);
  delay(5000);
  myGLCD.clrScr();

}
   
