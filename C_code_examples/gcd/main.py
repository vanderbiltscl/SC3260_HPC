import gcd
import sys
import time

if __name__ == '__main__':
    start_time = time.time()
    n = int(sys.argv[1])

    cnt = 0
    for i in range(1, n):
        for j in range(1, n):
            if gcd.find_gcd(i, j)==1:
                cnt += 1

    print("Execution time %s s to find %d coprime numbers" % (
        time.time() - start_time, cnt))
