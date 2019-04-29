//
//  GENG1003 Assignment 1
//
//
//  Created by Tim McClymont
//

#include<stdio.h>
#include<string.h>
#include<ctype.h> //ctype.h required in order to perform string compare line 40-45 ignoring case of string text
// File Paths
#define DICTIONARY "dictionary.txt"

//SUB1 is the first canned substition text from blackboard. It is defined here as SUB1 for easy use later in the substition cracker function
#define SUB1 "RCR VYE BGBX HBNX FHB FXNQBRV YM RNXFH IZNQEBCJ FHB PCJB? C FHYEQHF KYF. CF'J KYF N JFYXV FHB DBRC PYEZR FBZZ VYE. CF'J N JCFH ZBQBKR. RNXFH IZNQEBCJ PNJ N RNXA ZYXR YM FHB JCFH, JY IYPBXMEZ NKR JY PCJB HB LYEZR EJB FHB MYXLB FY CKMZEBKLB FHB OCRCLHZYXCNKJ FY LXBNFB ZCMB… HB HNR JELH N AKYPZBRQB YM FHB RNXA JCRB FHNF HB LYEZR BGBK ABBI FHB YKBJ HB LNXBR NWYEF MXYO RVCKQ. FHB RNXA JCRB YM FHB MYXLB CJ N INFHPNV FY ONKV NWCZCFCBJ JYOB LYKJCRBX FY WB EKKNFEXNZ. HB WBLNOB JY IYPBXMEZ… FHB YKZV FHCKQ HB PNJ NMXNCR YM PNJ ZYJCKQ HCJ IYPBX, PHCLH BGBKFENZZV, YM LYEXJB, HB RCR. EKMYXFEKNFBZV, HB FNEQHF HCJ NIIXBKFCLB BGBXVFHCKQ HB AKBP, FHBK HCJ NIIXBKFCLB ACZZBR HCO CK HCJ JZBBI. CXYKCL. HB LYEZR JNGB YFHBXJ MXYO RBNFH, WEF KYF HCOJBZM."
// Define state handles for selection of crypto mode
#define STATE_CAESAR 1
#define STATE_SUBST 2
#define STATE_CRACK_CAESAR 3
#define STATE_CRACK_SUBST 4


//constant global variables (the alphabet capitals) used later.
const char alphabet[26]={'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

void swapInt(int *xp, int *yp) {
  int temp = *xp;
  *xp = *yp;
  *yp = temp;
}
void swapChar(char *xp, char *yp) {
  char temp = *xp;
  *xp = *yp;
  *yp = temp;
}

int strcicmp(char const *a, char const *b) {
  // String compare that ignores case
  for (;; a++, b++) {
    int d = tolower((unsigned char)*a) - tolower((unsigned char)*b);
    if (d != 0 || !*a)
    return d;
  }
}

void substitution(void) {
  const int encrypt = 0;
  const int decrypt = 1;
  int mode;

  char text[1024], character;
  char encryptionKey[26];


  // Select encrypt/decrypt
  printf("\nEnter Selection:\n            Encrypt: 0\n            Decrypt: 1\n ");
  scanf(" %d" ,&mode);

  if (mode == encrypt) {
    // Encryption Code

    printf("Enter plaintext message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter 26 character encryption key: ");
    scanf(" %s", encryptionKey);

    // Loop through plaintext message
    for(int i=0; i<strlen(text); i++){
      // Finding what letters
      for(int j=0; j<26; j++){
        if(text[i] == alphabet[j] ){
          //Replace letter with matching encryption key character
          text[i] = encryptionKey[j];
          break;
        }
      }
    }
    printf("Encrypted text: \n%s\n", text);

  } else if (mode == decrypt){
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
          text[i] = alphabet[j];
          break;
        }
      }
    }
    printf("Decrypted text: \n%s\n", text);

  } else {
    printf("Invalid selection\n");
  }
}

void caesar(void){
  const int encrypt = 0; //declare two constant variables encrypt (0) and decrypt (1) these are usec for function selection in the menu system
  const int decrypt = 1;
  int mode; //declare a single integer mode for the storage of user input for menu selection

  //char text[1024], character; //two char variables 'character' and 'text' of length 1024 (arbitrary array length for storage of user encrypt/decrypt text)
  //char encryptionKey[26]; //encryption key array of length 26 for

  // Select encrypt/decrypt
  printf("\nEnter Selection:\n            Encrypt: 0\n            Decrypt: 1\n ");
  scanf(" %d" ,&mode);

  if (mode == encrypt) {
    char text[1024], character;
    int encryptionKey;

    printf("Enter plaintext message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter encryption key: ");
    scanf(" %d", &encryptionKey);


    for(int i = 0; text[i] != '\0'; i++){
      character = text[i];

      if(character >= 'A' && character <= 'Z'){
        character = character + encryptionKey;

        if(character > 'Z'){
          character = character - 'Z' + 'A' - 1;
        }

        text[i] = character;
      }
    }

    printf("Encrypted message: %s \n", text);

  }
  else if(mode == decrypt) {
    char text[1024], character;
    int i, encryptionKey;

    printf("Enter encrypted message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter encryption key: ");
    scanf(" %d", &encryptionKey);

    for(i = 0; text[i] != '\0'; i++){
      character = text[i];

      if(character >= 'A' && character <= 'Z'){
        character = character - encryptionKey;

        if(character < 'A'){
          character = character + 'Z' - 'A' + 1;
        }

        text[i] = character;
      }
    }

    printf("Decrypted message: %s \n", text);

  } else {
    printf("Invalid selection\n");
  }
}

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
    if(text[i] >= 'A' && text[i] <= 'Z'){ // Is it a letter?
      //Has letter been seen before?
      for (int j = 0; j < 26; j++) {
        if(text[i] == seen[j]) {
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
  const char letterDistIdeal[26] = {'E','T','A','O','I','N','S','R','D','H','L','U','C','M','W','F','Y','G','P','B','V','K','X','Q','J','Z'};
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
