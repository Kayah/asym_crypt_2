#ifndef CPP_UTILS
#define CPP_UTILS
#include <stdio.h>
#include <gmpxx.h>
#include <math.h>
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include "calc.h"
/***size of array***/
#define N  32

using std::endl;
using std::cout;
using std::string;
typedef char *(*BbsPF)();
const BbsPF pf = bbs;

int main ()
{
  string a;
	a = fromDecToHex(255,16);  
cout<< a << endl;
	mpz_class p("340282366920938463463374607431768211456");
    
  //  cout<< millerRabin(p)<<endl; 
  //  getRandomPrimeNumber(pf);
    return 0;
} 

mpz_class getRandomInt(mpz_class p)
{
    mpz_class x("0"),
              randomGen(p.get_mpz_t());
    gmp_randstate_t state;
    gmp_randinit_mt(state);
    unsigned long seed;
    gmp_randseed_ui(state, seed);   
    mpz_urandomm(x.get_mpz_t(),state,randomGen.get_mpz_t());      

    if(x == 0) x += 2;
    if(x == 1) x += 1;
  
    return x; 
}
bool millerRabin(mpz_class p)
{
    mpz_class pMinusOne(p.get_mpz_t()-1),
              tmpPMinusOne(p.get_mpz_t()-1),
              one("1"),
              two("2"),
              minusOne("-1"),
              x("0"),
              powVal("0"), //for d
              powmResult("0"),
              tmpPower("0"),
              xR("0"),
              resultOfGCD("0");
   
    mpz_class  d("0");
    mpz_class  s("0");
    mpz_class  k("0");
    
    //tmp p - minus one mod
    mpz_class result("1");
    mpz_mod(result.get_mpz_t(),tmpPMinusOne.get_mpz_t(),two.get_mpz_t());
    cout << result<<endl;
    //cout << tmpPMinusOne.get_ui(); не помещается
    mpz_mod(result.get_mpz_t(),tmpPMinusOne.get_mpz_t(),two.get_mpz_t());
   // while(tmpPMinusOne.get_ui()%two.get_ui() == 0) не помещается  
    while(result == 0)
    {
	//cout << "!!!!!!!!!!!!!!!!!!!!!";
        s++;
        tmpPMinusOne /= 2;
	mpz_mod(result.get_mpz_t(),tmpPMinusOne.get_mpz_t(),two.get_mpz_t());
	//cout << s <<endl;
    }
    
    d = tmpPMinusOne;
   // cout << s <<" "<< d << endl;
    powVal = d;

   
    for(k = 0; k < 1000; k++)
    {
        //step 1

        x = getRandomInt(p);
        mpz_gcd(resultOfGCD.get_mpz_t(),x.get_mpz_t(),p.get_mpz_t());
       // cout << "result of gcd" << resultOfGCD << endl;
        if(resultOfGCD.get_ui() != 1)//вмещается (так как gcd не будет больше UL)
	{
		 cout<<"p isn't prime" << endl;
		 return false;
        }
        //step 2.1            
        
        mpz_powm(powmResult.get_mpz_t(),x.get_mpz_t(),powVal.get_mpz_t(),p.get_mpz_t());
        if((mpz_cmp(powmResult.get_mpz_t(),one.get_mpz_t())==0) || (mpz_cmp(powmResult.get_mpz_t(),minusOne.get_mpz_t())==0))
        {
		//cout <<" continue" << endl;
		continue;
            //?????    
        }
	//step 2.2
	//cout <<"tmpPower" <<tmpPower << endl;
        for(int r = 1; r <= s-1; r++)
        {
		mpz_pow_ui(tmpPower.get_mpz_t(),two.get_mpz_t(),r);	        	  	
		powVal *= tmpPower;
		mpz_powm(xR.get_mpz_t(),x.get_mpz_t(),powVal.get_mpz_t(),p.get_mpz_t());
		
		if(xR==minusOne)
		//if(mpz_cmp(xR.get_mpz_t(),minusOne.get_mpz_t())==0)
		{
			continue;
		}
		else if(xR==one)
		//else if(mpz_cmp(xR.get_mpz_t(),one.get_mpz_t())==0)
		{
			cout << "Xr == one " << endl;
			return false;
		}
	//step 2.3
	
		if( r == (s-1))
		{
			cout << "r == s-1" <<endl;
			return false;
		}
	}	
    } 
    
    return true;
}

unsigned long long getRandomPrimeNumber(char*(*pf)())
{
    char *arrOfBits = pf();
    int p = 0; 
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
