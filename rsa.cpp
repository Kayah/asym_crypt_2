/*
compile via g++ <ProjectName.cpp> -o <ProjectName> -std=c++11 -lgmpxx -lgmp -lm
*/
#ifndef RSA_CPP
#define RSA_CPP

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

KeyPair  GenerateKeyPair(mpz_class p, mpz_class q)
{
    KeyPair key_pair;
    mpz_class
//            p ("25B0C52E797C3AADFC5F0938972B87A465D9E5373EB530362BA0A21084A1E7A5", 16),
//            q ("EDD3D25D544D30A6BC0714B50DF4C3427959C5066136F69218335EAFF2C0220C3F", 16 ),
            p_, q_,
            n,
            phi, phi_,
            e ("10001", 16), d;
    mpz_sub_ui(p_.get_mpz_t(), p.get_mpz_t(), 1);
    mpz_sub_ui(q_.get_mpz_t(), q.get_mpz_t(), 1);
    mpz_mul(n.get_mpz_t(), p.get_mpz_t(), q.get_mpz_t());
    mpz_mul(phi.get_mpz_t(), p_.get_mpz_t(), q_.get_mpz_t());
    mpz_sub_ui(phi_.get_mpz_t(), phi.get_mpz_t(), 1);
    mpz_invert(d.get_mpz_t(), e.get_mpz_t(), phi.get_mpz_t());
    key_pair.public_key.e = e;
    key_pair.public_key.n = n;
    key_pair.private_key.d = d;
    key_pair.private_key.n = n;
    key_pair.private_key.p = p;
    key_pair.private_key.q = q;
    gmp_printf("p = %ZX\n", p.get_mpz_t());
    gmp_printf("q = %ZX\n", q.get_mpz_t());
    gmp_printf("n = %ZX\n", n.get_mpz_t());
    gmp_printf("phi = %ZX\n", phi.get_mpz_t());
    gmp_printf("e = %ZX\n", e.get_mpz_t());
    gmp_printf("d = %ZX\n", d.get_mpz_t());
    return key_pair;
}

