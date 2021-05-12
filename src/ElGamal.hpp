/****************************************************************************
this hpp implements HISE from ElGamal PKE
*****************************************************************************
* @author     Yu Chen
* @paper      HISE
* @copyright  MIT license (see LICENSE file)
*****************************************************************************/
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

#include <mcl/ec.hpp>

#define PRECOMPUTATION

struct TagZn;
typedef mcl::FpT<> Fp;
typedef mcl::FpT<TagZn> Zn;
typedef mcl::EcT<Fp> Ec;

mcl::fp::WindowMethod<Ec> wm_g;
mcl::fp::WindowMethod<Ec> wm_pk;

struct ElGamal_PP
{
	Ec g; 
	size_t bitSize; 
};

struct ElGamal_CT
{
	Ec X; 
	Ec Y;
};


// void Precompute(size_t bitSize, size_t winSize, Ec& g, Ec& h)
// {

//     wm_g.init(g, bitSize, winSize);
//     wm_h.init(h, bitSize, winSize);
// }

void Setup(ElGamal_PP& PP, Ec g)
{
	PP.g = g; 

	#ifdef DEBUG 
		cout << "PP.g = " << PP.g << endl;
	#endif

	PP.bitSize = Zn::getBitSize(); 
}


void KeyGen(const ElGamal_PP& PP, Ec& pk, Zn& sk)
{
	sk.setRand(); 
	Ec::mul(pk, PP.g, sk); // pk = g^sk

	#ifdef DEBUG 
		cout << "pk = " << pk << endl;
		cout << "sk = " << sk << endl;
	#endif
}


void Encrypt(const ElGamal_PP& PP, const Ec& pk, const Ec& PT, ElGamal_CT& CT)
{	
	Zn r; 
	r.setRand(); 

	#ifdef PRECOMPUTATION
		wm_g.mul(CT.X, r);
        wm_pk.mul(CT.Y, r);
	#else
		Ec::mul(CT.X, PP.g, r); // X = g^r
		Ec::mul(CT.Y, pk, r);   // Y = pk^r
	#endif

	Ec::add(CT.Y, CT.Y, PT); // Y = pk^r \cdot M

	#ifdef DEBUG 
	cout << "PT = " << PT << endl;
	cout << "CT.X = " << CT.X << endl;
	cout << "CT.Y = " << CT.Y << endl;
	#endif 
}

void Decrypt(const Zn& sk, const ElGamal_CT& CT, Ec& PT)
{
	Ec k; 
	Ec::mul(k, CT.X, sk); // k = X^dk
	Ec::sub(PT, CT.Y, k); // m = Y-k
	
	#ifdef DEBUG 
	cout << "PT = " << PT << endl; 
	#endif
}
