#include <bits/stdc++.h>
using namespace std;

class CaesarCipher
{
public:
    // C = P + K
    static string encrypt(const string &plaintext, int key)
    {
        string ciphertext;

        for (char c : plaintext)
        {
            if (!('a' <= c && c <= 'z'))
                continue;

            ciphertext += ('A' + (c - 'a' + key) % 26);
        }

        return ciphertext;
    }

    // C = P - K
    static string decrypt(const string &ciphertext, int key)
    {
        string plaintext;

        for (char c : ciphertext)
            plaintext += ('a' + (c - 'A' + 26 - key) % 26);

        return plaintext;
    }
};

int main()
{
    cout << "<------Caeser Cipher------>\n";

    cout
        << "Enter plaintext (lowercase): ";
    string plaintext;
    cin >> plaintext;
    cout << "Enter key: ";
    int key;
    cin >> key;
    key = key > 26 ? key % 26 : key;

    string ciphertext = CaesarCipher::encrypt(plaintext, key);
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::tolower);

    cout
        << "Plaintext:  " << plaintext << "\n"
        << "Ciphertext: " << ciphertext << "\n";
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);

    plaintext = CaesarCipher::decrypt(ciphertext, key);

    cout
        << "Plaintext:  " << plaintext << "\n";

    return 0;
}
