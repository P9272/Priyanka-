/*
                            *
                            * Project Name:     Automatic Khichadi Making and Vending Device
                            * Author List:      Priyanka Kale, Amruta Kolekar, Vishal Tidke, Shrikrishna Patait
                            * Filename:         Khichadi_Device.ino
                            * Functions:        setup(), loop(), getFingerprintIDez(),flap_ingredients1(),
                            *                   flap_ingredients2(), arm_in(), arm_out(), spoon_opened(), spoon_closed(),
                            *                   arm_stir()
                            * Global Variables: finger, servoPin1,servoPin2, servoPin3, servoPin4, 
                            *                   Servo1,Servo2,Servo3,Servo4
*/
#include <Adafruit_Fingerprint.h>
#include<Wire.h> // For I2C
#include<LCD.h> // For LCD
#include<LiquidCrystal_I2C.h> // Added library*
#include<Servo.h> 
//Set the pins on the I2C chip used for LCD connections
//ADDR,EN,R/W,RS,D4,D5,D6,D7
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the default I2C bus address of the backpack-see article

SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

// Declare the Servo pin  
int servoPin1 = 8;
int servoPin2 = 9;
int servoPin3 = 10;
int servoPin4 = 11;
// Create a servo object 
Servo Servo1,Servo2,Servo3,Servo4;

/*
                            *
                            * Function Name:  setup
                            * Input:          
                            * Output:         Initialises LCD and turns on LCD backlight, attaches all servo pins to 
                            *                 servo objects, sets all flaps and arms to their initial position,initialises 
                            *                 fingerprint sensor and asks user to enter fingerprint
                            * Logic:          Used for initial setting of the control system 
                            * Example Call:   This function is automatically called once at the starting time of            
                            *                 execution of the program. It is the first function to be called in            
                            *                 Arduino                            
                            */
void setup()  
{
  // Set off LCD module
   lcd.begin (20,4); // 16 x 2 LCD module
   lcd.setBacklightPin(3,POSITIVE); // BL, BL_POL
   lcd.setBacklight(HIGH);

    
// We need to attach the servo to the used pin number 
   Servo1.attach(servoPin1);
   Servo2.attach(servoPin2);
   Servo3.attach(servoPin3);
   Servo4.attach(servoPin4);

   Servo1.write(0); 
   Servo2.write(65);
   Servo3.write(150);
   Servo4.write(100);
   finger.begin(57600);
   delay(5);
  if (finger.verifyPassword()) {
    lcd.setCursor(0,0);
    lcd.print("Found Sensor");
  } else {
    lcd.setCursor(0,0);
    lcd.print("Didn't find sensor");
    while (1) { delay(1); }
  }

  finger.getTemplateCount();
  Serial.println("Waiting for valid finger...");
  lcd.setCursor(0,1);
  lcd.print("Enter fingerprint:");
}

/*
                            *
                            * Function Name:  loop
                            * Input:          
                            * Output:         
                            * Logic:          Calls getFingerprintIDez()function repeatedly to read finger print 
                            *                 and further cooking process
                            * Example Call:   This function is automatically called in loop at the starting time             
                            *                 of execution of the program.         
                            */
void loop()                     // run over and over again
{
  getFingerprintIDez();
  delay(50);            //don't ned to run this at full speed.
}

