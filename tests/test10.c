#include "testheader.h"
unsigned primes[MAXN], n = 3;
int add_prime(unsigned num){
        int i;
        for (i = 2; i < MAXN; ++i){
                if (primes[i] * primes[i] > num){
                        primes[n++] = num;
                        return 1;
                }
                if (num % primes[i] == 0) {
                    break;
                }
        }
        return 0;
}
int main()
{
    unsigned i = 0;
    primes[0] = 2;
    primes[1] = 3;
    primes[2] = 5;
    while (n < MAXN){
            while (1){
                    i += 6;
                    if (add_prime(i + 1) + add_prime(i + 5)) break;
            }
    }


    for (i = 0; i < n; i++) {
        sys_putint(primes[i]);
    }
    return 0;
}