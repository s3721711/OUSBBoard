/*EEET2246 - OUSB Arithmetic Calculator ============

PURPOSE:
This file is a program that takes one number from the OUSB Board
DIP switches and a second number from the command line arguments as input numbers to your
program. The program will then perform a specific type of arithmetic operation, which will
be determined by the value of the second command line argument (if it is provided). The
resulting answer will then be displayed to the console screen in signed decimal
representation. Additionally your program will be required to also represent the absolute
value of the result as an 8-bit unsigned integer on the OUSB IO Board LEDs. Therefore if the
arithmetic operation on the two input numbers results in a decimal result, the signed decimal
value shall be displayed on the console screen and the absolute 8-bit integer representation
(ie. truncated version) will be represented on the OUSB board LEDs. You will need to account
for the limitations in the hardware and appropriately write the correct value to the OUSB
board.

The type of arithmetic operation that will be performed on the two input numbers will be
determined by the second command line argument (if provided), where if the second argument
is:
'a' an addition is to be performed,
's' a subtraction is to be performed,
'm' a multiplication is to be performed,
'd' a division is to be performed, and
'p' an exponential operation is to be performed.

If only one argument is provided, then the two input numbers should added together.
*/
/*
__________________________________________________________________________________________
___ GENERAL SPECIFICATIONS:
G3.	All outputs are a number or single character error indicator followed by a linefeed
( endl or \n).

G5.	DO NOT use 'cin' or gets() type functions. Do NOT ask for user input. All input MUST
be specified on the command line separated by blank spaces (i.e. use the argv and argc
input parameters).

G6.	All input and output is case sensitive.

G11. The OUSB Board switch state is always used as the first numerical argument.

G13. If an error (as per the definition in this specification) occurs then the value on
the OUSB LEDs must not to be updated.

G14. All numerical values read from / written to the OUSB Board are considered to be unsigned
and are between 0 and 255 (inclusive).

G15. All binary numbers within this document have the prefix 0b. This notation is not C++
compliant, however is present to avoid confusion between decimal, hexadecimal and binary
number formats with in the description and specification provided in this document. For
example number 10 in decimal could be written as 0xA in hexadecimal and 0b1010 in binary.
The could equally be written with leading zeroes such as: 0x0A or 0b00001010
*/
/*
___________________________________________________________________________________________
___ FUNCTIONAL REQUIREMENTS:

F1.	For situation where NO command line arguments are passed to your program:
	-->	 program  displays: "Olivia_Robertson"

F2.	For the situation where ONE command line argument is passed to your program:

F2.1	Your program must perform an addition operation, taking the first number
from the DIP switch state on the OUSB board and the command line argument as the second
operand for the arithmetic calculation. The signed result should be displayed to the console
with a new line character and the equivalent unsigned 8-bit absolute integer represenation
to the OUSB LEDs.

F3.	For the situation where TWO command line arguments are passed to your program:

F3.1	If the second argument is 'a', your program must perform an addition operation,
taking the first number from the DIP switch state on the OUSB board and the command line
argument as the second operand. The signed result should be displayed to the console with
a new line character and the equivalent unsigned 8-bit absolute integer represenation to
the OUSB LEDs.

F3.2	If the second argument is 's', your program must perform a subtraction operation,
taking the first number from the DIP switch state on the OUSB board and the command line
argument as the second operand. The signed result should be displayed to the console with
a new line character and the equivalent unsigned 8-bit absolute integer represenation to
the OUSB LEDs.

F3.3	If the second argument is 'm', your program must perform a multiplication operation,
taking the first number from the DIP switch state on the OUSB board and the command line
argument as the second operand. The signed result should be displayed to the console with
a new line character and the equivalent unsigned 8-bit absolute integer represenation to
the OUSB LEDs.

F3.4	If the third argument is 'd', your program must perform a division operation,
taking numerator from the DIP switch state on the OUSB board and the command line argument
as the denominator. The signed result should be displayed to the console with a new line
character and the equivalent unsigned 8-bit absolute integer represenation to the OUSB LEDs.

F3.5	If the third argument is 'p', your program must perform an exponential operation,
taking the base operator from the DIP switch state on the OUSB board and the command line
argument as the exponent. The signed result should be displayed to the console with a new
line character and the equivalent unsigned 8-bit absolute integer represenation to the
OUSB LEDs.

F4.	For situation where more than TWO command line arguments are passed to
your program, your program must display the character 'P' to the console with
a new line character.

F5.	For specifications F1 to F4 inclusive:

F5.1	Program must return 0 under all situations at exit.

F5.2	Program must be able to handle both integer and float arguments from the
command line arguments.

F5.3	Program must write only the equivalent unsigned 8-bit absolute integer
represenation of the result produced by the arithmetic operation to the OUSB LEDs.

F5.4	If the result to be written to the OUSB Board LEDs is above 255 (0xFF), the value
255 (or 0xFF) should be written to the board instead.

*/
/*
___________________________________________________________________________________________
___ ERROR HANDLING:

The following text lists errors you must detect and a priority of testing.
Note: order of testing is important as each test is slight more difficult than
the previous test.

E1. Error precedence:
The order of errors can theoretically be check in any order, however if multiple errors
occur during a program execution event, your program should only display one error code
followed by a newline character and then exit (with a return 0). The displayed error
codes to the console window should occur in this order:
'P' - Incorrect number of input command line arguments
'X' - Invalid numerical command line argument
'R' - command line argument out of range
'V' - Invalid operation selection
'M' - Division by zero
'Y' - MURPHY'S LAW (undefined error)
Therefore if an invalid numerical command line argument and an invalid operation argument
are passed to the program, the first error code should be displayed to the console, which
in this case would be 'X'. Displaying 'V' or 'Y' would be result in a loss of marks.

E2.	Valid operator input:
If the second command line input argument is not a valid operation selection, the output
shall be 'V'. Valid operators are ONLY (case sensitive):
a	-	addition
s	-	subtraction
m	-	multiplication
d	-	division
p	-	exponentiation i.e. to the power of:   2 ^ 3 = 8  (base exponent p)

E3.	Basic invalid number detection:
Valid numbers are all numbers that the "average Engineering graduate" in Australia
would consider valid. Therefore if the first command line argument is not a valid number,
the output shall be 'X'. For example:
013			is valid
+3			is valid
-45			is valid
.3			is valid
ABC123		is not valid
1.3.4		is not valid
123abc		is not valid

E4. OUSB IO Board communication error:
If the pipe code communicating to the OUSB.exe file reports and issue with communication
to the OUSB IO Board, the output shall be 'Y'. This type of error can be forced by
disconnecting the USB cable between the PC and the OUSB IO Board.

Note: The OUSB.exe will give a message "Fatal Exception" if the board is not connected
or is disconnected during normal operation. This message should NOT be returned by your
code. The only output your code should give is the single character, 'Y' which is the same
as the return character as the MURPHY'S LAW TEST below.

E7. Input number range checking:

E7.1 If the value of the first command line argument is greater than 65536 or less than -65535
the output shall be 'R'. Zero is a valid input.

E7.2 All 8-bits of the OUSB Board DIP switches are valid. Therefore 0 to 255 will be valid inputs.

E8.	Division by zero should produce output 'M'. The LEDs on the OUSB Board should not be updated.

*/

