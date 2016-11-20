#ifndef CPP_UTILS
#define CPP_UTILS
#include <stdio.h>
#include <gmpxx.h>
#include <math.h>
#include "utils.h"
#include <iostream>
#include <stdio.h>
#include "calc.h"

#define N  32 //Size of array of bytes

using std::endl;
using std::cout;
using std::string;
typedef unsigned char *(*BbsPF)();
const BbsPF pf = bbs;
bool testSimple(mpz_class);
bool even(mpz_class);
int main ()
{
    mpz_class p("340282366920938463463374607431768211456");
    mpz_class g("1135628817109367756995192706943908321032057986268200345015255110234801");
    mpz_class a("999983");
   // cout << testSimple(p)<<endl;
   
    // cout<< millerRabin(g)<<endl; 
    //mpz_class out = getRandomInt(p);
    //mpz_class out = getRandomPrimeNumber(pf);
    //cout << out << endl;
    return 0;
}

bool even(mpz_class p)
{
    return mpz_even_p(p.get_mpz_t());
    
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

    //if(x == 0) x += 2;
    //if(x == 1) x += 1;
    // верхнюю границу муменьшить на 2
     // тогда без ифов + 2
 
    return x; 
}

bool testSimple(mpz_class p)
{
    mpz_class d("0");
    mpz_class s("0");
    mpz_class tmpP = p-1;
    mpz_class two("2");
    mpz_class x("0"); 
    mpz_class GCD("0");
    mpz_class XD("0");
    mpz_class tmpPower("0");
    mpz_class XR("0");
    mpz_class one("1"); 
    
    while(even(tmpP))
    {
        ++s;
        tmpP >>=1;
    }
    
    d = tmpP;

    for(int k = 0; k < 1000; k++)
    {
        x = getRandomInt(p);
        mpz_gcd(GCD.get_mpz_t(),x.get_mpz_t(),p.get_mpz_t());
    
        if(GCD.get_ui() !=1 )
        {
            return false;    
        }

     
        mpz_powm(XD.get_mpz_t(),x.get_mpz_t(),d.get_mpz_t(),p.get_mpz_t());
        
        if((XD==1)|| (XD==tmpP))
        {
            continue;
            //return true;
        }
        
        for(int r = 1; r < s; r++)
        {
		    mpz_pow_ui(tmpPower.get_mpz_t(),two.get_mpz_t(),r);
            d *= tmpPower;	        	  	
		    mpz_powm(XR.get_mpz_t(),x.get_mpz_t(),d.get_mpz_t(),p.get_mpz_t());
            
            if( XR - p == -1)
            {
                XR = -1;
            }
            
            if( XR == -1)
            {
               continue; 
                //return true;
            }
            if(XR == 1)
            {
                return false;
            }
            
            if( r == (s-1))
            {
                return false;
            }
            
        }       
    }
        
    return true;
}
/*
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
   // cout << result<<endl;
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
    //cout << s <<" "<< d << endl;
    powVal = d;

   
    for(k = 0; k < 1000; k++)
    {
        //step 1

        x = getRandomInt(p);
        mpz_gcd(resultOfGCD.get_mpz_t(),x.get_mpz_t(),p.get_mpz_t());
       // cout << "result of gcd" << resultOfGCD << endl;
        if(resultOfGCD != 1)//вмещается (так как gcd не будет больше UL)
	    {
		 cout<<"p isn't prime" << endl;
		 return false;
        }
        //step 2.1            
        
        mpz_powm(powmResult.get_mpz_t(),x.get_mpz_t(),powVal.get_mpz_t(),p.get_mpz_t());
        if((powmResult==one) || (powmResult==minusOne))//mimusone на pminusone
        {
		//cout <<" continue" << endl;
		    continue;
            //?????    
        }
	//step 2.2
	//cout <<"tmpPower" <<tmpPower << endl;
        for(int r = 1; r <= s-1; r++)
        {
        powVal = d;
		mpz_pow_ui(tmpPower.get_mpz_t(),two.get_mpz_t(),r);	        	  	
		powVal = powVal * tmpPower;
		mpz_powm(xR.get_mpz_t(),x.get_mpz_t(),powVal.get_mpz_t(),p.get_mpz_t());
		if((xR - p) == minusOne)
		{
			xR = minusOne;
		}
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
	
		if( r == (s-1)) //r == s !!!!!!!!!!<<<<<<<<<<<<<<<<<<,
		{
			cout << "r == s-1" <<endl;
			return false;
		}
	}	
    } 
    
    return true;
}*/

mpz_class getRandomPrimeNumber(unsigned char*(*pf)())
{
    unsigned char *arrOfBits = pf();
    string hexStr;
    for (int i = 0; i < N; i++)
    {	
	hexStr.append(fromDecToHex(arrOfBits[i],16));
	  
    }
    mpz_class arg(hexStr,16);   
    mpz_class p("0");
    mpz_class two("2");
    mpz_class pModByTwo("0");
    mpz_class tmp("0");
    bool isSimple = false;
    //cout << arg << endl;
    p = getRandomInt(arg);
    isSimple = millerRabin(p);
    cout << isSimple << endl;
   /* while (!isSimple)
    {
      ///????????????????????????<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<!!!!!!!!!!!!!!!!!!!!!!!!!!!! 
	 p = p + 2;
	 cout << p << endl;
	// if (p == simple)
	// 2p+1 ? simple 
	isSimple = millerRabin(p);
	if(isSimple)
        {
   	    tmp = 2*p+1;
            isSimple = millerRabin(tmp);
            if(isSimple)
		return p;	    
	}	
    }*/   
   
    return p;
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
