
P = 1


def getGcd(a,b):
    r1 = 0
    r2 = 0

    r1 = a
    r2 = b

    while(r2 > 0):
        q = r1 // r2;
        r = r1 - q * r2
        r1 = r2
        r2 = r
    return r1


def findValues(m):
    return P // m

def getInverse(a,n):
    if getGcd(a,n) != 1:
        return 0
    r1 = n
    r2 = a

    t1 = 0
    t2 = 1

    while r2 > 0:
        q = r1 // r2;
        r = r1 - q * r2
        t = t1 - q * t2

        r1 = r2
        r2 = r

        t1 = t2
        t2 = t
    
    return t1


print("Enter the Number of equations: (N) : ")

n = (int)(input())

print("Enter values a1,a2,---,an (space separated): ")
a = list(map(int,input().split()))


print("Enter values m1,m2,---,mn (space separated): ")
m = list(map(int,input().split()))



for i in range(n):
    P *= m[i]


# geeting M1,M2,..., Mn values
M = list(map(findValues,m))

for i in M:
    print(i)

# getting inverse of each others
M_ = list(map(getInverse,M,m))


ans = 0

for i in range(n):
    ans = (ans + a[i] * M[i] * M_[i]) % P

print(f'Answer: {ans}')
