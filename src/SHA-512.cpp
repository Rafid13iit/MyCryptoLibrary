#include <bits/stdc++.h>
#include <bitset>
#include <sstream>
using namespace std;

// Define an unsigned 64-bit integer type for convenience
typedef unsigned long long int uint64;

// Array to store the message blocks
uint64 Message[80];

// Constants for SHA-512 algorithm
const uint64 Constants[80]
	= { 0x428a2f98d728ae22, 0x7137449123ef65cd,
		0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
		0x3956c25bf348b538, 0x59f111f1b605d019,
		0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
		0xd807aa98a3030242, 0x12835b0145706fbe,
		0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
		0x72be5d74f27b896f, 0x80deb1fe3b1696b1,
		0x9bdc06a725c71235, 0xc19bf174cf692694,
		0xe49b69c19ef14ad2, 0xefbe4786384f25e3,
		0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
		0x2de92c6f592b0275, 0x4a7484aa6ea6e483,
		0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
		0x983e5152ee66dfab, 0xa831c66d2db43210,
		0xb00327c898fb213f, 0xbf597fc7beef0ee4,
		0xc6e00bf33da88fc2, 0xd5a79147930aa725,
		0x06ca6351e003826f, 0x142929670a0e6e70,
		0x27b70a8546d22ffc, 0x2e1b21385c26c926,
		0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
		0x650a73548baf63de, 0x766a0abb3c77b2a8,
		0x81c2c92e47edaee6, 0x92722c851482353b,
		0xa2bfe8a14cf10364, 0xa81a664bbc423001,
		0xc24b8b70d0f89791, 0xc76c51a30654be30,
		0xd192e819d6ef5218, 0xd69906245565a910,
		0xf40e35855771202a, 0x106aa07032bbd1b8,
		0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
		0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
		0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb,
		0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
		0x748f82ee5defb2fc, 0x78a5636f43172f60,
		0x84c87814a1f0ab72, 0x8cc702081a6439ec,
		0x90befffa23631e28, 0xa4506cebde82bde9,
		0xbef9a3f7b2c67915, 0xc67178f2e372532b,
		0xca273eceea26619c, 0xd186b8c721c0c207,
		0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
		0x06f067aa72176fba, 0x0a637dc5a2c898a6,
		0x113f9804bef90dae, 0x1b710b35131c471b,
		0x28db77f523047d84, 0x32caab7b40c72493,
		0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
		0x4cc5d4becb3e42b6, 0x597f299cfc657e2a,
		0x5fcb6fab3ad6faec, 0x6c44198c4a475817 };


// Function to convert a 4-bit binary to its hexadecimal representation
    // Binary to hexadecimal mapping
string getHexFromBinary(const string& binary) {
    if (binary == "0000") return "0";
    if (binary == "0001") return "1";
    if (binary == "0010") return "2";
    if (binary == "0011") return "3";
    if (binary == "0100") return "4";
    if (binary == "0101") return "5";
    if (binary == "0110") return "6";
    if (binary == "0111") return "7";
    if (binary == "1000") return "8";
    if (binary == "1001") return "9";
    if (binary == "1010") return "a";
    if (binary == "1011") return "b";
    if (binary == "1100") return "c";
    if (binary == "1101") return "d";
    if (binary == "1110") return "e";
    if (binary == "1111") return "f";
    return "";
}

// Function to convert a decimal number to its hexadecimal representation
string decimalToHex(uint64 decimal) {
    string binaryString = bitset<64>(decimal).to_string();
    string hexString = "";

    // Convert 64-bit binary to hexadecimal in 4-bit chunks
    for (size_t i = 0; i < binaryString.length(); i += 4) {
        hexString += getHexFromBinary(binaryString.substr(i, 4));
    }

    return hexString;
}

// Function to convert binary string to decimal
uint64 binaryToDecimal(const string& binary) {
    return bitset<64>(binary).to_ullong();
}

// Function to perform bitwise right rotation
uint64 rotateRight(uint64 x, int n) {
    return (x >> n) | (x << (64 - n));
}

// Function to perform bitwise right shift
uint64 shiftRight(uint64 x, int n) {
    return (x >> n);
}

// Function to separate the input block into message blocks
void separateBlocks(const string& inputBlock) {
    int chunkNum = 0;

    // Convert 1024-bit input block to 64-bit message blocks
    for (size_t i = 0; i < inputBlock.length(); i += 64, ++chunkNum) {
        Message[chunkNum] = binaryToDecimal(inputBlock.substr(i, 64));
    }

    // Generate additional message blocks
    for (int g = 16; g < 80; ++g) {
        uint64 wordA = rotateRight(Message[g - 2], 19) ^ rotateRight(Message[g - 2], 61) ^ shiftRight(Message[g - 2], 6);
        uint64 wordB = Message[g - 7];
        uint64 wordC = rotateRight(Message[g - 15], 1) ^ rotateRight(Message[g - 15], 8) ^ shiftRight(Message[g - 15], 7);
        uint64 wordD = Message[g - 16];

        Message[g] = wordA + wordB + wordC + wordD;
    }
}

