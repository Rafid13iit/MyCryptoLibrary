#include <bits/stdc++.h>
using namespace std;

set<int> primes; // Collection of prime numbers
int public_key;  // Public key for encryption
int private_key; // Private key for decryption
int n;           // n = p * q, where p and q are prime numbers

// Function to fill the set of prime numbers using the Sieve of Eratosthenes
void fillPrimes() {
    vector<bool> sieve(250, true);
    sieve[0] = false;
    sieve[1] = false;

    for (int i = 2; i < 250; i++) {
        for (int j = i * 2; j < 250; j += i) {
            sieve[j] = false;
        }
    }

    for (int i = 0; i < sieve.size(); i++) {
        if (sieve[i])
            primes.insert(i);
    }
}

// Function to pick a random prime number and remove it from the set
int getRandomPrime() {
    int k = rand() % primes.size();
    auto it = primes.begin();
    while (k--) it++;
    int ret = *it;
    primes.erase(it);
    return ret;
}

// Function to set public and private keys for encryption and decryption
void setKeys() {
    int prime1 = getRandomPrime();
    int prime2 = getRandomPrime();
    n = prime1 * prime2;
    int phi = (prime1 - 1) * (prime2 - 1);

    int e = 2;
    while (1) {
        if (__gcd(e, phi) == 1) break;
        e++;
    }
    public_key = e;

    int d = 2;
    while (1) {
        if ((d * e) % phi == 1) break;
        d++;
    }
    private_key = d;
}

// Function to encrypt the given number using the public key
long long int encrypt(double message) {
    int e = public_key;
    long long int encrypted_text = 1;
    while (e--) {
        encrypted_text *= message;
        encrypted_text %= n;
    }
    return encrypted_text;
}

// Function to decrypt the given number using the private key
long long int decrypt(int encrypted_text) {
    int d = private_key;
    long long int decrypted = 1;
    while (d--) {
        decrypted *= encrypted_text;
        decrypted %= n;
    }
    return decrypted;
}

// Function to encode the message by encrypting each character
vector<int> encodeMessage(string message) {
    vector<int> encodedForm;
    for (auto& letter : message)
        encodedForm.push_back(encrypt((int)letter));
    return encodedForm;
}

// Function to decode the message by decrypting each encoded number
string decodeMessage(vector<int> encoded) {
    string decodedMessage;
    for (auto& num : encoded)
        decodedMessage += decrypt(num);
    return decodedMessage;
}

int main() {
    fillPrimes();
    setKeys();

    cout << "Enter the message: ";
    string message;
    getline(cin, message);

    vector<int> encodedMessage = encodeMessage(message);

    cout << "Initial message:\n" << message;
    cout << "\n\nThe encoded message (encrypted by public key):\n";
    for (auto& p : encodedMessage)
        cout << p;

    cout << "\n\nThe decoded message (decrypted by private key):\n";
    cout << decodeMessage(encodedMessage) << endl;

    return 0;
}