/*
                            *
                            * Function Name:  getFingerprintIDez
                            * Input:          Takes fingerprint image as the input
                            * Output:         Returns and prints ID of the fingerprint match found in the database and calls 
                            *                 other function to start cooking
                            * Logic:          Starts with reading the image, if an image is found then its ID is returned and displayed 
                            *                 If a valid match is found then only the functions are called to start cooking. 
                            * Example Call:   getFingerprintIDez();                        
        */
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #");
  lcd.setCursor(0,2);
  lcd.print("Found ID #");
  Serial.print(finger.fingerID); 
  lcd.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
  lcd.setCursor(0,3);
  lcd.print("Please wait");
  if(finger.fingerID!=-1)
  {
     flap_ingredients1();
     delay(2000);
     arm_in();
     delay(1000);
     spoon_opened();
     delay(1000);
     arm_stir();
     delay(1000);
     spoon_closed();
     delay(1000);
     arm_out();
     delay(1000);
     flap_ingredients2();
     delay(5000);
     arm_in();
     delay(1000);
     spoon_opened();
     delay(1000);
     arm_stir();
     delay(1000);
     spoon_closed();
     delay(1000);
     arm_out();
     delay(1000);     
  }
  return finger.fingerID; 
}
/*
                            *
                            * Function Name:  flap_ingredients1
                            * Input:          
                            * Output:         Open flap for a second to drop the ingredients
                            * Logic:          Servo pin 8 is written an angle of 0 degrees for one second 
                            *                 then the flap is opened by writing 20 degrees for one second to drop the ingredients,
                            *                 and then again brough to 0 degrees 
                            * Example Call:   flap_ingredients1();                          
        */
void flap_ingredients1()
{
   Servo1.write(0); 
   delay(1000); 
   Servo1.write(20); 
   delay(1000); 
   Servo1.write(0);
}
/*
                            *
                            * Function Name:  flap_ingredients2
                            * Input:          
                            * Output:         Open flap for a second to drop the other ingredients
                            * Logic:          Servo pin 9 is written an angle of 65 degrees for one second 
                            *                 then the flap is opened by writing 85 degrees for one second to drop the ingredients,
                            *                 and then again brough to 65 degrees 
                            * Example Call:   flap_ingredients2();                          
        */
void flap_ingredients2()
{
   Servo2.write(65); 
   delay(1000); 
   Servo2.write(85); 
   delay(1000); 
   Servo2.write(65); 
}
/*
                            *
                            * Function Name:  arm_in
                            * Input:          
                            * Output:         takes arm over the vessel
                            * Logic:          Servo pin 10 is written an angle of 150 degrees for one second 
                            *                and then the arm is taken over the vessel at an angle of 30 degrees
                            * Example Call:   arm_in();                          
        */
void arm_in()
{
   Servo3.write(150); 
   delay(1000); 
   Servo3.write(30);  
   delay(1000); 
}
/*
                            *
                            * Function Name:  arm_out
                            * Input:          
                            * Output:         takes arm out of the vessel at initial position
                            * Logic:          Servo pin 10 is written an angle of 45 degrees for one second 
                            *                and then the arm is taken out of the vessel at an angle of 150 degrees
                            * Example Call:   arm_in();                          
        */
void arm_out()
{
   Servo3.write(45); 
   delay(1000); 
   Servo3.write(150); 
   delay(1000); 
}
/*
                            *
                            * Function Name:  spoon_opened
                            * Input:          
                            * Output:         opens the spoon from the arm to stir
                            * Logic:          Servo pin 11 is written an angle of 100 degrees for one second 
                            *                and then the spoon is opened in the vessel at an angle of 0 degrees
                            * Example Call:  spoon_opened();                         
        */
void spoon_opened()
{
   Servo4.write(100); 
   delay(1000); 
   Servo4.write(0); 
   delay(1000); 
}
/*
                            *
                            * Function Name:  spoon_closed
                            * Input:          
                            * Output:         closes the spoon on the arm 
                            * Logic:          Servo pin 11 is written an angle of 0 degrees for one second 
                            *                and then the spoon is closed on the arm at an angle of 100 degrees
                            * Example Call:  spoon_closed();                         
        */
void spoon_closed()
{
   Servo4.write(0); 
   delay(1000); 
   Servo4.write(100); 
   delay(1000); 
}
/*
                            *
                            * Function Name:  arm_stir
                            * Input:          
                            * Output:         moves the arm to and fro repeatedly 
                            * Logic:          Moves the arm from 30 to 60 degrees 10 times with a delay
                            * Example Call:   arm_stir();                          
        */
void arm_stir()
{
   int i;
   for(i=1;i<=10;i++)
   {
   Servo3.write(30); 
   delay(1000); 
   Servo3.write(60); 
   delay(1000); 
   
  }
}
