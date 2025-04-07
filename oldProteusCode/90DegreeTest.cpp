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

int main(void) {
    int percentLeft = 15;
    int percentRight = -15;
    int counts = 270;

    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    while((abs(right_encoder.Counts()) + abs(left_encoder.Counts())) / 2. < counts){
        

        //Set both motors to desired percent
        right_motor.SetPercent(percentRight);
        left_motor.SetPercent(percentLeft);

        //While the average of the left and right encoder is less than counts,
        //keep running motors
        //string s of all encoder info
        LCD.WriteLine("Move Forward Complete: right, left: ");
        LCD.WriteLine(right_encoder.Counts());
        LCD.WriteLine(left_encoder.Counts());
        //Turn off motors
        
        //Sleep(0.25);
        Sleep(0.1);
        
    }

    right_motor.Stop();
    left_motor.Stop();

    while(true){
        

        //While the average of the left and right encoder is less than counts,
        //keep running motors
        //string s of all encoder info
        LCD.WriteLine("Move Forward Complete: right, left: ");
        LCD.WriteLine(right_encoder.Counts());
        LCD.WriteLine(left_encoder.Counts());
        //Turn off motors
        
        //Sleep(0.25);
        Sleep(0.1);
        
    }

    right_motor.Stop();
    left_motor.Stop();


}


//248-221
//230-213
//233-214
