#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>
#include <FEHMotor.h>

// Declarations for analog optosensors
AnalogInputPin right_opto(FEHIO::P2_0);
AnalogInputPin middle_opto(FEHIO::P2_1);
AnalogInputPin left_opto(FEHIO::P2_2);

DigitalInputPin FrontRight(FEHIO::P1_0);

//Declarations for encoders & motors
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor2,9.0);
FEHMotor left_motor(FEHMotor::Motor1,9.0);

void move(int percentLeft, int percentRight, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percentRight);
    left_motor.SetPercent(percentLeft);

    //While the average of the left and right encoder is less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts){}

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

float rightDiff = 1.9;
float middleDiff = 1.8;
float leftDiff = 1.9;

// 0 is straight, 1 is turn left, 2 is turn right
/*
int location(){
    //middle on line
    int r = 3;
    if(middle_opto.Value() > middleDiff){
        r = 0;
    }
    //right on line
    else if(right_opto.Value() > rightDiff){
        r = 1;
    }
    else if(left_opto.Value() > leftDiff){
        r = 2;
    }
    
    LCD.WriteLine(r);
    LCD.WriteLine(right_opto.Value());
    LCD.WriteLine(middle_opto.Value());
    LCD.WriteLine(left_opto.Value());
    return r;
}
    */

int main(void)
{
    float cps = 0.1;//count per step
    LCD.Clear();
    //move(25, 25, cps);
    //LCD.WriteLine(right_encoder.Counts());
    //LCD.WriteLine(left_encoder.Counts());
    
    //LCD.Clear();
    LCD.WriteLine("DONE");
    LCD.WriteLine(right_opto.Value());
    LCD.WriteLine(middle_opto.Value());
    LCD.WriteLine(left_opto.Value());
    int r;
    while(FrontRight.Value()){
        r = 3;
        if(middle_opto.Value() > middleDiff){
            r = 0;
        }
        //right on line
        else if(right_opto.Value() > rightDiff){
            r = 1;
        }
        else if(left_opto.Value() > leftDiff){
            r = 2;
        }
        
        LCD.WriteLine(r);
        LCD.WriteLine(right_opto.Value());
        LCD.WriteLine(middle_opto.Value());
        LCD.WriteLine(left_opto.Value());
        switch(r){
            case 0://straight
                right_motor.SetPercent(25);
                left_motor.SetPercent(25);
                Sleep(cps);
                //Turn off motors
                right_motor.Stop();
                left_motor.Stop();
            break;
            case 2://left
                right_motor.SetPercent(25);
                left_motor.Stop();
                Sleep(cps);
                //Turn off motors
                right_motor.Stop();
            break;
            case 1://right
                right_motor.Stop();
                left_motor.SetPercent(25);
                Sleep(cps);
                //Turn off motors
                left_motor.Stop();
            break;
            case 3:
                LCD.WriteLine(" Nothin ");
                Sleep(cps);
            break;
        }
    }
    
}

/*
FEH 105
Left Opto on line: 2.378
Left Opto off line: 1.144
Middle Opto on line: 1.929
Middle Opto off line: 1.452
right Opto on line: 2.423
Right Opto off line: 1.201
CURVE THAT THANG
Left Opto on line: 2.398
Left Opto off line: 1.157
Middle Opto on line: 2.001
Middle Opto off line: 1.491
right Opto on line: 2.557
Right Opto off line: 1.304
 */