#include <bits/stdc++.h>
using namespace std;

void file()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
}

// Function for extended Euclidean Algorithm
int ansS, ansT;
int findGcdExtended(int r1, int r2, int s1, int s2, int t1, int t2)
{
    // Base Case
    if (r2 == 0)
    {
        ansS = s1;
        ansT = t1;
        return r1;
    }

    int q = r1 / r2;
    int r = r1 % r2;

    int s = s1 - q * s2;
    int t = t1 - q * t2;

    cout << q << " " << r1 << " " << r2 << " " << r << " " << s1 << " " << s2 << " " << s << " " << t1 << " " << t2 << " " << t << endl;

    return findGcdExtended(r2, r, s2, s, t2, t);
}

int modInverse(int A, int M)
{
    int x, y;
    int g = findGcdExtended(A, M, 1, 0, 0, 1);
    if (g != 1)
    {
        cout << "Inverse doesn't exist";
        return 0;
    }
    else
    {

        // m is added to handle negative x

        int res = (ansS % M + M) % M;
        cout << "inverse is" << res << endl;
        return res;
    }
}

long long powM(long long a, long long b, long long n)
{
    if (b == 1)
        return a % n;
    long long x = powM(a, b / 2, n);
    x = (x * x) % n;
    if (b % 2)
        x = (x * a) % n;
    return x;
}

int findGCD(int num1, int num2)
{
    if (num1 == 0)
        return num2;
    return findGCD(num2 % num1, num1);
}

// Code to demonstrate RSA algorithm
int main()
{
    file();

    // Two random prime numbers
    long long p, q, e;
    string ms;
    // 17 31 7 2

    cout << "Please enter 2 prime number and e and Message to Encript" << endl;
    cin >> p >> q >> e >> ms;

    cout << "2 random prime numbers selected are " << p << " " << q << endl;

    // First part of public key:
    long long n = p * q;
    cout << "Product of two prime number n is " << n << endl;

    // Finding other part of public key.
    // e stands for encrypt

    cout << "Taken e is " << e << endl;

    long long phi = (p - 1) * (q - 1);
    cout << "phi is " << phi << endl;

    while (e < phi)
    {
        // e must be co-prime to phi and
        // smaller than phi.
        if (findGCD(e, phi) == 1)
            break;
        else
            e++;
    }

    cout << "Final e value is " << e << endl;

    // Private key (d stands for decrypt)

    long long d = modInverse(e, phi);
    cout << "d is " << d << endl;

    cout << "\nso now our publissc key is "
         << "<" << e << "," << n << ">" << endl;
    cout << "\nso now our private key is "
         << "<" << d << "," << n << ">" << endl
         << endl;

    // Message to be encrypted

    cout << "Message date is " << ms << endl;

    // Encryption c = (msg ^ e) % n

    string enc = "";

    for (auto it : ms)
    {
        int val = it - 'a' + 1;
        long long c = powM(val, e, n);
        // cout << val << " " << c << endl;
        enc += to_string(c);
        enc += ',';
    }

    cout << "\nencripted Message is " << enc << endl
         << endl;
    int val = 0;
    string dec = "";
    for (auto it : enc)
    {

        if (it == ',')
        {

            long long m = powM(val, d, n);
            // cout << val << " " << m << endl;
            dec += ('a' + m - 1);
            val = 0;
            continue;
        }
        val *= 10;
        val += (it - '0');
    }

    cout << "Message after decription is " << dec;

    //  c = powM(msg, e, n);
    // cout << "Encripted Message is " << c << endl;

    // // Decryption m = (c ^ d) % n
    // long long m = powM(c, d, n);
    // cout << "original Message is " << m << endl;

    return 0;
}