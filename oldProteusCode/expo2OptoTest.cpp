#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHSD.h>

// Declarations for analog optosensors
AnalogInputPin left_opto(FEHIO::P2_0);
AnalogInputPin middle_opto(FEHIO::P2_1);
AnalogInputPin right_opto(FEHIO::P2_2);

int main(void)
{
    float x, y; //for touch screen

    // Open output file and prepare for writing values to it
    // <ADD CODE HERE>

    //Initialize the screen
    LCD.Clear(BLACK);
    LCD.SetFontColor(WHITE);
    FEHFile *fptr = SD.FOpen("Test.txt","w");
    //Close the file
    

    LCD.WriteLine("Analog Optosensor Testing");
    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    // Record values for optosensors on and off of the straight line
    // Left Optosensor on curved line
    Sleep(0.5);
    LCD.Clear(BLACK);
    LCD.WriteLine("Place left optosensor on straight line");
     // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (1/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    float num = left_opto.Value();
    SD.FPrintf(fptr,  "Left Opto on line: %f\n", num);

    // <ADD CODE HERE>

    
    // Left Optosensor off straight line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place left optosensor off straight line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (2/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = left_opto.Value();
    SD.FPrintf(fptr,  "Left Opto off line: %f\n", num);
    // <ADD CODE HERE>

    

    //////////Middle Sensor


    // Record values for optosensors on and off of the straight line
    // Right Optosensor on straight line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place middle optosensor on straight line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (3/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = middle_opto.Value();
    SD.FPrintf(fptr,  "Middle Opto on line: %f\n", num);
    // <ADD CODE HERE>
    
    // Left Optosensor off straight line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place middle optosensor off straight line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (4/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = middle_opto.Value();
    SD.FPrintf(fptr,  "Middle Opto off line: %f\n", num);
    
    //////////////////Right Sensor

    // Record values for optosensors on and off of the straight line
    // Left Optosensor on straight line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place right optosensor on straight line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value 5/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = right_opto.Value();
    SD.FPrintf(fptr,  "right Opto on line: %f\n", num);
    LCD.WriteLine("right O");
    // <ADD CODE HERE>
    
    // Left Optosensor off straight line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place right optosensor off straight line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (6/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = right_opto.Value();
    SD.FPrintf(fptr,  "Right Opto off line: %f\n", num);
    
    // Repeat process for remaining optosensors, and repeat all three for the curved line values
    // <ADD CODE HERE>

    // Close output file
    // <ADD CODE HERE> 



    //curved line







    LCD.WriteLine("Analog Optosensor Testing");
    LCD.WriteLine("CURVE THAT THANG");
    SD.FPrintf(fptr,  "CURVE THAT THANG\n");
    LCD.WriteLine("Touch the screen");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed

    // Record values for optosensors on and off of the curved line
    // Left Optosensor on curved line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place left optosensor on curved line");
     // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (1/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = left_opto.Value();
    SD.FPrintf(fptr,  "Left Opto on line: %f\n", num);
    // <ADD CODE HERE>

    
    // Left Optosensor off curved line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place left optosensor off curved line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (2/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = left_opto.Value();
    SD.FPrintf(fptr,  "Left Opto off line: %f\n", num);
    // <ADD CODE HERE>

    

    //////////Middle Sensor


    // Record values for optosensors on and off of the curved line
    // Right Optosensor on curved line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place middle optosensor on curved line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (3/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = middle_opto.Value();
    SD.FPrintf(fptr,  "Middle Opto on line: %f\n", num);
    // <ADD CODE HERE>
    
    // Left Optosensor off curved line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place middle optosensor off curved line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (4/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = middle_opto.Value();
    SD.FPrintf(fptr,  "Middle Opto off line: %f\n", num);
    
    //////////////////Right Sensor

    // Record values for optosensors on and off of the curved line
    // Left Optosensor on curved line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place right optosensor on curved line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value 5/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = right_opto.Value();
    SD.FPrintf(fptr,  "right Opto on line: %f\n", num);
    LCD.WriteLine("right O");
    // <ADD CODE HERE>
    
    // Left Optosensor off curved line
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Place right optosensor off curved line");
    Sleep(0.5); // Wait to avoid double input
    LCD.WriteLine("Touch screen to record value (6/12)");
    while(!LCD.Touch(&x,&y)); //Wait for screen to be pressed
    while(LCD.Touch(&x,&y)); //Wait for screen to be unpressed
    // Write the value returned by the optosensor to your output file
    num = right_opto.Value();
    SD.FPrintf(fptr,  "Right Opto off line: %f\n", num);
    
    // Repeat process for remaining optosensors, and repeat all three for the curved line values
    // <ADD CODE HERE>

    // Close output file
    // <ADD CODE HERE> 

    // Print end message to screen
    LCD.Clear(BLACK);
    LCD.WriteLine(num);
    LCD.WriteLine("Test Finished");
    SD.FClose(fptr);
    return 0;
}

/*
Left Opto on line: 2.026
Left Opto off line: .921
Middle Opto on line: 2.196
Middle Opto off line: 1.091
right Opto on line: 1.351
Right Opto off line: 1.247
*/

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
