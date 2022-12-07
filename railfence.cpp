#include <bits/stdc++.h>
using namespace std;
class RailFenceCipher
{
public:
    static string encrypt(string plaintext, int depth)
    {
        transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);

        vector<char> levels[depth];
        int curLevel = 0;
        int turn = 1;
        for (int i = 0; i < plaintext.length(); i++)
        {
            levels[curLevel].push_back(plaintext[i]);

            if (curLevel == depth - 1 && turn == 1)
            {
                turn = -1;
            }
            else if (curLevel == 0 && turn == -1)
            {
                turn = 1;
            }
            curLevel += turn;
        }
        string ciphertext;

        for (int i = 0; i < depth; i++)
        {
            for (char c : levels[i])
                ciphertext += c;
        }
        return ciphertext;
    }

    static string decrypt(string ciphertext, int depth)
    {
        int curLevel = 0;
        int turn = 1;
        vector<int> counts(depth, 0);

        for (int i = 0; i < ciphertext.length(); i++)
        {
            counts[curLevel]++;
            if (curLevel == depth - 1 && turn == 1)
            {
                turn = -1;
            }
            else if (curLevel == 0 && turn == -1)
            {
                turn = 1;
            }
            curLevel += turn;
        }

        vector<string> letters(depth);

        int start_index = 0;

        for (int i = 0; i < depth; i++)
        {
            int c = counts[i];
            letters[i] = ciphertext.substr(start_index, c);
            start_index += c;
        }

        string plaintext;

        fill(counts.begin(), counts.end(), 0);

        curLevel = 0;
        turn = 1;
        for (int i = 0; i < ciphertext.length(); i++)
        {
            plaintext += letters[curLevel][counts[curLevel]];
            counts[curLevel]++;

            if (curLevel == depth - 1 && turn == 1)
            {
                turn = -1;
            }
            else if (curLevel == 0 && turn == -1)
            {
                turn = 1;
            }
            curLevel += turn;
        }

        return plaintext;
    }
};

int main()
{
    string s;
    int depth;

    cout << "Enter plaintext: ";
    cin >> s;

    cout << "Enter depth: ";
    cin >> depth;

    string ciphertext = RailFenceCipher::encrypt(s, depth);

    cout << "Ciphertext : " << ciphertext << endl;

    cout << "Plaintext(Decrypted): " << RailFenceCipher::decrypt(ciphertext, depth) << '\n';

    return 0;
}