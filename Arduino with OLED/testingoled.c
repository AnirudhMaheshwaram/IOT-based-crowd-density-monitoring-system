#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>                                   // libraries for graphics
#include <Adafruit_SSD1306.h>                               // libraries for establishing connection

#define SCREEN_WIDTH 128                                    // OLED display width, in pixels
#define SCREEN_HEIGHT 64                                    // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):

#define OLED_MOSI  9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

int inPin[5] = {2,3,5,6,7};                                 // pins of arduino that we are using
int val[5];
int currentValue;
void setup()                                               // runs first
{
  Serial.begin(9600);                                      //setting the communication. 

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  
  if(!display.begin(SSD1306_SWITCHCAPVCC)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);                                              // Don't proceed, loop forever
  }
  for(int i =0;i<6;i++)
  {
    pinMode(inPin[i], INPUT);                             // sets the digital pin 7 as input
    
  }
}

void loop() 
{
  display.clearDisplay();                                 // clearing the display
  display.setTextColor(WHITE);                            // setting color to white
  display.setTextSize(1);                                 // Normal 1:1 pixel scale
  display.setCursor(0,15);                                // cursor position 
  display.print("Maximum Occupancy:10");                  // prints on display 
  display.setCursor(0,40);                                // cursor position
  display.print("Current Occupancy:");                    // prints on display
  display.display();                                      // displays on screen
  getInput();                                             // goes to the function
  density(currentValue);                                  // goes to the function
  delay(1000);                                            // delay for 1000 ms
}

// function for getting function

void getInput()
{
  for(int i =0; i<5; i++)
  {
    val[i] = digitalRead(inPin[i]);                       // read the input pin
    Serial.println(val[i]);                               
    }   

    Serial.println("n\n");                                // prints the value
   currentValue = val[0];                                 
   int multiple = 2;
   int index;
   for(int i=1;i<5;i++)
   {
    index = val[i] * multiple;
    currentValue = currentValue+index;
    multiple = multiple*2;
    }
}

// function for printing number on display

void density(int i)
{  

  display.setCursor(108,40);
  display.print(i);
  display.display();
}
