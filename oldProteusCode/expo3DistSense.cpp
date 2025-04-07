// Team D1

#include <FEHBattery.h>
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <FEHMotor.h>
#include <string>
#include <cstdlib>
#include <FEHRCS.h>

#define INCH 40.5

using namespace std;

// Declarations for analog optosensors
// AnalogInputPin right_opto(FEHIO::P2_0);
// AnalogInputPin middle_opto(FEHIO::P2_1);
// AnalogInputPin left_opto(FEHIO::P2_2);

// DigitalInputPin FrontRightSwitch(FEHIO::P1_0);

AnalogInputPin cds(FEHIO::P0_2);
DigitalInputPin distSens(FEHIO::P0_3);
DigitalInputPin frontRight(FEHIO::P0_4);

//Declarations for encoders & motors
DigitalEncoder left_encoder(FEHIO::P0_0);
DigitalEncoder right_encoder(FEHIO::P0_1);
FEHMotor left_motor(FEHMotor::Motor0,9.0);
FEHMotor right_motor(FEHMotor::Motor1,9.0);

//move right by turning right motor back and left motor forward
void turn_right(float percentLeft, float percentRight, int counts) //using encoders
{
    // Makes for a right turn in place.
    //ensure percentRight is negative 
    //if percentRight is positive/0 make negative
    using namespace std;
    percentLeft = -1 * abs((float)percentLeft);
    percentRight = abs(percentRight);
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    //check if right encoders counts will be negtive if moving motor backward
    while((abs(right_encoder.Counts()) + abs(left_encoder.Counts())) / 2. < counts){}
    LCD.WriteLine("Move Right Complete");
    //LCD.WriteLine(right_encoder.Counts());
    //LCD.WriteLine(left_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    Sleep(0.25);
}

//print encoder counts
void testCounts(){

        right_encoder.ResetCounts();
        left_encoder.ResetCounts();

        //string s of all encoder info
        while(true){
            LCD.WriteLine("Counts::");
            LCD.WriteLine(right_encoder.Counts());
            LCD.WriteLine(left_encoder.Counts());
            Sleep(0.5);
        }

        Sleep(0.25);
}

//move left by turning left motor back and right motor forward
void turn_left(float percentLeft, float percentRight, int counts) //using encoders
{
    // Makes for a left turn in place.
    //ensure percentRight is negative 
    // Ensure percentLeft is positive (meaning going backward), and percentRight is negative
    percentLeft = abs(percentLeft);
    percentRight = -1 * abs(percentRight);
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    //check if right encoders counts will be negtive if moving motor backward
    while((abs(right_encoder.Counts()) + abs(left_encoder.Counts())) / 2. < counts){}
    LCD.WriteLine("Move Left Completed: right, left: ");
    //LCD.WriteLine(right_encoder.Counts());
    //LCD.WriteLine(left_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    Sleep(0.25);
}

//move forward by turning both motors, can used varied percents
void move_forward(float percentLeft, float percentRight, int counts) //using encoders
{
    percentLeft *= -1;
    percentRight *= -1;
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts){}
    //string s of all encoder info
    LCD.WriteLine("Move Forward Complete: right, left: ");
    LCD.WriteLine(right_encoder.Counts());
    LCD.WriteLine(left_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    Sleep(0.25);
}

//move forward by turning both motors, can used varied percents
void move_until(float percentLeft, float percentRight) //using encoders
{
    percentLeft = -1* abs(percentLeft);
    percentRight = -1 * abs(percentRight);
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while(distSens.Value()){}
    //string s of all encoder info
    LCD.WriteLine("Move Forward Complete: right, left: ");
    LCD.WriteLine(right_encoder.Counts());
    LCD.WriteLine(left_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    Sleep(0.25);
}

int main(void) {
    float percentLeft = 30.0;
    float percentRight = 30.0;
    int Turn90Counts = 245;
    float backIn = 2; 
    LCD.Clear();

    left_motor.SetPercent(15.0);
    right_motor.SetPercent(15.0);


    move_until(percentLeft, percentRight);
    move_forward(-1*percentLeft, -1*percentRight, (backIn*INCH));
    turn_right(percentLeft, percentRight, Turn90Counts);
    move_until(percentLeft, percentRight);
    move_forward(-1*percentLeft, -1*percentRight, (backIn*INCH));
    turn_left(percentLeft, percentRight, Turn90Counts);
    move_until(percentLeft, percentRight);
    LCD.Write("Done");

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    

    right_motor.Stop();
    left_motor.Stop();


}


//248-221
//230-213
//233-214