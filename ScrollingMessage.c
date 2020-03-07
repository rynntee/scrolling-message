/*
 * Author: Rynn Tee
 * Course: APSC 160
 * Purpose: Option 1 - Scrolling message across an 8 LED display
 * Bonus: Part B - User can choose 1 of 2 predetermined messages
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <DAQlib.h>
#include <Windows.h>

/* True or false */
#define TRUE 1
#define FALSE 0

/* Lenght of time between each move on LED display (in milliseconds)*/
#define DELAY_TIME 1000

/* LED Display Positions */
#define POSITION_0 0
#define POSITION_1 1
#define POSITION_2 2
#define POSITION_3 3
#define POSITION_4 4
#define POSITION_5 5
#define POSITION_6 6
#define POSITION_7 7

/* function prototypes */
void scrollMessage(void);
void writeMessage(int numCharacters, int messageNum);
void writeCharacter(int character, int position, int messageNum);


/* main Function */
int main(void)
{
    int setupNum;

    printf("Enter the setup number for DAQ (0 for the device or 4 for the simulator): ");
    scanf("%d", &setupNum);

	/*
	** Calling the setupDAQ function to initialise DAQ
    ** If the return value of the setupDAQ function call is TRUE, initialisation is
	** successful.
	*/

    if ( setupDAQ(setupNum) == TRUE )
        scrollMessage();
    else
        printf("ERROR: Cannot initialise DAQ\n");

    system("PAUSE");
    return 0;
}
/* <scrollMessage function> 
 * Asks user to choose 1 of 2 messages,
 * then scrolls the message across LED
 * Parameters: none
 */
void scrollMessage(void)
{
	int messageNum; // user's option of which message to display
	

	printf("Please choose which message to display:");
			printf("\nMessage 1: Hello");
			printf("\nMessage 2: Goodbye");
			printf("\nPlease enter 1 or 2: ");
			scanf("%d", &messageNum);
	
    while( continueSuperLoop() == TRUE )
    {
		
		int numCharacters;	// number of characters in the word
				
			// Message 1 - word is Hello. 
			if (messageNum == 1)
			{
				numCharacters = 5;
			}
			
			// Message 2 - word is Goodbye
			else if (messageNum == 2)
			{
				numCharacters = 7;
			}

			writeMessage(numCharacters, messageNum);	
		
    }
}

/* <writeMessage function> 
 * Write message to the LED display
 * Parameters: 
 * numCharacters - number of characters in the word you are scrolling 
 * messageNum - which message is chosen by user to display
 */
void writeMessage(int numCharacters, int messageNum)
{
		// Variables to represent the index of the characters (from the message arrays) shown on the LED 
		// There are 8 characters, 1 for each LED screen
		int character1 = numCharacters - numCharacters;				// character1 is set as 0
		int character2 = numCharacters - (numCharacters + 1);		// character2 is set as -1, which is 1 less than 0
		int character3 = numCharacters - (numCharacters + 2);		// character3 is set as -2, which is 2 less than 0
		int character4 = numCharacters - (numCharacters + 3);		// etc
		int character5 = numCharacters - (numCharacters + 4);		// etc
		int character6 = numCharacters - (numCharacters + 5);
		int character7 = numCharacters - (numCharacters + 6);
		int character8 = numCharacters - (numCharacters + 7);


			// numCharacters + 7 because that's how many configurations there are to
			//	       scroll the entire word across the display, plus 1 second of blank 
			// Use "while" to run a loop - message will continue scrolling non-stop until users quit
			while (character1 <= (numCharacters + 7))	
				{
					// Use (character... > 0) - so will only display the characters from the message arrays
					//    since 0th term is a placeholder 

					// LED position 0 will display the first character of the message first
					if (character1 > 0)
					{
						writeCharacter(character1, POSITION_0, messageNum);
					}
					
					// LED position 1 will display the first character of the message 
					//    1 second after LED position 0 displays the first character
					//    (since character2 was set as -1 at the beginning)
					if (character2 > 0)
					{
						writeCharacter(character2, POSITION_1, messageNum);
					}

					// LED position 2 will display the first character of the message 
					//    2 seconds after LED position 0 displays the first character
					//    (since character3 was set as -2 at the beginning)
					if (character3 > 0)
					{
						writeCharacter(character3, POSITION_2, messageNum);
					}

					// etc, see above for logic
					if (character4 > 0)
					{
						writeCharacter(character4, POSITION_3, messageNum);
					}

					if (character5 > 0)
					{
						writeCharacter(character5, POSITION_4, messageNum);
					}

					if (character6 > 0)
					{
						writeCharacter(character6, POSITION_5, messageNum);
					}

					if (character7 > 0)
					{
						writeCharacter(character7, POSITION_6, messageNum);
					}

					if (character8 > 0)
					{
						writeCharacter(character8, POSITION_7, messageNum);
					}
					
					
					Sleep(DELAY_TIME);	// word will scroll every 1 second, or 1000 milliseconds
					
					// incrementing, so each position will display the next letter in the message array
					character1++;
					character2++;
					character3++;
					character4++;
					character5++;
					character6++;
					character7++;
					character8++;
					
					// reset character variables to 0, to begin loop again from beginning
					if (character1 > (numCharacters + 7))
					{
						character1 = 0;
					}

					if (character2 > (numCharacters + 7))
					{
						character2 = 0;
					}

					if (character3 > (numCharacters + 7))
					{
						character3 = 0;
					}

					if (character4 > (numCharacters + 7))
					{
						character4 = 0;
					}
				
					if (character5 > (numCharacters + 7))
					{
						character5 = 0;
					}
					
					if (character6 > (numCharacters + 7))
					{
						character6 = 0;
					}
					
					if (character7 > (numCharacters + 7))
					{
						character7 = 0;
					}
					
					if (character8 > (numCharacters + 7))
					{
						character8 = 0;
					}	
			} 
}
	
	
/* <writeCharacter function> 
 * Lights up the appropriate segments of the LED
 * Parameters: 
 * characeterIndex - index of letter needed in array
 * position - position of LED where segments are lit up/characters are displayed
 * messageNum - the message that is chose by the user
 */
void writeCharacter(int characterIndex, int position, int messageNum)
{
	
	/*The first character in the arrays ("0") is a placeholder*/
	// message 1 word: Hello
	if (messageNum == 1)
	{
		static int testMessage1[12] = {0, 110, 158, 28, 28, 252};
		displayWrite(testMessage1[characterIndex], position);
	}

	// message 2 word: Goodbye
	if (messageNum == 2)
	{
		static int testMessage2[14] = {0, 246, 252, 252, 122, 62, 118, 158};
		displayWrite(testMessage2[characterIndex], position);
	}

}