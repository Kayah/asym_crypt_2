#ifndef H_UTILS
#define H_UTILS
#include <gmpxx.h>
unsigned long long getRandomPrimeNumber(char*(*bbs)());
char * bbs();
mpz_class millerRabin(mpz_class p);
mpz_class getRandomInt(mpz_class p);
#endif