#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <errno.h>   

using namespace std;

const double MAXRANGE = pow(2.0, 16.0); // 65536
const double MINRANGE = -pow(2.0, 16.0);

unsigned int ReadPinC()
{
	int pinc = 0;
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousbsim2 -r io PINC" };

	// pipe code that sends out the current Command stored in the command variable
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			// do nothing, or print out debug data
			//cout << "Debug line: " << line; // print out OUSB data
		}
		_pclose(fpipe);
	}

	// convert value from char array to int	
	pinc = (unsigned int)atoi(line);
	// Mask pinc value for bottom 8-bit only.
	pinc = pinc & 0x00FF;
	return pinc;
}

unsigned int WritePortB(unsigned int val)
{
	char line[255] = {};	// array to hold received data from the OUSB board
	FILE *fpipe;			// file variable, see text book module 11.
	char command[255] = { "ousbsim2 -r io PORTB " }; // Need to have a extra space after PORTB
	char val_string[4] = {};

	//Convert integer (in base 10) to character
	_itoa_s(val, val_string, 10);
	// append the value to the Command string
	strcat_s(command, val_string);

	// pipe code that sends out the current Command stored in the command variable
	fpipe = (FILE*)_popen(command, "r");
	if (fpipe != NULL)
	{
		while (fgets(line, sizeof(line), fpipe))
		{
			// do nothing, or print out debug data
			//cout << "Debug line: " << line; // print out OUSB data
		}
		_pclose(fpipe);
	}

	// convert value from char array to int	
	unsigned int portb = (unsigned int)atoi(line);
	return portb;
}

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		// When run with just the program name (no parameters) returns developer name
		cout << "Olivia_Robertson" << endl;
		return 0;
	}

	unsigned int num1 = 0;
	num1 = ReadPinC();

	double num2 = 0;
	double result = 0;

	bool X = false;
	bool V = false;
	bool R = false;
	int z = 0;
	char str2[255] = {};

	//input error checking - are the input values valid?
	for (int i = 0; argv[1][i]; i++)
	{
		if (isdigit(argv[1][i])){

		}
		else if (argv[1][i] == '-'){

		}
		else if (argv[1][i] == '+'){

		}
		else if (argv[1][i] == '.'){
			z++;
		}
		else if (argv[1][i] == 'e'){

		}
		else if (argv[1][i] == ','){
			int w = i;
			int k = 0;
			for (int j = 0; argv[1][j]; j++)
			{
				if (j != w)
				{
					str2[k] = argv[1][j];
					k++;
				}
				else
				{
				}
			}
		}
		else{
			cout << "X" << endl;
			X = true;
			break;
		}

		if (z >= 2){
			cout << "X" << endl;
			X = true;
			break;
		}
	}

	// if no error has been detected in the value inputs, continue 
	if (X == false){
		num2 = atof(str2);
		//num2 = atof(argv[1]);

		// operator check
		if (argc == 2){
			// range check
			if ((num2 >= 65536) || (num2 < -65535))
			{
				cout << "R" << endl;
			}
			result = num1 + num2;
			cout << result << endl;

			unsigned int boardout = (int)abs(result);
			if (boardout > 255)
				boardout = 255;
			// debugging
			cout << boardout << endl;
			WritePortB(boardout);
		}

		if (argc == 3){
			for (int i = 1; argv[2][i]; i++)
			{
				if (i != '\0')
				{
					cout << "V" << endl;
					V = true;
					break;
				}
			}
			if (V == false)
			{
				// range check
				if ((num2 >= 65536) || (num2 < -65535))
				{
					cout << "R" << endl;
					R = true;
				}
			}
			if ((V == false) && (R == false))
			{
				if (argv[2][0] == 'a')
				{
					result = num1 + num2;
					cout << result << endl;

					unsigned int boardout = (int)abs(result);
					if (boardout > 255)
						boardout = 255;
					// debugging
					cout << boardout << endl;
					WritePortB(boardout);
				}
				else if (argv[2][0] == 's')
				{
					result = num1 - num2;
					cout << result << endl;

					unsigned int boardout = (int)abs(result);
					if (boardout > 255)
						boardout = 255;
					// debugging
					cout << boardout << endl;
					WritePortB(boardout);
				}
				else if (argv[2][0] == 'm')
				{
					result = num1 * num2;
					cout << result << endl;

					unsigned int boardout = (int)abs(result);
					if (boardout > 255)
						boardout = 255;
					// debugging
					cout << boardout << endl;
					WritePortB(boardout);
				}
				else if (argv[2][0] == 'd')
				{
					if (argv[1][0] == '0')
					{
						cout << "M" << endl;
					}
					else
					{
						result = num1 / num2;
						cout << result << endl;

						unsigned int boardout = (int)abs(result);
						if (boardout > 255)
							boardout = 255;
						// debugging
						cout << boardout << endl;
						WritePortB(boardout);
					}
				}
				else if (argv[2][0] == 'p')
				{
					result = pow(num1, num2);
					cout << result << endl;

					unsigned int boardout = (int)abs(result);
					if (boardout > 255)
						boardout = 255;
					// debugging
					cout << boardout << endl;
					WritePortB(boardout);
				}
				else
				{
					cout << "V" << endl;
					V = true;
				}
			}
		}
	}
	if (argc >= 4){
		cout << "P" << endl;
	}

	return 0;
} 


   // End of file. 
