#include <bits/stdc++.h>
using namespace std;

class Vigenere
{
public:
    static string encrypt(string plainText, string key)
    {
        string modKey;
        string cipherText = "";
        int keyLen = key.length();
        int l = 0;

        for (int i = 0; i < plainText.length(); ++i)
        {
            modKey += key[l];
            l++;
            l %= keyLen;
        }
        // cout << modKey << endl;

        map<char, int> indexOf;
        map<int, char> indexOfInverse;
        char ch = 'A';
        for (int i = 0; i < 26; i++)
        {
            indexOf[ch + i] = i;
            indexOfInverse[i] = ch + i;
        }

        for (int i = 0; i < plainText.length(); ++i)
        {
            cipherText += indexOfInverse[(indexOf[plainText[i]] + indexOf[modKey[i]]) % 26];
        }

        return cipherText;
    }
    static string decrypt(string cipherText, string key)
    {
        string plainText = "";
        string modKey;
        int keyLen = key.length();
        int l = 0;

        for (int i = 0; i < cipherText.length(); ++i)
        {
            modKey += key[l];
            l++;
            l %= keyLen;
        }
        // cout << modKey << endl;

        map<char, int> indexOf;
        map<int, char> indexOfInverse;
        char ch = 'A';
        for (int i = 0; i < 26; ++i)
        {
            indexOf[ch + i] = i;
            indexOfInverse[i] = ch + i;
        }

        for (int i = 0; i < cipherText.length(); ++i)
        {
            plainText += indexOfInverse[(indexOf[cipherText[i]] - indexOf[modKey[i]] + 26) % 26];
        }
        return plainText;
    }
};

int main()
{
    string plainText;
    string key;

    cout << "Enter Plaintext: ";
    cin >> plainText;

    cout << "Enter Key: ";
    cin >> key;
    cout << endl;

    string cipherText = Vigenere::encrypt(plainText, key);

    cout << "Plaintext: " << plainText << endl;
    cout << "Key: " << key << endl;

    cout << "Encrypted Data: " << cipherText << endl;
    cout << "Decrypted Data: " << Vigenere::decrypt(cipherText, key) << endl;
    return 0;
}