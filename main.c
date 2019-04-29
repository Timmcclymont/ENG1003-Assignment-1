//
//  ENGG1003 Assignment 1
//
//
//  Created by Tim McClymont
//
//A program written in C to perform various (basic) text cipher encryption/decryption and cracking
//functions. Inputs and outputs for cipher text are in capitals. This program performs two separate
//cipher types: Caesar cipher (or rotation cipher) and substitution cipher.
//
//In addition to encrypting and decrypting text with a known key:
//This program also cracks rotation ciphers correctly using a dictionary file of 10,000 common english
//words as a lookup table to confirm successful decryption before printing the result to the user.
//
//The substitution cipher cracking function is under test and currently implements english character
//freqency analysis of the cipher text in order to attempt decryption with a list of most commonly
//used english letters.
//
// Menu system:
//      Caesar Cipher: 1
//Substitution Cipher: 2
//     Crack Rotation: 3
// Crack Substitution: 4
//User selectable by typing the desired item number and pressing <enter>
//
//Caesar and Substitution ciphers have the following additional menus:
//Enter Selection:
//            Encrypt: 0
//            Decrypt: 1
//This prompts the user to select a sub-function of the encryption method.


#include<stdio.h>
#include<string.h>
#include<ctype.h> //ctype.h required in order to perform string compare line 40-45 ignoring case of string text
// File Paths
#define DICTIONARY "dictionary.txt"

//SUB1 is the first canned substition text from blackboard. It is defined here as SUB1 for easy use later in the substition cracker function
#define SUB1 "RCR VYE BGBX HBNX FHB FXNQBRV YM RNXFH IZNQEBCJ FHB PCJB? C FHYEQHF KYF. CF'J KYF N JFYXV FHB DBRC PYEZR FBZZ VYE. CF'J N JCFH ZBQBKR. RNXFH IZNQEBCJ PNJ N RNXA ZYXR YM FHB JCFH, JY IYPBXMEZ NKR JY PCJB HB LYEZR EJB FHB MYXLB FY CKMZEBKLB FHB OCRCLHZYXCNKJ FY LXBNFB ZCMB… HB HNR JELH N AKYPZBRQB YM FHB RNXA JCRB FHNF HB LYEZR BGBK ABBI FHB YKBJ HB LNXBR NWYEF MXYO RVCKQ. FHB RNXA JCRB YM FHB MYXLB CJ N INFHPNV FY ONKV NWCZCFCBJ JYOB LYKJCRBX FY WB EKKNFEXNZ. HB WBLNOB JY IYPBXMEZ… FHB YKZV FHCKQ HB PNJ NMXNCR YM PNJ ZYJCKQ HCJ IYPBX, PHCLH BGBKFENZZV, YM LYEXJB, HB RCR. EKMYXFEKNFBZV, HB FNEQHF HCJ NIIXBKFCLB BGBXVFHCKQ HB AKBP, FHBK HCJ NIIXBKFCLB ACZZBR HCO CK HCJ JZBBI. CXYKCL. HB LYEZR JNGB YFHBXJ MXYO RBNFH, WEF KYF HCOJBZM"
//second canned substitution text 2 for testing
#define SUB2 "N KBP JLCBKFCMCL FXEFH RYBJ KYF FXCEOIH WV LYKGCKLCKQ CFJ YIIYKBKFJ NKR ONACKQ FHBO JBB FHB ZCQHF, WEF XNFHBX WBLNEJB CFJ YIIYKBKFJ BGBKFENZZV RCB, NKR N KBP QBKBXNFCYK QXYPJ EI FHNF CJ MNOCZCNX PCFH CF. - ONU IZNKLA."

// Define state handles for selection of crypto mode
#define STATE_CAESAR 1
#define STATE_SUBST 2
#define STATE_CRACK_CAESAR 3
#define STATE_CRACK_SUBST 4


//constant global variables (the alphabet in capitals) used in the substitution cipher function.
const char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

void swapInt(int *xp, int *yp) { // This function swaps integer values pointed by xp and yp its used in the substitution crack function only
  int temp = *xp;//initialise char temp to *xp holding its value for use later
  *xp = *yp; //now set *xp to *yp
  *yp = temp; //finally set *yp to the value stored in 'temp' which was originally *xp
}

void swapChar(char *xp, char *yp) { // This function swaps char values pointed by xp and yp as above
  char temp = *xp; //initialise char temp to *xp holding its value for use later
  *xp = *yp; //now set *xp to *yp
  *yp = temp; //finally set *yp to the value stored in 'temp' which was originally *xp
}

