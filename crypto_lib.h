#ifndef CRYPTO_LIB_H
#define CRYPTO_LIB_H

#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long int uint64;
typedef long long int lli;

// AES functions
void AES();
void KeyExpansionCore(unsigned char * in, unsigned char i);
void KeyExpansion(unsigned char inputKey[16], unsigned char expandedKeys[176]);
void AddRoundKey(unsigned char * state, unsigned char * roundKey);
void SubRoundKey(unsigned char * state, unsigned char * roundKey);
void SubBytes(unsigned char * state);
void ShiftRows(unsigned char * state);
void invShiftRows(unsigned char * state);
void invSubBytes(unsigned char * state);
void MixColumns(unsigned char * state);
void InverseMixColumns(unsigned char * state);
void Round(unsigned char * state, unsigned char * key);
void FinalRound(unsigned char * state, unsigned char * key);
void invRound(unsigned char * state, unsigned char * key);
void InitialRound(unsigned char * state, unsigned char * key);
void AESEncrypt(unsigned char * message, unsigned char * expandedKey, unsigned char * encryptedMessage);
void AESDecrypt(unsigned char * encryptedMessage, unsigned char * expandedKey, unsigned char * decryptedMessage);


// SHA-512 function
void SHA512();
string getHexFromBinary(const string& binary);
string decimalToHex(uint64 decimal);
uint64 binaryToDecimal(const string& binary);
uint64 rotateRight(uint64 x, int n);
uint64 shiftRight(uint64 x, int n);
void separateBlocks(const string& inputBlock);
uint64 maj(uint64 a, uint64 b, uint64 c);
uint64 ch(uint64 e, uint64 f, uint64 g);
uint64 sigmaE(uint64 e);
uint64 sigmaA(uint64 a);
void hashFunction(uint64 a, uint64 b, uint64 c, uint64& d, uint64 e, uint64 f, uint64 g, uint64& h, int k);
string sha512(const string& input);


// RSA functions
void RSA();
void fillPrimes();
int getRandomPrime();
void setKeys();
lli encrypt(double message);
lli decrypt(int encrypted_text);
vector<int> encodeMessage(string message);
string decodeMessage(vector<int> encoded);


#endif // CRYPTO_LIB_H
