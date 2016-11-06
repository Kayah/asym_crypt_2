#ifndef H_UTILS
#define H_UTILS
#include <gmpxx.h>
#include <string>
unsigned long long getRandomPrimeNumber(unsigned char*(*bbs)());
unsigned char* bbs();
bool millerRabin(mpz_class p);
mpz_class getRandomInt(mpz_class p);
#endif
