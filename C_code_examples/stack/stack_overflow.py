import sys

def recursive_mul(n, value):
    if value == 0:
        return 0
    return n + recursive_mul(n, value-1)

if __name__ == '__main__':
    n = int(sys.argv[1])
    value = int(sys.argv[2])
    print("%f" %(recursive_mul(n, value)))

