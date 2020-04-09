#include <SPI.h>                  // spi header file
#include <Wire.h>
#include <Adafruit_GFX.h>         // Graphic libraries for display
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128          // OLED display width, in pixels
#define SCREEN_HEIGHT 64          // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int inPin[7] = {2,3,4,5,6,7,8};   // input pins
int val[7];
int currentValue;                 // declaraing an interger

void setup()                      // first function that executes
{
  Serial.begin(9600); //setting the communication 

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  for(int i =0;i<7;i++)
  {
    pinMode(inPin[i], INPUT);    // sets the digital pin 7 as input  
  }
}

void loop()                      // code written inside this keeps on running in a loop
{
  display.clearDisplay();        // clearing the display
  display.setTextColor(WHITE);   // setting color to white
  display.setCursor(0,15);       // setting position to print
  display.print("Maximum Occupancy:10");  // prints on display
  display.setCursor(0,40);       // setting position to print
  display.print("Current Occupancy:");    // prints on display
  display.display();             // displays everything
  getInput();                    // goes to that function
  density(currentValue);         // goes to the function with that value
  delay(2000);                   // waits for 2000 ms
}

void getInput()                  // getinput function
{
  currentValue++;                // increments value
  if(currentValue>10)            // if statement
    currentValue=0;
  /*for(int i =0; i<7; i++){
    val[i] = digitalRead(inPin[i]);   // read the input pin
    }   
   currentValue = val[0];
   int multiple = 2;
   int index;
   for(int i=1;i<7;i++){
    index = val[i] * multiple;
    currentValue = currentValue+index;
    multiple = multiple*2;
    }*/
}

void density(int i)              // density function with an integer i
{  
  display.setCursor(108,40);     // setting position to print
  display.print(i);              // prints on display
  display.display();             // displays everything
}
