#ifndef CPP_UTILS
#define CPP_UTILS
#include <stdio.h>
#include <gmpxx.h>
#include <math.h>
#include "utils.h"
#include <iostream>
#include <stdio.h>

/***size of array***/
#define N  20

using std::endl;
using std::cout;

typedef char *(*BbsPF)();
const BbsPF pf = bbs;

int main ()
{
    mpz_class p("143");
    //p /= 2;
    //cout << p << endl;
    millerRabin(p); 
   // getRandomPrimeNumber(pf);
    return 0;
} 

mpz_class getRandomInt(mpz_class p)
{
    mpz_class x("0"),
              randomGen(p.get_ui());
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    gmp_randseed_ui(state, seed);   
    mpz_urandomm(x.get_mpz_t(),state,randomGen.get_mpz_t());      

    if(x == 0) x += 2;
    if(x == 1) x += 1;
  
    return x; 
}
mpz_class millerRabin(mpz_class p)
{
    mpz_class pMinusOne(p.get_ui()-1),
              tmpPMinusOne(p.get_ui()-1),
              one("1"),
              two("2"),
              minusOne("-1"),
              x("0"),
              powVal("0"),
              powmResult("0"),
              resultOfGCD("0");
   
    int d = 0;
    int s = 0;
    int k;

    while(tmpPMinusOne.get_ui()%2 == 0)
    {
        s++;
        tmpPMinusOne /= 2;
    }
    
    d = tmpPMinusOne.get_ui();
    powVal = d;
    for(k = 0; k < 100; k++)
    {
        //step 1

        x = getRandomInt(p);
        mpz_gcd(resultOfGCD.get_mpz_t(),x.get_mpz_t(),p.get_mpz_t());
       
        if(resultOfGCD.get_ui() != 1) break;
        
        //step 2            
        
        mpz_powm(powmResult.get_mpz_t(),x.get_mpz_t(),powVal.get_mpz_t(),p.get_mpz_t());
        if(powmResult.get_ui() == one.get_ui() || powmResult == minusOne.get_ui())
        {
            //?????    
        }
        for(int r = 1; r <= s; r++)
        {
                
        }
    } 
    
    return p;
}

unsigned long long getRandomPrimeNumber(char*(*pf)())
{
    char *arrOfBits = pf();
    unsigned long long p = 0;
    return p;
}

char * bbs()
{
    char *out_put = new char[N];
    mpz_class r;
    r = pow(5,56);
    mpz_class p("0xD5BBB96D30086EC484EBA3D7F9CAEB07");
    mpz_class q("0x425D2B9BFDB25B9CF6C416CC6E37B59C1F");
    mpz_class n = p*q;
    mpz_class x;
    mpz_class two("2");
    for(int i = 0; i < N; i++)
    {
        mpz_powm(r.get_mpz_t(),r.get_mpz_t(),two.get_mpz_t(),n.get_mpz_t());
        mpz_mod(x.get_mpz_t(),r.get_mpz_t(),two.get_mpz_t());
        //cout<<x.get_ui()<<endl;
        out_put[i] = x.get_ui();
       // cout << (int)out_put[i];
    }
    //return x.get_ui();
    return out_put;
}


	
#endif