// Functions for SHA-512 operations
uint64 maj(uint64 a, uint64 b, uint64 c) {
    return (a & b) ^ (b & c) ^ (c & a);
}

uint64 ch(uint64 e, uint64 f, uint64 g) {
    return (e & f) ^ (~e & g);
}

uint64 sigmaE(uint64 e) {
    return rotateRight(e, 14) ^ rotateRight(e, 18) ^ rotateRight(e, 41);
}

uint64 sigmaA(uint64 a) {
    return rotateRight(a, 28) ^ rotateRight(a, 34) ^ rotateRight(a, 39);
}

// Function to perform the hash computation
void hashFunction(uint64 a, uint64 b, uint64 c, uint64& d, uint64 e, uint64 f, uint64 g, uint64& h, int k) {
    uint64 t1 = h + ch(e, f, g) + sigmaE(e) + Message[k] + Constants[k];
    uint64 t2 = sigmaA(a) + maj(a, b, c);

    d = d + t1;
    h = t1 + t2;
}

// Function to calculate SHA-512 hash
string sha512(const string& input) {
    // Initial hash values
    uint64 a = 0x6a09e667f3bcc908;
    uint64 b = 0xbb67ae8584caa73b;
    uint64 c = 0x3c6ef372fe94f82b;
    uint64 d = 0xa54ff53a5f1d36f1;
    uint64 e = 0x510e527fade682d1;
    uint64 f = 0x9b05688c2b3e6c1f;
    uint64 g = 0x1f83d9abfb41bd6b;
    uint64 h = 0x5be0cd19137e2179;

    // Prepare the input block
    stringstream fixedStream;
    for (char ch : input) {
        fixedStream << bitset<8>(ch);
    }

    // Obtain the 1024-bit input block
    string s1024 = fixedStream.str();
    int originalLen = s1024.length();
    int toBeAdded;

    // Padding the input block
    int modded = s1024.length() % 1024;
    if (1024 - modded >= 128) {
        toBeAdded = 1024 - modded;
    } else {
        toBeAdded = 2048 - modded;
    }

    s1024 += "1";
    for (int y = 0; y < toBeAdded - 129; y++) {
        s1024 += "0";
    }

    // Append the original length in binary to the padded block
    string lengthBits = bitset<128>(originalLen).to_string();
    s1024 += lengthBits;

    // Break the 1024-bit block into 512-bit blocks
    int blocksNumber = s1024.length() / 1024;
    int chunkNum = 0;
    string blocks[blocksNumber];
    for (int i = 0; i < s1024.length(); i += 1024, ++chunkNum) {
        blocks[chunkNum] = s1024.substr(i, 1024);
    }

    // Process each block
    for (int letsgo = 0; letsgo < blocksNumber; ++letsgo) {
        separateBlocks(blocks[letsgo]);

        // Backup original hash values
        uint64 aa = a, bb = b, cc = c, dd = d, ee = e, ff = f, gg = g, hh = h;
        int count = 0;

        // Perform hash computations for 80 rounds
        for (int i = 0; i < 10; i++) {
            hashFunction(a, b, c, d, e, f, g, h, count);
            count++;
            hashFunction(h, a, b, c, d, e, f, g, count);
            count++;
            hashFunction(g, h, a, b, c, d, e, f, count);
            count++;
            hashFunction(f, g, h, a, b, c, d, e, count);
            count++;
            hashFunction(e, f, g, h, a, b, c, d, count);
            count++;
            hashFunction(d, e, f, g, h, a, b, c, count);
            count++;
            hashFunction(c, d, e, f, g, h, a, b, count);
            count++;
            hashFunction(b, c, d, e, f, g, h, a, count);
            count++;
        }

        // Update hash values
        a += aa;
        b += bb;
        c += cc;
        d += dd;
        e += ee;
        f += ff;
        g += gg;
        h += hh;
    }

    // Concatenate the final hash values
    stringstream output;
    output << decimalToHex(a) << decimalToHex(b) << decimalToHex(c) << decimalToHex(d)
           << decimalToHex(e) << decimalToHex(f) << decimalToHex(g) << decimalToHex(h);

    return output.str();
}

int main() {
    // User Input
    cout << "Enter a string: ";
    string userInput;
    getline(cin, userInput);

    // Function Call
    cout << "SHA-512 Hash: " << sha512(userInput) << endl;

    return 0;
}
