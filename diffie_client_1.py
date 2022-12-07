import asyncio
import websockets
import json


X = 0

# power calculation using binary exponentiation with modulo arithmetic


def power(x, y, p):
    res = 1     # Initialize result

    x = x % p

    if (x == 0):
        return 0

    while (y > 0):

        # If y is odd, multiply
        # x with result
        if ((y & 1) == 1):
            res = (res * x) % p

        # y must be even now
        y = y >> 1      # y = y/2
        x = (x * x) % p

    return res


def getPrimitiveRoots(q):
    roots = []

    for i in range(2, q):
        mods = set()
        for j in range(1, q):
            val = power(i, j, q)
            if val in mods:
                break
            mods.add(val)
        if (len(mods) == q - 1):
            roots.append(i)
    return roots

# getting list of all primitive roots for the prime for easy selection for user


def suggestRoots(q):
    roots = getPrimitiveRoots(q)

    print("These are the primitive roots for given prime (select any one)")
    print(roots)


def calculatePublicKey(X, alpha, q):
    Y = power(alpha, X, q)
    return Y


def calculateKey(Y, q):
    print(X)
    K = power(Y, X, q)
    return K

# User inputs for q,aplha and private key


def sendKey():
    print("Client Connected.....Starting the key exchange")
    print("Select The Prime Number q: ")
    q = (int)(input())

    print("Calculating the primitive roots (This may take some minutes...)")
    suggestRoots(q)
    alpha = (int)(input())

    print("Select Private Key [X] (<q): ")

    global X
    X = (int)(input())

    y = calculatePublicKey(X, alpha, q)

    print("Your Public Key[Y]: ", y)

    print("Sendint the Data to Client........")

    return {'y': y, 'alpha': alpha, 'q': q}


# sending key to other client which has the websocket server running at its port
async def keySender():
    dataToSend = sendKey()
    async with websockets.connect("ws://localhost:5000", ping_interval=None) as websocket:
        await websocket.send(json.dumps(dataToSend))

        response = await websocket.recv()

        print(response)

        data = json.loads(response)

        Y = data["y"]
        q = data["q"]

        print(f'Received Data: q = {q} Y = {Y}')

        K = calculateKey(Y, q)

        print("Key Calculated at Original sender: ", K)

        print("DONE!!")


# receive key from other program - handled using starting websocket server
async def keyReceiver(websocket):
    async for message in websocket:
        print(message)
        data = json.loads(message)
        Y = data["y"]
        alpha = data["alpha"]
        q = data["q"]
        print(f'Received Data: alpha = {alpha}, q = {q}, Y = {Y}')

        print("Enter Your Private Key [X] (<q): ")

        global X
        X = (int)(input())

        Y_ = calculatePublicKey(X, alpha, q)

        print("Your Public Key[Y]: ", Y_)

        K = calculateKey(Y, q)

        print("Key Calculated: ", K)

        print("Sending Public key for verification")

        await websocket.send(json.dumps({'y': Y_, 'q': q}))


async def startServer():
    async with websockets.serve(keyReceiver, "localhost", 5000):
        await asyncio.Future()


if __name__ == '__main__':
    mode = 0

    print("Select The Mode: (0 for send 1 for receive) ")

    mode = (int)(input())

    if (mode == 1):
        asyncio.run(startServer())
    else:
        asyncio.run(keySender())
