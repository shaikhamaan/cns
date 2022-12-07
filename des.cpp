#include <algorithm>
#include <bitset>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

class DES
{
private:
  map<char, string> b = {
      {'0', "0000"}, {'1', "0001"}, {'2', "0010"}, {'3', "0011"}, {'4', "0100"}, {'5', "0101"}, {'6', "0110"}, {'7', "0111"}, {'8', "1000"}, {'9', "1001"}, {'A', "1010"}, {'B', "1011"}, {'C', "1100"}, {'D', "1101"}, {'E', "1110"}, {'F', "1111"}};

  string hexToBin(string &str)
  {
    string bin;

    for (char c : str)
      bin += b[c];

    return bin;
  }

  const vector<char> h = {'0', '1', '2', '3', '4', '5', '6', '7',
                          '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

  string binToHex(string &str)
  {
    stringstream ss(str);
    string hex;
    bitset<4> bits;

    while (ss >> bits)
    {
      int x = bits.to_ulong();
      hex += h[x];
    }

    return hex;
  }

  const vector<int> PC1_box = {57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34,
                               26, 18, 10, 2, 59, 51, 43, 35, 27, 19, 11, 3,
                               60, 52, 44, 36, 63, 55, 47, 39, 31, 23, 15, 7,
                               62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37,
                               29, 21, 13, 5, 28, 20, 12, 4};

  const vector<int> PC2_box = {14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
                               23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
                               41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
                               44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32};

  const vector<int> IP_box = {
      58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
      62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8,
      57, 49, 41, 33, 25, 17, 9, 1, 59, 51, 43, 35, 27, 19, 11, 3,
      61, 53, 45, 37, 29, 21, 13, 5, 63, 55, 47, 39, 31, 23, 15, 7};

  const vector<int> IP_1_box = {
      40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
      38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
      36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
      34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9, 49, 17, 57, 25};

  const vector<int> E_box = {32, 1, 2, 3, 4, 5, 4, 5, 6, 7, 8, 9,
                             8, 9, 10, 11, 12, 13, 12, 13, 14, 15, 16, 17,
                             16, 17, 18, 19, 20, 21, 20, 21, 22, 23, 24, 25,
                             24, 25, 26, 27, 28, 29, 28, 29, 30, 31, 32, 1};

  const vector<int> P_box = {16, 7, 20, 21, 29, 12, 28, 17, 1, 15, 23,
                             26, 5, 18, 31, 10, 2, 8, 24, 14, 32, 27,
                             3, 9, 19, 13, 30, 6, 22, 11, 4, 25};

  string permute(string &str, const vector<int> &table)
  {
    string p;

    for (int i : table)
      p += str[i - 1];

    return p;
  }

  vector<string> generateSubKeys(string &key)
  {
    string K = hexToBin(key);
    string K_ = permute(K, PC1_box);

    int shift[16] = {1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1};

    string C = K_.substr(0, 28);
    string D = K_.substr(28, 28);

    vector<string> subKeys;

    for (int i = 0; i < 16; i++)
    {
      rotate(C.begin(), C.begin() + shift[i], C.end());
      rotate(D.begin(), D.begin() + shift[i], D.end());

      string CD = C + D;
      subKeys.push_back(permute(CD, PC2_box));
    }

    return subKeys;
  }

  string XOR(string &a, string &b)
  {
    string c;
    int n = a.size();

    for (int i = 0; i < n; i++)
      c += '0' + ((a[i] - '0') ^ (b[i] - '0'));

    return c;
  }

  string xorHex(string &a, string &b)
  {
    string A = hexToBin(a);
    string B = hexToBin(b);
    string C;
    int n = A.size();

    for (int i = 0; i < n; i++)
      C += '0' + ((A[i] - '0') ^ (B[i] - '0'));

    return binToHex(C);
  }

  const int S_box[8][4][16] = {
      {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
       0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
       4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
       15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13},
      {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
       3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
       0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
       13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9},
      {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
       13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
       13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
       1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12},
      {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
       13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
       10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
       3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14},
      {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
       14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
       4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
       11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3},
      {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
       10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
       9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
       4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13},
      {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
       13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
       1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
       6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12},
      {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
       1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
       7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
       2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}};

  string f(string &R, string &K)
  {
    string E_R = permute(R, E_box);
    string K_E_R = XOR(K, E_R);

    string S;
    for (int i = 0; i < 8; i++)
    {
      string B = K_E_R.substr(i * 6, 6);

      int row = 2 * (B[0] - '0') + (B[5] - '0');
      int col =
          8 * (B[1] - '0') + 4 * (B[2] - '0') + 2 * (B[3] - '0') + (B[4] - '0');

      S += bitset<4>(S_box[i][row][col]).to_string();
    }

    return permute(S, P_box);
  }

  string encode(string &text, vector<string> &K)
  {
    string M = hexToBin(text);
    string IP = permute(M, IP_box);

    string L = IP.substr(0, 32);
    string R = IP.substr(32, 32);

    for (int i = 0; i < 16; i++)
    {
      string L_ = R;
      string f_R = f(R, K[i]);
      string R_ = XOR(L, f_R);

      L = L_;
      R = R_;
    }

    string RL = R + L;
    string P = permute(RL, IP_1_box);

    return binToHex(P);
  }

public:
  string encrypt(string &plaintext, string &key, int mode = 0)
  {
    vector<string> subKeys = generateSubKeys(key);

    int n = plaintext.size();
    if (n % 16 != 0)
    {
      int r = 16 - (n % 16);
      plaintext += string(r, '0');
      n += r;
    }

    string ciphertext;

    switch (mode)
    {
    case 0:
    { // ECB
      for (int i = 0; i < n; i += 16)
      {
        string P = plaintext.substr(i, 16);
        ciphertext += encode(P, subKeys);
      }
    }
    break;

    case 1:
    {                                // CBC
      string C = "606D8F39FB9AEDB5"; // initial value is IV

      for (int i = 0; i < n; i += 16)
      {
        string P = plaintext.substr(i, 16);
        string X = xorHex(P, C);
        C = encode(X, subKeys);
        ciphertext += C;
      }
    }
    break;
    }

    return ciphertext;
  }

  string decrypt(string &ciphertext, string &key, int mode = 0)
  {
    vector<string> subKeys = generateSubKeys(key);
    reverse(subKeys.begin(), subKeys.end());

    int n = ciphertext.size();
    string plaintext;

    switch (mode)
    {
    case 0:
    { // ECB
      for (int i = 0; i < n; i += 16)
      {
        string C = ciphertext.substr(i, 16);
        plaintext += encode(C, subKeys);
      }
    }
    break;

    case 1:
    {                                // CBC
      string T = "606D8F39FB9AEDB5"; // initial values is IV

      for (int i = 0; i < n; i += 16)
      {
        string C = ciphertext.substr(i, 16);
        string X = encode(C, subKeys);
        plaintext += xorHex(X, T);
        T = C;
      }
    }
    break;
    }

    return plaintext;
  }
};

int main()
{
  cout << "DES:\n\n";

  cout << "Enter plaintext (hex digits - uppercase): ";
  string plaintext;
  cin >> plaintext;
  plaintext.erase(remove_if(plaintext.begin(), plaintext.end(), ::isspace),
                  plaintext.end());

  cout << "Enter key (16 hex digits - uppercase): ";
  string key;
  cin >> key;

  DES des;
  string ciphertext = des.encrypt(plaintext, key);

  cout << "Plaintext:  " << plaintext << "\n"
       << "Ciphertext: " << ciphertext << "\n";

  cout << "Enter ciphertext (hex digits - uppercase): ";
  ciphertext;
  cin >> ciphertext;

  cout << "Enter key (16 hex digits - uppercase): ";
  key;
  cin >> key;

  plaintext = des.decrypt(ciphertext, key);

  cout << "Ciphertext: " << ciphertext << "\n"
       << "Plaintext:  " << plaintext << "\n";

  return 0;
}
