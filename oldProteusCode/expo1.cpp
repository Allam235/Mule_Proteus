#include <FEHUtility.h>
#include <FEHServo.h>
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHMotor.h>

int expo(void) 
{ 

    //500 min
    //2306 max
    LCD.Clear();
    FEHServo servo(FEHServo::Servo7); // declare servo arm
    AnalogInputPin Cds(FEHIO::P0_0);

    DigitalInputPin FrontRight(FEHIO::P2_0);
    DigitalInputPin FrontLeft(FEHIO::P2_1);
    DigitalInputPin BackRight(FEHIO::P2_3);
    DigitalInputPin BackLeft(FEHIO::P2_2);
    FEHMotor Right(FEHMotor::Motor2, 9.0);
    FEHMotor Left(FEHMotor::Motor1, 9.0);

    Right.SetPercent(25);
    Left.SetPercent(25);
    while(FrontLeft.Value() & FrontRight.Value()){}
    Right.Stop();
    Left.Stop();
    LCD.Write("Forward done");
    Sleep(3);
    LCD.Write("BackRight");
    Right.SetPercent(-25);
    while(BackRight.Value()){}
    LCD.Write("BackRightSwitch");
    Right.SetPercent(0);
    Sleep(1);
    LCD.Write("BackLeft");
    Left.SetPercent(-20);
    while(BackLeft.Value()){}
    LCD.Write("BackLeftSwitch");
    Left.SetPercent(0);
    Sleep(7);
    Right.SetPercent(25);
    Left.SetPercent(25);
    while(FrontLeft.Value() & FrontRight.Value()){}
    Right.Stop();
    Left.Stop();
    Sleep(1);



    Left.SetPercent(-25);
    //Right.SetPercent(10);
    while(BackLeft.Value()){}
    LCD.Write("BackLeftSwitch");
    Left.SetPercent(0);
    Right.SetPercent(0);
    Sleep(1);
    Right.SetPercent(-25);
    while(BackRight.Value()){}
    Sleep(7);
    Right.SetPercent(25);
    Left.SetPercent(25);
    while(FrontLeft.Value() & FrontRight.Value()){}
    Right.Stop();
    Left.Stop();
    Sleep(1);
    


    
    

    /*
    while(true){
    if(!FrontRight.Value()){
        LCD.WriteLine("FrontRight");
    }
    if(!FrontLeft.Value()){
        LCD.WriteLine("FrontLeft");
    }
    if(!BackRight.Value()){
        LCD.WriteLine("BackRight");
    }
    if(!BackLeft.Value()){
        LCD.WriteLine("BackLeft");
    }
    Sleep(0.3);
    }
    */
    //servo code
    /*
    servo.SetMax(2306);
    servo.SetMin(500);
    while(true){
        float val = Cds.Value();
        LCD.WriteLine(val);
        servo.SetDegree((val/3.3)*180);
        Sleep(0.5);
    }
        */

    
	return 0;
}