//– What are the inputs? - User plaintext capitals only (lowercase passed through) and encryption key
//– What is the return value? - void
//– What does the function do? - Caesar cipher encryption/decryption function which takes user input in the form of plaintext
//and converts it to encrypted text and vice versa given a numerical encryption key (0-26) from the user
//– Are there limitations to the function? - Strings of less than 1024 character length and only upper case characters.
void caesar(void){
  const int encrypt = 0; //declare two constant variables encrypt (0) and decrypt (1) these are usec for function selection in the menu system
  const int decrypt = 1;
  int mode; //declare a single integer 'mode' for the storage of user input for menu selection

  // Select encrypt/decrypt
  printf("\nEnter Selection:\n            Encrypt: 0\n            Decrypt: 1\n "); //menu with formatting for selection of encryption function mode
  scanf(" %d" ,&mode); //store user integer value for mode selection

  if (mode == encrypt) { //if user selected mode = constant variable encrypt (0) perform this function
    char text[1024], character; //char declaration, function is limited to a maximum input text length of 1024 chracters
    int encryptionKey; //integer declaration for the user inputted encryption key 0-26

    printf("Enter plaintext message: "); //promt the user to enter the plaintext message to be encrypted
    scanf(" %[^\n]s" ,text); //store this text on char variable 'text'
    printf("Enter encryption key: "); //prompt the user to enter the encryption key
    scanf(" %d", &encryptionKey); //store the encryption key on int variable 'encryptionKey'


    for(int i = 0; text[i] != '\0'; i++){ //for loop to step through each character in array text[i] as long as text does not equal a null character (stored at end of array)
      character = text[i]; //set character to the i'th letter in the text array

      if(character >= 'A' && character <= 'Z'){ //test the character is in the range of A - Z
        character = character + encryptionKey; //if the character is in the range increment it by the value of encryption key

        if(character > 'Z'){
          character = character - 'Z' + 'A' - 1; //deals with lowercase out of range characters and special ASCII characters
        }

        text[i] = character; //set the text at i'th index position to the now encrypted character
      }
    }

    printf("Encrypted message: %s \n", text);

  }
  else if(mode == decrypt) { //if user selected mode = constant variable decrypt (1) perform this function
    char text[1024], character;
    int i, encryptionKey;
    //variable declarations are as per the encryption function above nothing new here
    printf("Enter encrypted message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter encryption key: ");
    scanf(" %d", &encryptionKey);
    //Decryption function is exactly the same however instead of adding the encryption key, it subtracts the key
    for(i = 0; text[i] != '\0'; i++){
      character = text[i];

      if(character >= 'A' && character <= 'Z'){
        character = character - encryptionKey; //subtraction of the encryption key rather than addition like the encrypt function

        if(character < 'A'){
          character = character + 'Z' - 'A' + 1; //inverse of the encrypt function to deal with lowercase letters being turned into special characters
        }

        text[i] = character;
      }
    }

    printf("Decrypted message: %s \n", text); //print the decrypted message to the terminal

  } else {
    printf("Invalid selection\n"); //if the user enters a value that != 1 or 0 then this error is displayed.
  }
}

//– What are the inputs? - User plaintext capitals only (lowercase passed through) and encryption key
//– What is the return value? - void
//– What does the function do? - Caesar cipher encryption/decryption function which takes user input in the form of plaintext
//and converts it to encrypted text and vice versa given an alphabetical encryption key from the user
//– Are there limitations to the function? - Strings of less than 1024 character length and only upper case characters.
void substitution(void) {
  const int encrypt = 0; //declare two constant variables encrypt (0) and decrypt (1) these are usec for function selection in the menu system
  const int decrypt = 1;
  int mode;

  char text[1024], character;
  char encryptionKey[26];


  // Select encrypt/decrypt
  printf("\nEnter Selection:\n            Encrypt: 0\n            Decrypt: 1\n "); //menu with formatting for selection of encryption function mode
  scanf(" %d" ,&mode); //store user integer value for mode selection

  if (mode == encrypt) { //if user selected mode = constant variable encrypt (0) perform this function

    printf("Enter plaintext message: "); //prompt the user to enter the plaintext message to be encrypted
    scanf(" %[^\n]s" ,text); //store this text on char variable 'text'
    printf("Enter 26 character encryption key: "); //prompt the user to enter the encryption key
    scanf(" %s", encryptionKey); //store the encryption key on char variable 'encryptionKey'

    // Loop through plaintext message
    for(int i=0; i<strlen(text); i++){ //loops using the function strlen (string length) which is the number of characters in variable 'text'
      for(int j=0; j<26; j++){ //for the length of characters in the alphabet (26) continue to loop so long as j !<26
        if(text[i] == alphabet[j] ){
          //Replace letter with its corresponding encryption key character of index j
          text[i] = encryptionKey[j];
          break;
        }
      }
    }
    printf("Encrypted text: \n%s\n", text); //print the encrypted text to the console for the user

  } else if (mode == decrypt){ //if user selected mode = constant variable decrypt (1) perform this function
    // Decryption Code
    printf("Enter encrypted message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter 26 character encryption key: ");
    scanf(" %s", encryptionKey);

    // Loop through encrypted message
    for(int i=0; i<strlen(text); i++){
      // Finding what letter
      for(int j=0; j<26; j++){
        if(text[i] == encryptionKey[j] ){
          //Replace letter with matching alphabet character
          text[i] = alphabet[j]; //constant global variable 'alphabet' is used here, so each letter of encrypted text indexed correclty with the encryption key gets replaced with its corresponding j'th alphabet character
          break;
        }
      }
    }
    printf("Decrypted text: \n%s\n", text); //print the newly decrypted text to the console for the user

  } else {
    printf("Invalid selection\n"); //notify the user that an incorrect substitution cipher mode has been entered
  }
}

