#ifndef CPP_UTILS
#define CPP_UTILS
#include <stdio.h>
#include <gmpxx.h>
#include <math.h>
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include "calc.h"
#include <time.h>
#include <limits.h>
#include "rsa.h"
#define N  32 //Size of array of bytes

using std::endl;
using std::cout;
using std::string;
typedef unsigned char *(*BbsPF)();
const BbsPF pf = bbs;
/*int main ()
{
    cout << getRandomPrimeNumber(pf)<<endl;
    return 0;
}
*/
bool even(mpz_class p)
{
    return mpz_even_p(p.get_mpz_t());
}

mpz_class getRandomPrimeNumber(unsigned char*(*bbs)())
{
    unsigned char *arrOfBits = pf();
    string hexStr;
    mpz_class result ("0");
    for (int i = 0; i < N; i++)
    {
        hexStr.append(fromDecToHex(arrOfBits[i],16));
    }
    mpz_class arg (hexStr,16);
    while (true)
    {
        arg = getRandomInt(arg);
        if(!millerRabin(arg))
        {
            result = arg;
            break;
        }
    }

    return result;
}

mpz_class getRandomInt(mpz_class p)
{
    mpz_class x("0");
    /*time_t t;
    srand((unsigned) time(&t));
    gmp_randstate_t state;
    gmp_randinit_default(state);
    mpz_urandomm(x.get_mpz_t(),state,p.get_mpz_t());
    */
    mpz_class randomGen(p.get_mpz_t());
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    gmp_randseed_ui(state, seed);
    mpz_urandomm(x.get_mpz_t(),state,randomGen.get_mpz_t());

    return x;
}

bool millerRabin(mpz_class p)
{
    mpz_class d("0");
    mpz_class s("0");
    mpz_class p_1 = p-1;

    mpz_class tmp = p_1; //for while
    while (even(tmp))
    {
        ++s;
        tmp >>=1;
    }

    d = tmp;// end of temps lifecycle

    mpz_class x("0");
    mpz_class GCD("0");
    mpz_class one("1");
    mpz_class two("2");
    mpz_class xD("0");
    mpz_class xR("0");
    for (int k = 0; k < 30; ++k)
    {
        x = getRandomInt(p_1);

        /*while (mpz_cmp_ui(x.get_mpz_t(),0) == 0 || mpz_cmp_ui(x.get_mpz_t(),1) == 0)
        {
            x = getRandomInt(p_1);
        }*/

        mpz_gcd(GCD.get_mpz_t(),x.get_mpz_t(),p.get_mpz_t());

        if(GCD != one)
        {
            //cout << "GCD != 1" << endl;
            return true; // yes, its composite
        }

        mpz_powm(xD.get_mpz_t(),x.get_mpz_t(),d.get_mpz_t(),p.get_mpz_t());

        if((mpz_cmp_ui(xD.get_mpz_t(),1)==0) || (mpz_cmp(xD.get_mpz_t(),p_1.get_mpz_t())==0))
        {
            continue;
        }

        for (int r = 1; r < s; ++r)
        {
            mpz_powm_ui(xR.get_mpz_t(),xD.get_mpz_t(),2,p.get_mpz_t());

            if(mpz_cmp_ui(xR.get_mpz_t(),1))
            {
                return true;
            }
            if(mpz_cmp(xR.get_mpz_t(),p_1.get_mpz_t()))
            {
                break;
            }
        }
        if((mpz_cmp(xR.get_mpz_t(),p_1.get_mpz_t()) != 0))
        {
            return true; // yes, its composite
        }
    }

    return false; // no, its not composite
}

unsigned char* bbs()
{
  unsigned char* out_put = new unsigned char[N];
  mpz_class p("0xD5BBB96D30086EC484EBA3D7F9CAEB07");
  mpz_class q("0x425D2B9BFDB25B9CF6C416CC6E37B59C1F");
  mpz_class n = p*q;
  mpz_class x;
  mpz_class two("2"); 
  mpz_class b("256");
  mpz_class r;
  r = pow(5,56);
  
  for(int i = 0; i < N; i++)
  {
    mpz_powm(r.get_mpz_t(),r.get_mpz_t(),two.get_mpz_t(),n.get_mpz_t());
    //x = r.get_ui()%b.get_ui();
    mpz_mod(x.get_mpz_t(),r.get_mpz_t(),b.get_mpz_t());
   // cout << x.get_ui() << endl;
    out_put[i] = x.get_ui();
  }
  return out_put;
}
#endif
