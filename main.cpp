#include "utils.h"
#include "rsa.h"
#include "calc.h"

using std::endl;
using std::cout;
using std::string;

typedef unsigned char *(*BbsPF)();
const BbsPF pf = bbs;

int main()
{
    KeyPair key_pair;
    KeyPair new_key_pair;
    mpz_class myN ("BC1966FAC15136FACA21FC426BB1E444BBF297D9853F2C494565D30CDC66CD0E0432EC5344B8FA09596FCF33BF39327A705F15F3B98A9EC38753A57E6C623C4ACB",16);
    mpz_class newyKey("DF92CFF46FD73B33F4194177F7CD05EE6D76319EBF84A85264CCAD020F8790F549B556D19510E56FBE45F04387AEFF3A91627DF089D7ABAA65B08D807F402C3C2",16);
    mpz_class newSig("59B771EFFE99258134D1AE67A45DA8AD65E55085B464199B413D21596561D449691EDD1278E032B3FA43B83F2A01B19CFF154BA3AF5A1612CC111D17CF9661162",16);
    mpz_class myE("10001",16);
    mpz_set(new_key_pair.public_key.n.get_mpz_t(), myN.get_mpz_t());
    mpz_set(new_key_pair.public_key.e.get_mpz_t(), myE.get_mpz_t());
    mpz_class
            p ("25B0C52E797C3AADFC5F0938972B87A465D9E5373EB530362BA0A21084A1E7A5", 16),
            q ("EDD3D25D544D30A6BC0714B50DF4C3427959C5066136F69218335EAFF2C0220C3F", 16 );

    SignedMessage signed_message, secret_value;
    SignedMessage newSignn;
    key_pair = GenerateKeyPair(p,q);
    mpz_class
            M ("32EEB5F5DC5F7C980BA74E4383ABE7A0440A961976A96B07E13BB94A1F1F7FF8", 16),
            C,
            k ("32D4AD66A4612BB02C02A75D955FA38ABBE53137CB850B8E576F15B3585281D1"
                       "A1B74A321ACEEC547F864AEB8712BC162C3EBCC54E0C5096005E07792B9447B2", 16);
//    C = Encrypt(M, key_pair.public_key);
//    Decrypt(C, key_pair.private_key);
//    signed_message = Sign(M, key_pair.private_key);
//    Verify(signed_message, key_pair.public_key);
    mpz_set(newSignn.message.get_mpz_t(),newyKey.get_mpz_t());
    mpz_set(newSignn.signature.get_mpz_t(),newSig.get_mpz_t());
    //gmp_printf("keypair' = %ZX\n", new_key_pair.public_key.n.get_mpz_t());


    secret_value = Sendkey(key_pair.public_key, key_pair.private_key, new_key_pair.public_key, k);
    //RecieveKey(new_key_pair.public_key, key_pair.public_key, key_pair.private_key, newSignn);
    gmp_printf("Key' = %ZX\n", secret_value.message.get_mpz_t());
    gmp_printf("Sig' = %ZX\n", secret_value.signature.get_mpz_t());
    return 0;
}
/*
int main()
{
   // cout << getRandomPrimeNumber(pf)<<endl;
    mpz_class a("769413610058761400034655651558992373923011008199");
   //char * str =  mpz_get_str(NULL,16,a.get_mpz_t());    
    //cout << str << endl;
  return 0;
}*/