mpz_class Encrypt(mpz_class M, Public_key public_key)
{
//    if (mpz_sgn(M.get_mpz_t()) != 1
//        || mpz_cmp(M.get_mpz_t(), public_key.n.get_mpz_t()) >= 0)
//        return mpz_class(0);
    mpz_class
            e (public_key.e),
            n (public_key.n),
            C;
    mpz_powm(C.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
    gmp_printf("C = %ZX\n", C.get_mpz_t());
    return C;
}

mpz_class Decrypt(mpz_class C, Private_key private_key)
{
    mpz_class
            d (private_key.d),
            n (private_key.n),
            M;
    mpz_powm(M.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
    gmp_printf("M = %ZX\n", M.get_mpz_t());
    return M;
}

SignedMessage Sign(mpz_class M, Private_key private_key)
{
    SignedMessage signed_message;
    mpz_class
            d (private_key.d),
            n (private_key.n),
            S;
    mpz_powm(S.get_mpz_t(), M.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
    gmp_printf("S = %ZX\n", S.get_mpz_t());
    signed_message.message = M;
    signed_message.signature = S;
    return signed_message;
}

bool Verify(SignedMessage signed_message, Public_key public_key)
{
    mpz_class
            e (public_key.e),
            n (public_key.n),
            M;
    mpz_powm(M.get_mpz_t(), signed_message.signature.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
    if (mpz_cmp(M.get_mpz_t(), signed_message.message.get_mpz_t()) == 0)
    {
        printf("Signature verified.\n");
        return true;
    }
    else
    {
        printf("Signature verification failed.\n");
        return false;
    }
}

SignedMessage Sendkey(Public_key public_key_A, Private_key private_key_A, Public_key public_key_B, mpz_class k)
{
    SignedMessage signed_message;
    if (mpz_cmp(public_key_A.n.get_mpz_t(), public_key_B.n.get_mpz_t()) > 0)
    {
        printf("Inappropriate public key, please generate another one.\n");
        return signed_message;
    }
    mpz_class
            k_shared,
            S,
            S_shared;
    mpz_powm(k_shared.get_mpz_t(), k.get_mpz_t(), public_key_B.e.get_mpz_t(), public_key_B.n.get_mpz_t());
    mpz_powm(S.get_mpz_t(), k.get_mpz_t(), private_key_A.d.get_mpz_t(), public_key_A.n.get_mpz_t());
    mpz_powm(S_shared.get_mpz_t(), S.get_mpz_t(), public_key_B.e.get_mpz_t(), public_key_B.n.get_mpz_t());
    signed_message.message = k_shared;
    signed_message.signature = S_shared;
    gmp_printf("K' = %ZX\n", k_shared.get_mpz_t());
    gmp_printf("k = %ZX\n", k.get_mpz_t());
    gmp_printf("e' = %ZX\n", public_key_B.e.get_mpz_t());
    gmp_printf("e = %ZX\n", public_key_A.e.get_mpz_t());
    gmp_printf("n' = %ZX\n", public_key_B.n.get_mpz_t());
    gmp_printf("n = %ZX\n", public_key_A.n.get_mpz_t());
    gmp_printf("S = %ZX\n", S.get_mpz_t());
    gmp_printf("S' = %ZX\n", S_shared.get_mpz_t());
    return signed_message;
}

mpz_class RecieveKey(Public_key public_key_A, Public_key public_key_B, Private_key private_key_B, SignedMessage signed_message)
{
    mpz_class
            k_shared, k,
            S;
    if (mpz_cmp(public_key_B.n.get_mpz_t(), public_key_A.n.get_mpz_t()) < 0)
    {
        printf("Inappropriate public key, please generate another one.\n");
        return mpz_class("0");
    }
    mpz_powm(k.get_mpz_t(), signed_message.message.get_mpz_t(), private_key_B.d.get_mpz_t(), public_key_B.n.get_mpz_t());
    mpz_powm(S.get_mpz_t(), signed_message.signature.get_mpz_t(), private_key_B.d.get_mpz_t(), public_key_B.n.get_mpz_t());
    mpz_powm(k_shared.get_mpz_t(), S.get_mpz_t(), public_key_A.e.get_mpz_t(), public_key_A.n.get_mpz_t());
    gmp_printf("k = %ZX\n", k.get_mpz_t());
    gmp_printf("k_shared = %ZX\n", k_shared.get_mpz_t());
    gmp_printf("e = %ZX\n", public_key_A.e.get_mpz_t());
    gmp_printf("n = %ZX\n", public_key_A.n.get_mpz_t());
//    gmp_printf("signed_message_message = %ZX\n", signed_message.message.get_mpz_t());

    if (mpz_cmp(k_shared.get_mpz_t(), k.get_mpz_t()) == 0)
    {
        gmp_printf("Signature verified.\n");
        gmp_printf("S = %ZX\n", S.get_mpz_t());
        return S;
    }
    else
    {
        gmp_printf("Signature verification failed.\n");
        gmp_printf("S = %ZX\n", S.get_mpz_t());
        gmp_printf("k = %ZX\n", k.get_mpz_t());

        return mpz_class(0);
    }
}

/*int main(int argc, char *argv[])
{
    KeyPair key_pair;
    SignedMessage signed_message, secret_value;
    key_pair = GenerateKeyPair();
    mpz_class
            M ("32EEB5F5DC5F7C980BA74E4383ABE7A0440A961976A96B07E13BB94A1F1F7FF8", 16),
            C,
            k ("32D4AD66A4612BB02C02A75D955FA38ABBE53137CB850B8E576F15B3585281D1"
                       "A1B74A321ACEEC547F864AEB8712BC162C3EBCC54E0C5096005E07792B9447B2", 16);
    C = Encrypt(M, key_pair.public_key);
    Decrypt(C, key_pair.private_key);
    signed_message = Sign(M, key_pair.private_key);
    Verify(signed_message, key_pair.public_key);
    secret_value = Sendkey(key_pair.public_key, key_pair.private_key, key_pair.public_key, k);
    RecieveKey(key_pair.public_key, key_pair.public_key, key_pair.private_key, secret_value);
    return 0;
}*/
#endif
