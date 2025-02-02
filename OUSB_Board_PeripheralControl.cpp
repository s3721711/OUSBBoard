/*EEET2246 - OUSB Process Control ============

PURPOSE:
This file is a program that takes up to 2 command line arguments
and makes several decisions based on certain register values on the OUSB Board.

You will be required to read the 'PINC' and 'ADC 5' registers which are connected to
the DIP switches and potentiometer, respectively. Your program will then perform a
comparison (decision) on the input data from the command line arguments and OUSB Board
PINC / ADC registers and write the largest value to PORTB, as well as display the binary
representation of the value to the console window.

The binary representation of the largest value from the comparison must be written to
the console using 8 characters (zero padded as necessary) to either display the binary
representation in reverse or conventional order. The value
written to PORTB should always be in the conventional bit-order.

The program decisions will be based on:
- The first input argument, which must be a valid number between 0 and 255 input as a
floating point number. This number will need to be rounded to the nearest integer.

- The (optional) second input argument, determines the comparison operation to undertake
and the format of the output on the console window. The only valid arguments for the
second command line argument are:
"c1"  compare command line argument 1 to OUSB Board switches and display the binary
value to the console window in reverse order (default).
"c2"  compare command line argument 1 to OUSB Board potentiometer and display the
binary value to the console window in reverse order.
"c3"  compare command line argument 1 to OUSB Board potentiometer and switches and
display binary value to the console window in reverse order.
"c4"  compare command line argument 1 to the OUSB Board potentiometer and switches,
however display the console number in the correct order of bit7 through to bit0.

If only one command line argument is provided, then a comparison between the first
command line input argument and the OUSB Board switches should be performed (i.e.
option "c1" by default).

- The value at PORTC (pinc) which is connected to the 8 (DIP) switches.

- The value at ADC pin 5, which is connected to potentiometer.

The program output will be via the OUSB Board LEDs connected to PORTB and the console window.
The output to the console window under normal conditions will display the binary
representation of the value at PORTB in the specified order followed by a new line character.
If an error occurs the only output will be a one character error code followed by a new line
character. The OUSB Board LEDs must not be updated if an error occurs.
*/
/*
___________________________________________________________________________________________
___ GENERAL SPECIFICATIONS (common to all three EEET2246 Laboratory Tests):
G3.	All outputs are a binary representation of an integer or a single character error
indicator followed by a linefeed ( endl or \n).

G5.	DO NOT use 'cin' or gets() type functions. Do NOT ask for user input. All input MUST
be specified on the command line separated by blank spaces (i.e. use the argv and argc
input parameters).

G6.	All input and output is case sensitive.

G12. If an error (as per the definition in this specification) occurs then the value on
the OUSB LEDs must not to be updated.

G13. All numerical values read from / written to the OUSB Board are considered to be unsigned
and are between 0 and 255 (inclusive).

G14. All binary numbers within this document have the prefix 0b. This notation is not C++
compliant, however is used to avoid confusion between decimal, hexadecimal and binary
number formats within the description and specification provided in this document. For
example the number 10 in decimal could be written as 0xA in hexadecimal or 0b1010 in binary.
It can equally be written with leading zeroes such as: 0x0A or 0b00001010. For output
to the console screen you should only ever display the numerical characters only and omit
the 0x or 0b prefixes.

G15. Do not attempt to read/write to any other OUSB Board IO port other than PORTB, PINC
or ADC pin 5 (adc 5).

G16. The conversion to binary must occur in your code, not by using the -b switch as part
of the OUSB.exe application. The '-b' flag will not be supported by the AutoTester.
*/
/*
___________________________________________________________________________________________
___ FUNCTIONAL REQUIREMENTS:

- Read OUSB Board switches.
- Read OUSB potentiometer (right shift by 2, which is equivalent to a division by 4)
- Console input arguments (first is a number, second is the comparison operation)
- "c1"  compare argument to OUSB Board switches (default)
- "c2"  compare argument to OUSB Board potentiometer
- "c3"  compare OUSB Board switches, potentiometer and console input arguments.
- "c4"  compare OUSB Board switches, potentiometer and console arguments
(however displays the console number in bit correct order)
- which one is numerically greater is displayed on the OUSB LEDs and console
(console should be in binary)
- Whichever one is greater, is displayed is displayed on the LEDs in binary.
- Base conversion of largest value in binary on console (in specified order).


F1.		For situations where NO command line arguments are passed to your program:
	--> program displays: "1Olivia_Robertson"

F2.	For the situation where ONE command line argument is passed to your program:
	--> Your program must compare the rounded value (to the nearest integer) of the
input argument with the value of the DIP switches connected to PINC of the OUSB Board.
Whichever value is larger should then be represented on the OUSB LEDs on PORTB. The
value should also be displayed to console window using the reverse binary representation
in an 8 character long string (ie. Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7 with
no commas or spaces) followed by a new line character.

F3.		For the situation where TWO command line arguments are passed to your program:
Whichever value is larger should then be
represented on the OUSB LEDs on PORTB. The value should also be displayed to console
window using the reverse binary representation in an 8 character long string
(ie. Bit0, Bit1, Bit2, Bit3, Bit4, Bit5, Bit6, Bit7 with no commas or spaces) followed
by a new line character.

F3.1		If the second argument is "c1", your program must compare the rounded value
(to the nearest integer) of the input argument with the value of the DIP switches
connected to PINC of the OUSB Board. 

F3.2		If the second argument is "c2", your program must compare the rounded value
of the input argument with the value of the POTENTIOMETER 
connected to PORTD of the OUSB Board using the 'ADC 5' command. As the ADC value is a
10-bit number (ie 0 to 1023), you are required to convert it to an 8-bit number by
dividing it by 4 to scale it within the range of 0 to 255. 

F3.3		If the second argument is "c3", your program must compare the rounded value
(to the nearest integer) of the input argument with the value of the potentiometer
connected to PORTD of the OUSB Board using the 'ADC 5' command and the DIP switches
connected to PINC of the OUSB Board. As the ADC value is a 10-bit number (ie 0 to 1023),
you are required to convert it to an 8-bit number by dividing it by 4 to scale it within
the range of 0 to 255. 


F3.4		If the second argument is "c4", your program must compare the rounded value
(to the nearest integer)  of the input argument with the value of the potentiometer
connected to PORTD of the OUSB Board using the 'ADC 5' command and the DIP switches
connected to PINC of the OUSB Board. As the ADC value is a 10-bit number (ie 0 to 1023),
you are required to convert it to an 8-bit number by dividing it by 4 to scale it within
the range of 0 to 255. 

F4.		For situations where more than TWO command line arguments are passed to
your program, your program must display the character 'P' to the console with
a new line character.

F5.		For specifications F1 to F4 inclusive:
F5.3		Program must write only the equivalent unsigned 8-bit absolute integer
representation of the result produced by the arithmetic operation to the OUSB LEDs.

F5.4		If the result to be written to the OUSB Board LEDs is above 255 (0xFF), the value
255 (or 0xFF) should be written to the board instead.
*/
/*
___________________________________________________________________________________________
___ ERROR HANDLING:

The following text lists errors you must detect and a priority of testing.
Note: order of testing is important as each test is slightly more difficult than
the previous test.

E1. Error precedence:
The order of errors can theoretically be checked in any order, however if multiple errors
occur during a program execution event, your program should only display one error code
followed by a newline character and then exit (with a return 0). The displayed error
codes to the console window should occur in this order:
'P' - Incorrect number of input command line arguments
'X' - Invalid numerical command line argument
'R' - command line argument out of range
'V' - Invalid operation selection
'H' - Out of range OUSB number returned by 'pinc' or 'adc 5' command
'Y' - MURPHY'S LAW (undefined error)
Therefore if an invalid numerical command line argument and an invalid operation argument
are passed to the program, the first error code should be displayed to the console, which
in this case would be 'X'. Displaying 'V' or 'Y' would be result in a loss of marks.

E2.	Valid operator input:
If the second command line input argument is not a valid operation selection, the output
shall be 'V'. Valid operators are ONLY (case sensitive):
- "c1"  compare argument to OUSB Board switches (default)
- "c2"  compare argument to OUSB Board potentiometer
- "c3"  compare OUSB Board switches, potentiometer and console input arguments.
- "c4"  compare OUSB Board switches, potentiometer and console arguments.
(however display the console number in correct order)

E3.	Basic invalid number detection:
Valid numbers are all numbers that the "average Engineering graduate" in Australia
would consider valid. Therefore if the first command line argument is not a valid number,
the output shall be 'X'. For example:
013			is valid
+3			is valid
.3			is valid
ABC123		is not valid
1.3.4		is not valid
123abc		is not valid

E4. OUSB IO Board communication error:
If the pipe code communicating to the OUSB.exe file reports an issue with communication
to the OUSB IO Board, the output shall be 'Y'. This type of error can be forced by
disconnecting the USB cable between the PC and the OUSB IO Board.

Note: The OUSB.exe will give a message "Fatal Exception" if the board is not connected
or is disconnected during normal operation. This message should NOT be returned by your
code. The only output your code should give is the single character, 'Y' which is the same
as the return character as the MURPHY'S LAW TEST below.


E7. Input number range checking:

E7.1 If the value of the first command line argument is greater than 255 or less than 0
the output shall be 'R'. Zero is a valid input.
For example:
0			is valid
85.0		is valid
1.05e2		is valid
-45			is not valid
450			is not valid

E7.2 All 8-bits of the OUSB Board DIP switches are valid. Therefore 0 to 255 will be valid inputs.
If the hardware returns a value higher than 255 or less than 0 for some mysterious reason then the
output shall be 'H'.  This applies to PINC (switches) and PORTD after scaling (adc 5).
*/
/*
___________________________________________________________________________________________
NOTES:
- OUSB commands:
To read the value at port B:					ousb -r io portb
To write 20 to port B:  						ousb -r io portb 20
To read the value of the DIP switches (pinc):	ousb -r io pinc
To read the potentiometer (ADC5):				ousb -r adc 5

- Description of _itoa_s() library function - Converts an integer to a string.
Prototype:
errno_t _itoa_s(int value, char *buffer, int radix);
Parameters:
[in]  value  - Number to be converted.
[out] buffer - Is filled with the result of the conversion as a C string.
[in]  radix  - Base of value; which must be in the range 2–36.
Return Value - Zero if successful; an error code on failure.

- Description of strcpy_s() library function - Copies a C string.
Prototype:
errno_t strcpy_s(char *strDestination, const char *strSource);
Parameters:
strDestination - Location of the destination string buffer.
strSource      - Null-terminated source string buffer.
Return Value   - Zero if successful; an error code on failure.

- Description of strcat_s() library function - Appends a C string.
Prototype:
errno_t strcat_s(char *strDestination, const char *strSource);
Parameters:
strDestination - Null-terminated destination string buffer.
strSource      - Null-terminated source string buffer.
Return Value   - Zero if successful; an error code on failure.

- The following code is the syntax required to open a pipe to the device.
It may / may not include all of the necessary code to complete the task.

//----Start of template standalone .cpp file--------------------------------------------
#include "stdafx.h"
#include <iostream>
#define Debug 1
using namespace std;
int main(int argc, char* argv[])
{
char command[256] = {};
strcpy_s(command, "ousb -r io PORTB 20"); // command to write 20 to OUSB board

FILE *fpipe;
char line[250] = {}; // size of Line should be smaller than command

fpipe = (FILE*)_popen(command,"r");    // attempt to open pipe and execute a command
if( fpipe != NULL )					   // check that the pipe opened correctly
{
while( fgets(line, sizeof(line), fpipe) )
{   // do nothing here, or print out debug data
if (Debug) cout << line; // print out OUSB data for debug purposes
}
_pclose(fpipe);   // close pipe
}
else cout << "Error, problems with pipe!\n";

// do something with the value returned by the OUSB board, eg:
unsigned short portb = (unsigned short)atoi(line); // convert from char array to unsigned short
cout << "value = " << portb << endl;

return 0;
}
//----End of template standalone .cpp file----------------------------------------------
____________________________________________________________________________________________
*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <errno.h>   
#include <string>
#include <sstream>

using namespace std;

const double MAXRANGE = 255;
const double MINRANGE = 0;

string convertBinary(int portb){
	char r[9];

	for (int i = 7; i >= 0; i--)
	{
		if (portb > 0)
		{
			if (portb % 2 == 0)
			{
				r[i] = '0';
			}
			else
			{
				r[i] = '1';
			}
			portb = portb / 2;
		}
		else
		{
			r[i] = '0';
		}
	}
	r[8] = '\0';
	string console = r;
	return console;
}

string reverseBinary(int portb){
	char r[9];

	for (int i = 0; i < 8; i++)
	{
		if (portb > 0)
		{
			if (portb % 2 == 0)
			{
				r[i] = '0';
			}
			else
			{
				r[i] = '1';
			}
			portb = portb / 2;
		}
		else
		{
			r[i] = '0';
		}
	}
	r[8] = '\0';
	string console = r;
	return console;
}

unsigned int readPinC(){
	unsigned int pinc = 0;
	char command[256] = {};
	strcpy_s(command, "ousbsim2 -r io PINC"); // command to write 20 to OUSB board

	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << "Debug: " << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	// do something with the value returned by the OUSB board, eg:
	pinc = (unsigned int)atoi(line);
	// DEBUG - cout << "value = " << pinc << endl;
	return pinc;
}

unsigned int writePortB(int value){
	char command[256] = { "ousbsim2 -r io PORTB " };
	char val_str[4] = {};

	_itoa_s(value, val_str, 10);

	strcat_s(command, val_str);

	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << "Debug: " << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	// do something with the value returned by the OUSB board, eg:
	unsigned short portb = (unsigned short)atoi(line); // convert from char array to unsigned short
	// DEBUG - cout << "value = " << portb << endl;

	return 0;
}

unsigned int readADC(){
	unsigned int adc = 0;
	char command[256] = {};
	strcpy_s(command, "ousbsim2 -r adc 5"); // command to write 20 to OUSB board

	FILE *fpipe;
	char line[250] = {}; // size of Line should be smaller than command

	fpipe = (FILE*)_popen(command, "r");    // attempt to open pipe and execute a command
	if (fpipe != NULL)					   // check that the pipe opened correctly
	{
		while (fgets(line, sizeof(line), fpipe))
		{   // do nothing here, or print out debug data
			//cout << "Debug: " << line; // print out OUSB data for debug purposes
		}
		_pclose(fpipe);   // close pipe
	}
	else cout << "Error, problems with pipe!\n";

	// do something with the value returned by the OUSB board, eg:
	adc = (unsigned int)atoi(line);
	cout << "value before right shift = " << adc << endl;
	adc = adc >> 2;
	cout << "value after right shift = " << adc << endl;
	return adc;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		// When run with just the program name (no parameters) 
		cout << "Olivia_Robertson" << endl;
		return 0;
	}

	if (argc >= 4){
		cout << "P" << endl;
	}
	else{
		char str[255] = {};
		double arg1 = 0;

		// need error checking
		const char valids[] = {".,+-eE0123456789"};
		bool valid = false;
		for (int i = 0; i < strlen(argv[1]); i++)
		{
			for (int j = 0; j < valids[j]; j++)
			{
				if (argv[1][i] == valids[j])
				{
					if (argv[1][i] == ',')
					{
						int w = i;
						int k = 0;
						for (int l = 0; l < argv[1][l]; l++)
						{
							if (l != w)
							{
								str[k] = argv[1][l];
								k++;
								arg1 = atof(str);
							}
						}
					}
					valid = true;
					break;
				}
				else
				{
					valid = false;
				}
			}
			if (valid == false)
			{
				cout << 'X' << endl;
			}
		}

		//values read/written to OUSB are considered to be unsigned, btween 0 - 255 (inclusive).
		if (valid == false){

			// unsigned int?
			// need to check between - 255 and round to nearest integer
			// it is input as floating point number
			if(arg1 == 0) arg1 = atof(argv[1]);
			int num2 = (int)round(arg1);
			int result = 0;
			int pinc = readPinC();
			int adc = readADC();


			// argc check
			if (argc == 2)
			{
				if (num2 > pinc)
				{
					result = num2;
				}
				else
				{
					result = pinc;
				}

				writePortB(result);
				cout << reverseBinary(result) << endl;
			}
			else
			{
				if (argv[2][0] != 'c')
				{
					//error
				}
				else if (argv[2][2] != '\0')
				{
					//error
				}
				else if (argv[2][1] == '1')
				{

					if (num2 > pinc)
					{
						result = num2;
					}
					else
					{
						result = pinc;
					}

					writePortB(result);
					cout << reverseBinary(result) << endl;
				}
				else if (argv[2][1] == '2')
				{
					if (num2 > adc)
					{
						result = num2;
					}
					else
					{
						result = adc;
					}
					writePortB(result);
					cout << reverseBinary(result) << endl;
				}
				else if (argv[2][1] == '3')
				{
					if (num2 > pinc)
					{
						if (adc > num2)
						{
							result = adc;
						}
						else
						{
							result = num2;
						}
					}
					else
					{
						if (adc > pinc)
						{
							result = adc;
						}
						else
						{
							result = pinc;
						}
					}
					writePortB(result);
					cout << reverseBinary(result) << endl;

				}
				else if (argv[2][1] == '4')
				{
					if (num2 > pinc)
					{
						if (adc > num2)
						{
							result = adc;
						}
						else
						{
							result = num2;
						}
					}
					else
					{
						if (adc > pinc)
						{
							result = adc;
						}
						else
						{
							result = pinc;
						}
					}
					writePortB(result);
					cout << convertBinary(result) << endl;
				}
				else
				{
					// error - V
				}
			}
		}
	}

 
	return 0;
}  
   // End of file. 

