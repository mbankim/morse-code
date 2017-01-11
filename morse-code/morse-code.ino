/* The program accepts a line of text from the serial input
 * and transmits Morse encoding using the green LED.
 */

#define LED GREEN_LED

//length of time to flash
int DOT = 1000;
int DASH = 3000;
int SKIP = 0;

/* Delays between each of signals, letters, words
 * DELAY_SIGNAL subtracted from WORD and LETTER to account
 * for the signal delay after each signal, regardless of
 * whether a new word or letter occurs
 */
int DELAY_SIGNAL = 1000;
int DELAY_LETTER = 3000-DELAY_SIGNAL;
int DELAY_WORD = 7000-DELAY_LETTER-DELAY_SIGNAL;

//ascii for min/max letters, used to find the index in MORSE_ALPHA
int ASCII_a = 97;
int ASCII_z = 122;
int ASCII_A = 65;
int ASCII_Z = 90;
//for reading input
int incomingByte = 0;
// flag to detect multiple spaces.
int newWord = 1;

//a=0, b=1, etc.
int MORSE_ALPHA[][4] = {
{SKIP, SKIP, DOT, DASH},  //A
{DASH, DOT, DOT, DOT},    //B
{DASH, DOT, DASH, DOT},   //C
{SKIP, DASH, DOT, DOT},   //D
{SKIP, SKIP, SKIP, DOT},  //E
{DOT, DOT, DASH, DOT},    //F
{SKIP, DASH, DASH, DOT},  //G
{DOT, DOT, DOT, DOT},     //H
{SKIP, SKIP, DOT, DOT},   //I
{DOT, DASH, DASH, DASH},  //J
{SKIP, DASH, DOT, DASH},  //K
{DOT, DASH, DOT, DOT},    //L
{SKIP, SKIP, DASH, DASH}, //M
{SKIP, SKIP, DASH, DOT},  //N
{SKIP, DASH, DASH, DASH}, //O
{DOT, DASH, DASH, DOT},   //P
{DASH, DASH, DOT, DASH},  //Q
{SKIP, DOT, DASH, DOT},   //R
{SKIP, DOT, DOT, DOT},    //S
{SKIP, SKIP, SKIP, DASH}, //T
{SKIP, DOT, DOT, DASH},   //U
{DOT, DOT, DOT, DASH},    //V
{SKIP, DOT, DASH, DASH},  //W
{DASH, DOT, DOT, DASH},   //X
{DASH, DOT, DASH, DASH},  //Y
{DASH, DASH, DOT, DOT}};  //Z

//method to flash for the appropriate time
void flash(int signal) {
    //signal can be DOT, DASH, or SKIP (do nothing)
    if (signal==SKIP) return;

    digitalWrite(LED, HIGH);
    delay(signal);
    digitalWrite(LED, LOW);
    delay(DELAY_SIGNAL);
}

// signals the letter at the specified index
void letter(int idx) {
    for(int i = 0; i < 4; i++)
        flash(MORSE_ALPHA[idx][i]);

    //delay after the letter
    delay(DELAY_LETTER);

    //also resets the newWord flag
    newWord = 0;
}

void setup()
{
    //Enable LED and Serial I/O
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0) {
        //executes when data is received
        incomingByte = Serial.read();

        //using ascii, check lower case first (a=97, b=98, ..., z=122)
        if (incomingByte >= ASCII_a && incomingByte <= ASCII_z) {
            letter(incomingByte-ASCII_a);
        }
        //next check upper case (A=65, B=66, ..., Z=90)
        else if (incomingByte >= ASCII_A && incomingByte <= ASCII_Z) {
            letter(incomingByte-ASCII_A);
        }
        //next, check for new words and multiple spaces
        else if (incomingByte == 32 && newWord==0) {
            newWord = 1;
            delay(DELAY_WORD);
        }
        //ignore everything else
    }
}


