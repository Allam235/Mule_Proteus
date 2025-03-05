#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <FEHMotor.h>
#include <string>

// Declarations for analog optosensors
AnalogInputPin right_opto(FEHIO::P2_0);
AnalogInputPin middle_opto(FEHIO::P2_1);
AnalogInputPin left_opto(FEHIO::P2_2);

DigitalInputPin FrontRightSwitch(FEHIO::P1_0);
AnalogInputPin cds(FEHIO::P0_0);

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor1,9.0);
FEHMotor left_motor(FEHMotor::Motor0,9.0);

//move forward by turning both motors, can used varied percents
void move_forward(int percentLeft, int percentRight, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts)
    //string s of all encoder info
    std::string s = "MoveForward, RightCount:" + std::to_string(right_encoder.Counts()) + " LeftCount:" + std::to_string(left_encoder.Counts());
    //LCD.WriteLine("MoveForward, RightCount:" + std::to_string(right_encoder.Counts()) + " LeftCount:" + std::to_string(left_encoder.Counts()));
    LCD.WriteLine("Move forward: right, left");
    LCD.WriteLine(right_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

//move one motor by using char s, l for left motor, r for right motor 
void move_oneMotor(int percent, char s, int counts) //using encoders
{
     
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
    while((left_encoder.Counts() + (-1*right_encoder.Counts())) < counts){}
    LCD.WriteLine("Move forward: right, left");
    LCD.WriteLine(right_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

//move right by turning right motor back and left motor forward
void move_right(int percentLeft, int percentRight, int counts) //using encoders
{
    //ensure percentRight is negative 
    //if percentRight is positive/0 make negative
    if(percentRight >= 0){
        percentRight *= -1;
    }
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    //check if right encoders counts will be negtive if moving motor backward
    while((left_encoder.Counts() + (-1*right_encoder.Counts())) / 2. < counts){}
    LCD.WriteLine("Move forward: right, left");
    LCD.WriteLine(right_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

//move left by turning left motor back and right motor forward
void move_left(int percentLeft, int percentRight, int counts) //using encoders
{
    //ensure percentRight is negative 
    //if percentRight is positive/0 make negative
    if(percentLeft >= 0){
        percentLeft *= -1;
    }
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    //check if right encoders counts will be negtive if moving motor backward
    while((right_encoder.Counts() + (-1*left_encoder.Counts())) / 2. < counts){}
    LCD.WriteLine("Move forward: right, left");
    LCD.WriteLine(right_encoder.Counts());
    LCD.WriteLine(right_encoder.Counts());
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

int main(void)
{
    //Set both motors to desired percent

    //TODO check all methods/function to make sure the function as desired

    //default powers for each motor, change in case of unbalenced motors
    int defaultRightPower = 50;
    int defaultLeftPower = 50;

    //40.5 counts per inch

    //TODO: "Control Panel" use the following variables to control and distances travelled
    //the following values are inch travelled, the conversion to encoder counts i done already

    float upRamp = 44; // move forward till parallel with humidifer huttons
    float turnRight90 = 11; // turn 90 degrees to right (both wheels)
    float toHumidifierLight = 17;
    float toHumidiferButtonStraight = 1;
    float redBlueBarrier = 1.05;
    //tilt to press humidifer button inch
    float rightTilt = 0.75;
    float leftTilt = rightTilt;

    //move forward up ramp, 
    move_forward(defaultLeftPower, defaultRightPower, (upRamp*40.5));
    move_left(defaultLeftPower, defaultRightPower, (turnRight90*40.5));
    move_forward(defaultLeftPower, defaultRightPower, (toHumidifierLight*40.5));

    //from this point, check light color, move forward and tilt in desired position
    

    //////////TODO: check if this logic is right///////////////////////
    //if cds value is above, tilt right by moving right motor
    if(cds.Value() > redBlueBarrier){
        //move in to position to tilt
        move_forward(defaultLeftPower, defaultRightPower, (toHumidiferButtonStraight*40.5));
        move_oneMotor(defaultRightPower, 'r', (rightTilt*40.5));
        move_oneMotor(-1*defaultRightPower, 'r', (rightTilt*40.5));
    }
    else if(cds.Value() < redBlueBarrier){
        //move into position to tilt
        move_forward(defaultLeftPower, defaultRightPower, (toHumidiferButtonStraight*40.5));
        move_oneMotor(defaultLeftPower, 'l', (leftTilt*40.5));
        move_oneMotor(-1*defaultLeftPower, 'l', (leftTilt*40.5));
    }

}