//– What are the inputs? - User plaintext capitals only (lowercase passed through) only
//– What is the return value? - void
//– What does the function do? - Substitution decryption function which takes user input in the form of encrypted Text
//and converts it to plaintext based on a frequency analysis of most commonly used english characters distribution using and requires the use of
//two functions swapInt and swapChar to index two arrays of arranged letters.
//– Are there limitations to the function? - Strings of less than 2048 character length and only upper case characters.
// This function is also under test and therfore not fully functional, it uses defined fixed variable SUB1 and has printF input commented out.
void crackSubstitution(void){
  int freqs[26]; // Frequencies of occurance
  for (int i=0; i < 26; i++) {freqs[i] = 0;} // Initialise array of zeros
  char seen[26];
  char text[2048] = SUB1;
  int lenSeen = 0;
  int len = strlen(text);

  // printf("Enter cipher to crack: "); //Prompt the user for cipher text input
  // scanf(" %[^\n]s" , text);   //store the users cipher text input on char variable 'text'

  // Step through encrypted text and accumulate unlabelled frequencies

  // Step through every letter in the text
  for (int i = 0; i < len; i++) {
    if(text[i] >= 'A' && text[i] <= 'Z'){ // Is it a letter between A-Z?
      //Has letter been seen before?
      for (int j = 0; j < 26; j++) {
        if(text[i] == seen[j]) { //test this character as to whether its been seen before
          freqs[j]++;
          break;
        } else {  // If never seen, accumulate and add an occurance
          if (j >= lenSeen) {
            lenSeen++;
            seen[j] = text[i];
            freqs[j]++;
            break;
          }
        }
      }
    }

  }

  // Now, we have an array of unique, seen letters (seen), and a corresponding array of occurences (freqs)
  // Sort the array of occurences in descending order, and mirror that sorting in the array of letters
  int i, j;
  for (i = 0; i < lenSeen-1; i++){
    // Last i elements are already in place
    for (j = 0; j < lenSeen-i-1; j++) //sort the the array of occurences in descending order
    if (freqs[j] < freqs[j+1]) {
      swapInt(&freqs[j], &freqs[j+1]);
      swapChar(&seen[j], &seen[j+1]); //mirror the frequency array in the seen letter array
    }
  }

  // Assume ideal freq. distribution of english letters
  const char letterDistIdeal[26] = {'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','X','Q','Z'};
  // Now perform substitution decryption exactly the same as the substitution decryption function detailed above
  // Loop through encrypted message
  for(int i=0; i<strlen(text); i++){ //for loop to loop through the entire encrypted message character by character and replace each with the corresponding ideal freq letter
    // Finding what letter
    for(int j=0; j<lenSeen; j++){
      if(text[i] == seen[j] ){
        //Replace letter with matching alphabet character
        text[i] = letterDistIdeal[j]; //for the i'th and j'th indexed letters replace text with its corresponding indexed 'ideal frequncy letter E, T, A, O...'
        break; //break out of the for loop after i (counter) becomes greater that the string length of 'text'
      }
    }
  }
  printf("Decrypted text: \n%s\n", text); //prints the decrypted text stored on the 'text' variable to the console


}

int strcicmp(char const *a, char const *b) {
  // String compare that ignores case of the characters
  for (;; a++, b++) {
    int d = tolower((unsigned char)*a) - tolower((unsigned char)*b); //tolower requires ctype.h library
    if (d != 0 || !*a)
    return d;
  }
}

