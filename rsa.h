#ifndef RSA_H
#define RSA_H
#include <gmpxx.h>

struct Public_key
{
    mpz_class
	    e,
	    n;
};

struct Private_key
{
    mpz_class
            d,
            n,
            p,
            q;
};

struct KeyPair
{
    Public_key public_key;
    Private_key private_key;
};

struct SignedMessage
{
    mpz_class message = 0;
    mpz_class signature = 0;
};


KeyPair  GenerateKeyPair(mpz_class,mpz_class);
mpz_class Encrypt(mpz_class, Public_key);
mpz_class Decrypt(mpz_class, Private_key);
SignedMessage Sign(mpz_class, Private_key);
bool Verify(SignedMessage , Public_key);
SignedMessage Sendkey(Public_key, Private_key, Public_key, mpz_class);
mpz_class RecieveKey(Public_key, Public_key, Private_key, SignedMessage);

#endif
