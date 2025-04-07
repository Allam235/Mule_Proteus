// Team D1

#include <FEHBattery.h>
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <FEHMotor.h>
#include <string>
#include <cstdlib>

#define INCH 40.5

using namespace std;

// Declarations for analog optosensors
// AnalogInputPin right_opto(FEHIO::P2_0);
// AnalogInputPin middle_opto(FEHIO::P2_1);
// AnalogInputPin left_opto(FEHIO::P2_2);

// DigitalInputPin FrontRightSwitch(FEHIO::P1_0);

AnalogInputPin cds(FEHIO::P0_3);

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
    LCD.WriteLine("Move Forward");
    //LCD.WriteLine(right_encoder.Counts());
    //LCD.WriteLine(left_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    Sleep(0.25);
}

//move one motor by using char s, l for left motor, r for right motor 
// Note for clarity: "r" turns left, "l" turns right 
void move_oneMotor(float percent, char s, int counts) //using encoders
{
    percent *= -1;
    // Makes for a wide turn.
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    if(s == 'l'){
        //Set both motors to desired percent
        right_motor.Stop();
        left_motor.SetPercent(percent);
    }
    else if(s == 'r'){
        //Set both motors to desired percent
        right_motor.SetPercent(percent);
        left_motor.Stop();
    }

        //While the average of the left and right encoder is less than counts,
        //keep running motors
        //the none moving encoder count should be 0 so no need to divide combined count by 2
        while((abs(left_encoder.Counts()) + abs(right_encoder.Counts())) < counts){}
        LCD.WriteLine("Move One Motor Complete");
        //LCD.WriteLine(right_encoder.Counts());
        //LCD.WriteLine(left_encoder.Counts());
        //Turn off motors
        right_motor.Stop();
        left_motor.Stop();
        Sleep(0.25);
    }

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

float cds_averager(float &ext_output_var){
    float cds_avg = 0;
    for (std::size_t i = 0; i < 100; ++i){
        cds_avg += cds.Value();
        Sleep(0.005);
    }
    cds_avg /= 100; // gets the average of the light at this location over a second
    if (cds_avg <= 0.1) {
        LCD.Write("ERROR: CdS SHORT CIRCUIT. ADJUST WIRES (I blame Rithvik)");
    }
    ext_output_var = cds_avg; // just because ben is stupid and silly
    return cds_avg;
}

float cds_move(float percentLeft, float percentRight, int counts) // using encoders
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
    float reading = 3.6, cds_min_found = 3.6, external_output_var = 0;

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts){
        reading = cds.Value();
        if (reading < cds_min_found){
            cds_min_found = reading;
        }
        Sleep(0.005);
    }
    // string s of all encoder info
    // LCD.WriteLine("Move Forward Complete: right, left: ");
    // LCD.WriteLine(right_encoder.Counts());
    // LCD.WriteLine(left_encoder.Counts());
    // Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    Sleep(0.25);
    return cds_min_found;
}



int main(void) {
    LCD.Clear();
    LCD.WriteLine("Battery Power: ");
    LCD.WriteLine(Battery.Voltage());
    LCD.WriteLine("Wating for Start Light...");
    float external_output_var = 0;
    while (cds_averager(external_output_var) >= 1.5) // Wait for starting light
        Sleep(0.05);
    LCD.WriteLine("Reading that started movement: ");
    LCD.WriteLine(external_output_var);

    //Set both motors to desired percent
    //default powers for each motor, change in case of unbalenced motors

    float actual_power = /**/ 37 /**/ * 11.5 / Battery.Voltage(); // CURRENT SETTING: 50% desired
    float defaultRightPower = actual_power, defaultLeftPower = actual_power;

    //*** 40.5 counts per inch ***
    //the following values are inch travelled, the conversion to encoder counts i done already

    float upRamp = 32.82; // move forward till parallel with humidifer huttons
    float turnLeft45 = 2.63;
    float turn90Count = 270;
    float toWindowTilt = 9;
    float toWindow = 3;
    float toWindowRightTilt = 8;
    float backCloseWindowStr = 3;
    float backCloseWindow = 10;


    move_forward(defaultLeftPower, defaultRightPower, (4.5*INCH));
    // Make 45 degree turn 
    turn_left(defaultLeftPower, defaultRightPower, (turnLeft45*INCH));
    //move forward up ramp, 
    move_forward(defaultLeftPower+10, defaultRightPower+10, (upRamp*INCH));
    //testCounts();

    // sharp left turn
    turn_left(25, 25, turn90Count);

    // move forward to push window
    move_forward(defaultLeftPower, defaultRightPower+5, (toWindowTilt*INCH));
    
    move_forward(defaultLeftPower+10, defaultRightPower+5, (toWindow*INCH));
    move_forward(defaultLeftPower+20, defaultRightPower, (toWindowRightTilt*INCH));
    Sleep(1.0);
    //move_backward(defaultLeftPower, defaultRightPower, (backCloseWindowStr*INCH));
    //move_backward(defaultLeftPower+20, defaultRightPower, (backCloseWindow*INCH));
    testCounts();



}