int dictionaryLookup(char *word){ // Return 0 if argument string is found in a dictionary file, else return 1

  FILE *dictFile;
  dictFile = fopen(DICTIONARY,"r"); //open defined DICTIONARY into file: dictFile as read only
  char dictWord[30];  // A temporary holder for an individual dictionary word
  int test = 0;       // Holds the returned status of fscanf 1 or 0 depending on a match being found
  // Compare a string against every entry in the dictionary
  while(test != EOF){
    test = fscanf(dictFile,"%s",dictWord); //get a word from the dictionary, store in dictWord array
    //if decrypted word matches a word in the dictionary, increment that key's score
    if (strcasecmp(word,dictWord) == 0) { // strcasecmp (UNIX systems) ignores case this is not a portable libray so will likely return errors on other OS'

    fclose(dictFile); //closes dictFile
    return 0; // match found
  }
}
fclose(dictFile); //closes dictFile
return 1; // No match found
}

//– What are the inputs? - User plaintext capitals only (lowercase passed through) only
//– What is the return value? - void
//– What does the function do? - Caesar cipher decryption function which takes user input in the form of encrypted Text
//and converts it to plaintext based on a dictionary lookup function of file: dictionary.txt using function dictionaryLookup
//– Are there limitations to the function? - Strings of less than 2048 character length and only upper case characters.
void crackRotation(void) {

  char text[2048] = {0};
  char decipherText[2048] = {0};
  char character;
  int scores[26];
  for(int i = 0; i < 26; i++) { //sets each array value to 0
    scores[i]=0;
  } // Array to hold number of real words found for each decryption key. Initialise with zeros.

  // Prompt for cihpertext to decrypt from the user. Store in array 'text'.
  printf("Enter cipher to crack: ");
  scanf(" %[^\n]s" , text);

  // Loop through all possible keys and count number of dictionary words found for each key
  for(int encryptionKey = 0; encryptionKey < 25; encryptionKey++) {
    // Step 1: Perform decryption with current key (offset) same as the function used in rotation cipher
    for(int i = 0; text[i] != '\0'; i++){
      character = text[i];

      if(character >= 'A' && character <= 'Z'){
        character = character - encryptionKey;

        if(character < 'A' && character != ' '){
          character = character + 'Z' - 'A' + 1;
        }
      }
      decipherText[i] = character;
    }

    // Step 2: Tokenise the deciphertext and count how many dictionary words appear. Increment that key's score for each match
    char * pch;
    pch = strtok (decipherText," ,.-:"); //pch points to the first tokeknised word
    while (pch != NULL)
    {
      int result = dictionaryLookup(pch);
      if (result == 0) { //if a match is found in the dictionary increment the key's score
      scores[encryptionKey]++;
    }
    pch = strtok (NULL, " ,.-:"); //move to the next decipher text 'word'
  }

}

// Step 3: Find the highest scoring key
int maxScore = 0;
int encryptionKey = 0;
for(int i=0; i < 25; i++) {
  if(scores[i] > maxScore) {
    maxScore = scores[i];
    encryptionKey = i;
  }
}

printf("found key: %d\n", encryptionKey);

// Step 4: Final decipher with the best key
for(int i = 0; text[i] != '\0'; i++){
  character = text[i];

  if(character >= 'A' && character <= 'Z'){
    character = character - encryptionKey;

    if(character < 'A' && character != ' '){
      character = character + 'Z' - 'A' + 1;
    }
  }
  decipherText[i] = character;
}

// Step 5: Print deciphered text
printf("Deciphered Text:\n%s\n",decipherText);

}

int main() {

  while(1) {
    // Prompt for cipher function
    printf("\n\n\n   ENG1003 Assignment 1\n   ====================\n      Caesar Cipher: 1\nSubstitution Cipher: 2\n     Crack Rotation: 3\n Crack Substitution: 4\n");
    int state; // Determines which program to run.
    scanf(" %d" ,&state);

    // The state-machine: jump to the user-selected cipher algorithm
    switch(state) { //simple switch case function with 4 potential options 1-4 and a default returning an error message
      case STATE_CAESAR:
      caesar(); //jump to the caesar cipher function
      break;

      case STATE_SUBST:
      substitution(); //jump to the substitution cipher function
      break;

      case STATE_CRACK_SUBST:
      crackSubstitution(); //jump to the crack substitution function
      break;

      case STATE_CRACK_CAESAR:
      crackRotation(); //jump to the rotation cipher function
      break;

      default: printf("Incorrect input, enter a number 1 - 4 to select a mode"); //if no valid option is entered by the user this default statement prompts the user

    }

  }


}
