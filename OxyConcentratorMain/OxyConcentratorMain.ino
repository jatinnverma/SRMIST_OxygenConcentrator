#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
float mv;
float per;

// RELAY PIN ASSIGNMENT
//**************************************************************************
int Sieve_A_Valve = 5; //Defined Pin as Variable
int Sieve_B_Valve = 6; //Defined Pin as Variable
int PreCharge_Valve = 7; //Defined Pin as Variable
int Fan = 8; //Defined Pin as Variable

// VARIABLE CREATION
//**************************************************************************
unsigned long Relay_Test_Delay; //delay variable creation
unsigned long Startup_Purge_Delay; //delay variable creation
unsigned long Production_Delay; //delay variable creation
unsigned long Flush_Delay; //delay variable creation
unsigned long PreCharge_Delay; //delay variable creation

//**************************************************************************
void setup()
{


  // STARTUP
  //**************************************************************************
  // Serial Port initialization
  Serial.begin(9600);
  ads.begin();
  Serial.println("ADC Active. . . .Program Starting.");
  // SET PIN MODE FOR PINS IN PROGRAM
  //**************************************************************************
  pinMode(Sieve_A_Valve, OUTPUT);
  pinMode(Sieve_B_Valve, OUTPUT);
  pinMode(PreCharge_Valve, OUTPUT);
  pinMode(Fan, OUTPUT);


  //  SET DELAY TIMING HERE
  //**************************************************************************
  Relay_Test_Delay = 0;
  Startup_Purge_Delay = 1000;
  Production_Delay = 4000;
  Flush_Delay = 450;
  PreCharge_Delay = 700;

  // VALVE RELAY TEST SEQUENCE
  //**************************************************************************
  Serial.println("Relay Test Sequence");
  digitalWrite(Sieve_A_Valve, HIGH); //Turn on relay
  delay(Relay_Test_Delay);
  digitalWrite(Sieve_B_Valve, HIGH); //Turn on relay
  delay(Relay_Test_Delay);
  digitalWrite(PreCharge_Valve, HIGH); //Turn on relay
  delay(Relay_Test_Delay);
  Serial.println("Valve Relay Test Sequence Complete");
  delay(Relay_Test_Delay);


  // STARTUP PURGE
  //**************************************************************************
  Serial.println("Relay Test Sequence");
  digitalWrite(Sieve_A_Valve, HIGH); //Turn on relay
  digitalWrite(Sieve_B_Valve, HIGH); //Turn on relay
  digitalWrite(PreCharge_Valve, HIGH); //Turn on relay
  delay(Startup_Purge_Delay);


  // FAN CONTROL
  //**************************************************************************
  Serial.println("Program Starting...");
  delay(Relay_Test_Delay);
  digitalWrite(Fan, HIGH);
  Serial.println("Fan Switched On");
}

void loop()
{
  int16_t results;
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */
  results = ads.readADC_Differential_0_1();  
  mv = results * multiplier;
  per=map(mv,12,70,21,100);
  Serial.print("Voltage: "); Serial.print(mv); Serial.print("mv  ("); Serial.print(per); Serial.println("%)");

  //CYCLE 1
  //**************************************************************************
  Serial.println("Sieve A Charge / Sieve B Purge");
  digitalWrite(Sieve_A_Valve, HIGH);
  digitalWrite(Sieve_B_Valve, LOW);
  digitalWrite(PreCharge_Valve, LOW);
  delay(Production_Delay);
  
  results = ads.readADC_Differential_0_1();  
  mv = results * multiplier;
  per=map(mv,12,70,21,100);
  Serial.print("Voltage: "); Serial.print(mv); Serial.print("mv  ("); Serial.print(per); Serial.println("%)");


  //CYCLE 2
  //**************************************************************************
  Serial.println("Sieve A Charge / Sieve B Purge / Flush/PreCharge");
  digitalWrite(Sieve_A_Valve, HIGH);
  digitalWrite(Sieve_B_Valve, LOW);
  digitalWrite(PreCharge_Valve, HIGH);
  delay(Flush_Delay) ;
 

  //CYCLE 3
  //**************************************************************************
  Serial.println("Sieve A Charge / Sieve B Charge / Flush/PreCharge");
  digitalWrite(Sieve_A_Valve, HIGH);
  digitalWrite(Sieve_B_Valve, HIGH);
  digitalWrite(PreCharge_Valve, HIGH);
  delay(PreCharge_Delay);
  
  
  //CYCLE 4
  //**************************************************************************
  Serial.println("Sieve A Purge / Sieve B Charge");
  digitalWrite(Sieve_A_Valve, LOW);
  digitalWrite(Sieve_B_Valve, HIGH);
  digitalWrite(PreCharge_Valve, LOW);
  delay(Production_Delay);

  results = ads.readADC_Differential_0_1();  
  mv = results * multiplier;
  per=map(mv,12,70,21,100);
  Serial.print("Voltage: "); Serial.print(mv); Serial.print("mv  ("); Serial.print(per); Serial.println("%)");

  //CYCLE 5
  //**************************************************************************
  Serial.println("Sieve A Purge / Sieve B Charge / Flush/PreCharge");
  digitalWrite(Sieve_A_Valve, LOW);
  digitalWrite(Sieve_B_Valve, HIGH);
  digitalWrite(PreCharge_Valve, HIGH);
  delay(Flush_Delay);


  //CYCLE 6
  //**************************************************************************
  Serial.println("Sieve A Charge / Sieve B Charge / Flush/PreCharge");
  digitalWrite(Sieve_A_Valve, HIGH);
  digitalWrite(Sieve_B_Valve, HIGH);
  digitalWrite(PreCharge_Valve, HIGH);
  delay(PreCharge_Delay) ;

}
