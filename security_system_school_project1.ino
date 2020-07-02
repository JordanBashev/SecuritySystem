#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Wire.h> 
#include <Servo.h>

LiquidCrystal lcd(9,8,10,11,12,13);

Servo servo;

long NewPass = 0;
long storedpass = 0;
long ResPassCombination = 2345523;
  
char customKey;
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {7,6,5,4}; //rows keypad
byte colPins[COLS] = {3,2,1,0}; //columns keypad

//Connects with the Keypad
Keypad customKeypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS); 

void ResetingPassword()
{
  customKey = 'C';
  switch(customKey)
  {
     case 'C'://Reset's password
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Password must be 9 charachters long");
       //Moves the display to the left
       for (int positionCounter = 0; positionCounter < 40; positionCounter++)
       {
          lcd.scrollDisplayLeft();
          delay(150);
       }
       //Moves the display to the right
       for (int positionCounter = 29; positionCounter < 29; positionCounter++)
       {
          lcd.scrollDisplayRight();
          delay(150);
          lcd.noDisplay();
       }
       delay(4000);
       lcd.clear();
       lcd.setCursor(0,0);
       lcd.print("Press A to Confirm once you are done");
       //Moves the display to the left
       for (int positionCounter = 0; positionCounter < 40; positionCounter++)
       {
          lcd.scrollDisplayLeft();
          delay(150);
       }
       //Moves the display to the right
       for (int positionCounter = 29; positionCounter < 29; positionCounter++) 
       {
          lcd.scrollDisplayRight();
          delay(150);
          lcd.noDisplay();
       }
       delay(2000);
       lcd.clear();
       storedpass = 0;
       NewPass = 0;
       lcd.setCursor(0,0);
    break;
  }
}
  

void setup()
{
  //Start's the servo motor
  servo.attach(14);
  servo.write(91);
  lcd.begin(16,2);
}

void loop()
{                      
  customKey = customKeypad.getKey();
  switch(customKey)
  {
    case '0' ... '9'://Writes on the lcd
      lcd.setCursor(0,0);
      NewPass = NewPass * 10 + (customKey - '0');
      lcd.print(NewPass);
    break;
    
    case 'A'://Create new password
      lcd.setCursor(0,0);
      if(NewPass == 0)
      {      
        lcd.print("New Password must");
        lcd.setCursor(0,1);
        lcd.print("be 9 char long");
        delay(2000);
        lcd.clear();
      }
      else
      {
        if(storedpass > 0)
        {
          lcd.print("Password is already set");
          //Moves the display to the left
          for (int positionCounter = 0; positionCounter < 40; positionCounter++) 
          {
             lcd.scrollDisplayLeft();
             delay(150);
          }
          //Moves the display to the right
          for (int positionCounter = 29; positionCounter < 29; positionCounter++)
          {
             lcd.scrollDisplayRight();
             delay(150);
             lcd.noDisplay();
          }
          delay(1000);
          lcd.clear();
          NewPass = 0;
          lcd.setCursor(0,0);
        }
        else
        {
          storedpass = NewPass; 
          lcd.print("This is your");
          lcd.setCursor(0,1);
          lcd.print("new password");
          delay(2000);
          lcd.clear();
          lcd.print(storedpass);
          delay(6000);
          lcd.clear();
          NewPass = 0;
        }
      }  
    break;
    
    case 'B'://Prepares password for reset
      lcd.setCursor(0,0);
      lcd.print("Reset your ");
      lcd.setCursor(0,1);
      lcd.print("password");
      delay(2000);
      lcd.clear();
      if(NewPass == 234)
      {
        ResetingPassword();
      }
      lcd.setCursor(0,0);
      lcd.print("Press D to");
      lcd.setCursor(0,1);
      lcd.print("Return");
      lcd.clear();
    break;
    
    case 'D'://Clears lcd(Back Button)
      lcd.clear();
    break;
    
    case '#'://(Okey button) checks if the password is correct
             //If no sound's the alarm
             //else unlocks the door
      if(storedpass == NewPass)
      {
        lcd.clear();
        lcd.print("Password");
        lcd.setCursor(0,1);
        lcd.print("Accepted");
        servo.write(0);
        delay(2000);  
        lcd.clear();
        NewPass = 0;
      }
      else
      {
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Password");
        lcd.setCursor(0,1);
        lcd.print("Denied");
        tone(15,2000);
        delay(2000);
        lcd.clear();
        noTone(15);
        NewPass = 0;
      }
    break;
    
    case '*'://Clears lcd and reset's typed numbers
      NewPass = 0;
      lcd.clear();
    break;
  }
}















