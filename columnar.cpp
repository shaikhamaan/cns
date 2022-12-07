#include <bits/stdc++.h>
using namespace std;

class Columnar
{
private:
    static vector<int> colSequence(const vector<int> &key)
    {
        vector<pair<int, int>> v;
        int n = key.size();

        for (int i = 0; i < n; i++)
            v.push_back({key[i], i});

        sort(v.begin(), v.end());

        vector<int> seq;
        for (pair<int, int> p : v)
            seq.push_back(p.second);

        return seq;
    }

public:
    static string encrypt(const string &plaintext, const vector<int> &key)
    {
        int n = key.size();
        int m = ceil((float)plaintext.size() / n);

        vector<string> mat(m, string(n, 'X'));

        int i = 0, j = 0;
        for (char c : plaintext)
        {
            mat[i][j] = toupper(c);

            j++;
            if (j == n)
            {
                i++;
                j = 0;
            }
        }
        // padding

        string ciphertext;

        for (int j : colSequence(key))
        {
            for (int i = 0; i < m; i++)
                ciphertext += mat[i][j];
        }

        return ciphertext;
    }

    static string decrypt(const string &ciphertext, const vector<int> &key)
    {
        int n = key.size();
        int m = ceil((float)ciphertext.size() / n);

        vector<string> mat(m, string(n, '_'));

        int k = 0;
        for (int j : colSequence(key))
        {
            for (int i = 0; i < m; i++)
                mat[i][j] = tolower(ciphertext[k++]);
        }

        string plaintext;

        for (string &row : mat)
            plaintext += row;

        return plaintext;
    }
};

vector<int> getKey(const string &tempKey)
{
    stringstream ss(tempKey);
    vector<int> key;
    int k;

    while (ss >> k)
        key.push_back(k);

    return key;
}

int main()
{
    cout << "Columnar Cipher:\n\n"
         << "Enter your choice:\n"
         << "1. Encrypt\n"
         << "2. Decrypt\n"
         << "> ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "Enter plaintext (lowercase): ";
        string plaintext;
        getline(cin, plaintext); // input buffer flushing
        getline(cin, plaintext);
        plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace),
                        plaintext.end());

        cout << "Enter key (space separated integers 1 to numOfCols in random "
                "order): ";
        string tempKey;
        getline(cin, tempKey);
        vector<int> key = getKey(tempKey);

        string ciphertext = Columnar::encrypt(plaintext, key);

        cout << "Plaintext:  " << plaintext << "\n"
             << "Ciphertext: " << ciphertext << "\n";
    }
    break;

    case 2:
    {
        cout << "Enter ciphertext (uppercase without spaces): ";
        string ciphertext;
        cin >> ciphertext;

        cout << "Enter key (space separated integers 1 to numOfCols in random "
                "order): ";
        string tempKey;
        getline(cin, tempKey); // input buffer flushing
        getline(cin, tempKey);
        vector<int> key = getKey(tempKey);

        string plaintext = Columnar::decrypt(ciphertext, key);

        cout << "Ciphertext: " << ciphertext << "\n"
             << "Plaintext:  " << plaintext << "\n";
    }
    break;

    default:
        cout << "Invalid choice!!\n";
        break;
    }

    return 0;
}
