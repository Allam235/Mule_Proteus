// Team D1

#include <FEHBattery.h>
#include <FEHUtility.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <FEHMotor.h>
#include <string>
#include <cstdlib>
#include <FEHServo.h>

#define INCH 40.5
#define MULTI -1

using namespace std;

// Declarations for analog optosensors
// AnalogInputPin right_opto(FEHIO::P2_0);
// AnalogInputPin middle_opto(FEHIO::P2_1);
// AnalogInputPin left_opto(FEHIO::P2_2);

// DigitalInputPin FrontRightSwitch(FEHIO::P1_0);

AnalogInputPin cds(FEHIO::P0_3);

//Declarations for encoders & motors
DigitalEncoder left_encoder(FEHIO::P0_0);
DigitalEncoder right_encoder(FEHIO::P0_4);
FEHMotor left_motor(FEHMotor::Motor0,9.0);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHServo servo(FEHServo::Servo3);

//set min is 500;
//stable 920 is the value we are picking up the apple bucket with
//up is 1130 - stmax

//move forward by turning both motors, can used varied percents
void move_forward(float percentLeft, float percentRight, int counts) //using encoders
{
    percentLeft *= MULTI;
    percentRight *= MULTI;
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
    LCD.WriteLine(right_encoder.Counts());
    LCD.WriteLine(left_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
    Sleep(0.25);
}

//move forward by turning both motors, can used varied percents
void move_back(float percentLeft, float percentRight, int counts) //using encoders
{
    percentLeft = abs(percentLeft);
    percentRight = abs(percentRight);
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
    percent *= MULTI;
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
        percentLeft = MULTI * abs((float)percentLeft);
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
        percentRight = MULTI * abs(percentRight);
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

void servo_up(){
    servo.TouchCalibrate();
}

float cds_move(float percentLeft, float percentRight, int counts) // using encoders
{
    percentLeft *= MULTI;
    percentRight *= MULTI;
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

    float lignUp = 4; // move forward till parallel with humidifer huttons
    float backwall = 8;
    float toBucketStr = 10;
    float toBucketBent = 4;
    float turnout = 3.55*INCH;
    float turn45 = 135;
    float turnapple = 120;
    float turn90Count = 270;
    float toBucket = 9.5;
    float backright = 127;
    float backAppleStr = 475;
    float backWallAlign = 220;
    float strBackWallHit = 550;
    //float alignRamp = 158;
    
    servo.SetMin(700);
    //1125 is flat
    servo.SetMax(1305);
    servo.SetDegree(108);
    
    move_forward(defaultLeftPower, defaultRightPower, (4.5*INCH));
    // Make 45 degree turn 
    turn_left(defaultLeftPower+5, defaultRightPower, (turnout));
    //move forward up ramp, 
    move_forward(defaultLeftPower, defaultRightPower, (lignUp*INCH));
    //testCounts();
    turn_left(defaultLeftPower, defaultRightPower, turn90Count);
    move_back(defaultLeftPower+8, defaultRightPower-5, (backwall*INCH));

    //move towards apple bucket
    move_forward(defaultLeftPower, defaultRightPower, (toBucketStr*INCH));
    turn_right(defaultLeftPower, defaultRightPower, turnapple);
    move_forward(defaultLeftPower, defaultRightPower, (toBucketBent*INCH));
    turn_left(defaultLeftPower, defaultRightPower, turnapple+19);
    move_forward(defaultLeftPower, defaultRightPower, (toBucket*INCH));
    servo.SetDegree(180);
    Sleep(0.15);
    move_oneMotor(-1 * defaultRightPower, 'r', backright);
    move_back(defaultLeftPower, defaultRightPower, backAppleStr);
    turn_left(defaultLeftPower, defaultRightPower, backWallAlign);
    move_back(defaultLeftPower, defaultRightPower, strBackWallHit);


    
    

    
    testCounts();



}