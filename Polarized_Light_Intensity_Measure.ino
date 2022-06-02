#include "Measures.h"
#include "Laser.h"
using Volt = double;

#define RESISTOR_PIN A2
#define LASER_PIN_DIGITAL1 10
#define LASER_PIN_DIGITAL2 11
#define SERIAL_BAUD_RATE 9600U

#include "Languages/English.h"

#define MEASURES_PER_ITERATION 20
#define NUMBER_OF_ITERATIONS 20
#define DELAY_BETWEEN_SETS 2000
#define DELAY_LASER 10


Volt ReadVoltage() 
{
  return ReadVoltagePercentage() * 5.00;
}
Volt ReadVoltagePercentage() 
{
  return (Volt)analogRead(RESISTOR_PIN) / 1024.00;
}


Volt InputArray[MEASURES_PER_ITERATION];
Volt MediumValues[NUMBER_OF_ITERATIONS];
String SerialInput;
int typedReadCount = 0;
Laser laser(LASER_PIN_DIGITAL1, LASER_PIN_DIGITAL2);

Volt MakeMeasures()
{
  Serial.println(MEASURING);
  for (int i = 0; i < NUMBER_OF_ITERATIONS; i++)
  {
      Serial.print(i + 1);
      Serial.print(OF);
      Serial.print(NUMBER_OF_ITERATIONS);
      laser.Start();
      delay(DELAY_LASER);
      MediumValues[i] = Measure::TakeGroup<Volt>(InputArray, MEASURES_PER_ITERATION, ReadVoltage);
      delay(DELAY_LASER);
      laser.Stop();
      Serial.print("  ->\t ");
      Serial.println(MediumValues[i], 4);
      delay(DELAY_BETWEEN_SETS);
  }
  Volt BestValue = Average<Volt>(MediumValues, 0, NUMBER_OF_ITERATIONS);
  Serial.print(Measure::DrawGraph<Volt>(MediumValues, NUMBER_OF_ITERATIONS));
  Serial.println();
  Serial.print(BEST_VALUE);
  Serial.println(BestValue, 4);
  return BestValue;
}
void Calibrate()
{
  laser.Start();
  Serial.println(CALIBRATE);
  bool bCalibrating = true;
  String SerialInputCalibration;
  while (bCalibrating)
  {
    if (Serial.available()) {
      SerialInputCalibration += Serial.readStringUntil('\n');
    } else {
      delay(50);
    }
    if (SerialInputCalibration.indexOf(END_UPPER) >= 0 || SerialInputCalibration.indexOf(END_LOWER) >= 0)
    {
      bCalibrating = false;
    }
  }
  laser.Stop();
}
void ClearVariables()
{
  SerialInput = "";
  typedReadCount = 0;
  memset(InputArray, 0, MEASURES_PER_ITERATION * sizeof(Volt));
  memset(MediumValues, 0, NUMBER_OF_ITERATIONS * sizeof(Volt));
}
void MakeMultipleMeasures(int count)
{
  if (count <= 0)
    return;
  Volt* Results = (Volt*)malloc(sizeof(Volt) * count);
  for (int i = 0; i < count; i++)
  {
    Results[i] = MakeMeasures();
    Serial.println(WAIT_FOR_GO);
    if (i + 1 < count)
    {
      bool bWaiting = true;
      String SerialInputCalibration;
      while (bWaiting)
      {
        if (Serial.available()) {
          SerialInputCalibration += Serial.readStringUntil('\n');
        } else {
          delay(50);
        }
        if (SerialInputCalibration.indexOf(END_UPPER) >= 0 || SerialInputCalibration.indexOf(END_LOWER) >= 0)
        {
          return;
        }
        if (SerialInputCalibration.indexOf(GO_UPPER) >= 0 || SerialInputCalibration.indexOf(GO_LOWER) >= 0)
        {
          bWaiting = false;
        }
      }
    }
  }
  Serial.println(GROUP_RESULT);
  for (int i = 0; i < count; i++)
  {
    Serial.println(Results[i], 4);
  }
  free(Results);
}
void setup()
{
  ClearVariables();
  //A serial stream is needed
  while (!Serial)
  {
    delay(100);
  }
  Serial.begin(SERIAL_BAUD_RATE);
  Serial.setTimeout(2000U);
  Serial.println(SETUP_COMPLETED);
  Serial.println(REMINDER);
}
void loop()
{
  if (Serial.available()) {
    SerialInput += Serial.readStringUntil('\n');
  } else {
    delay(30);
    typedReadCount++;
    if (typedReadCount > 250) {
      Serial.println(REMINDER);
      typedReadCount = 0;
    }
  }
  if (SerialInput.indexOf(READ_UPPER) >= 0 || SerialInput.indexOf(READ_LOWER) >= 0)
  {
    ClearVariables();
    MakeMeasures();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println(REMINDER);
  }
  if (SerialInput.indexOf(CALIBRATE_UPPER) >= 0 || SerialInput.indexOf(CALIBRATE_LOWER) >= 0)
  {
    ClearVariables();
    Calibrate();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println(REMINDER);
  }
  if (SerialInput.indexOf(MULTIPLE_UPPER) >= 0 || SerialInput.indexOf(MULTIPLE_LOWER) >= 0)
  {
    ClearVariables();
    Calibrate();
    Serial.println();
    Serial.println();
    Serial.println();
    Serial.println(REMINDER);
  }
}
