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

// Define state handles for selection of crypto mode
#define STATE_CAESAR 1
#define STATE_SUBST 2
#define STATE_CRACK_CAESAR 3
#define STATE_CRACK_SUBST 4


// Global variables
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
  printf("\nEnter:\n0:Encrypt\n1:Decrypt\n ");
  scanf(" %d" ,&mode);

  if (mode == encrypt) {
    // Encryption Code

    printf("Enter plaintext message: ");
    scanf(" %[^\n]s" ,text);
    printf("Enter 26 character encryption key: ");
    scanf(" %s", encryptionKey);

    // Loop through plaintext message
    for(int i=0; i<strlen(text); i++){
      // Finding what letter
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
  const int encrypt = 0;
  const int decrypt = 1;
  int mode;

  char text[1024], character;
  char encryptionKey[26];

  // Select encrypt/decrypt
  printf("Enter:\n0:Encrypt\n1:Decrypt\n ");
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
  char text[2048];
  int lenSeen = 0;
  int len = strlen(text);

  printf("Enter cipher to crack: "); //Prompt the user for cipher text input
  scanf(" %[^\n]s" , text);   //store the users cipher text input on char variable 'text'

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
    for (j = 0; j < lenSeen-i-1; j++)
    if (freqs[j] < freqs[j+1]) {
      swapInt(&freqs[j], &freqs[j+1]);
      swapChar(&seen[j], &seen[j+1]);
    }
  }

  // Assume ideal freq. distribution
  const char letterDistIdeal[26] = {'E','T','A','O','I','N','S','H','R','D','L','C','U','M','W','F','G','Y','P','B','V','K','J','X','Q','Z'};
  // Now perform substitution decryption
  // Loop through encrypted message
  for(int i=0; i<strlen(text); i++){
    // Finding what letter
    for(int j=0; j<lenSeen; j++){
      if(text[i] == seen[j] ){
        //Replace letter with matching alphabet character
        text[i] = letterDistIdeal[j];
        break;
      }
    }
  }
  printf("Decrypted text: \n%s\n", text);


}

// Return 0 if argument string is found in a dictionary file, else return 1
int dictionaryLookup(char *word){
  // Open the dictionary file
  FILE *dictFile;
  dictFile = fopen(DICTIONARY,"r");
  char dictWord[30];  // A temporary holder for a dictionary word
  int test = 0;       // Holds the returned status of fscanf
  // printf("Checking %s ... ", word);
  // Compare a string against every entry in the dictionary
  while(test != EOF){
    test = fscanf(dictFile,"%s",dictWord); //get a word from the dictionary, store in dictWord array
    //if decrypted word matches a word in the dictionary, increment that key's score
    if (strcasecmp(word,dictWord) == 0) { // strcasecmp (UNIX systems) ignores case
      // if (strcicmp(word,dictWord) == 0) { // an attempt at a portable scring-compare that ignores case
      fclose(dictFile);
      // printf("Found %s\n", dictWord);
      return 0; // match found
    }
  }
  fclose(dictFile);
  // printf("No match found in dictionary\n");
  return 1; // No match found
}

void crackRotation(void) {

  char text[2048], decipherText[2048], character;
  int scores[26];
  for(int i = 0; i < 26; i++) { //sets each array value to 0
    scores[i]=0;
  } // Array to hold number of real words found for each dectyption key. Initialise with zeros.

  // Prompt for cihpertext to decrypt. Store in array.
  printf("Enter cipher to crack: ");
  scanf(" %[^\n]s" , text);

  // Loop through all possible keys and count number of dictionary words found for each key
  for(int encryptionKey = 0; encryptionKey < 25; encryptionKey++) {
    // Step 1: Perform decryption with current key (offset)
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
    switch(state) {
      case STATE_CAESAR:
      caesar();
      break;

      case STATE_SUBST:
      substitution();
      break;

      case STATE_CRACK_SUBST:
      crackSubstitution();
      break;

      case STATE_CRACK_CAESAR:
      crackRotation();
      break;

      default: printf("Incorrect input, enter a number 1 - 4 to select a mode");

    }

  }


}
