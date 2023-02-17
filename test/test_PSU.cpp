//#define DEBUG

#include "../common/print.hpp"
#include "../common/routines.hpp"
#include "../src/ElGamal.hpp"

#include <vector>
#include <ctime>


int main()
{

    size_t TEST_NUM = integer_power(2, 16); 
    cout << TEST_NUM << endl; 

    Ec g; 
    mcl::initCurve<Ec, Zn>(MCL_SECP256K1, &g); 

    // generate global pp
    ElGamal_PP PP; 
    Setup(PP, g); 

    Zn sk; 
    Ec pk; 

    KeyGen(PP, pk, sk); 


/* benchmark test */
    print_line('-'); 
    cout << "PSU benchmark test begins >>>" << endl;
    print_line('-'); 

#ifdef PRECOMPUTATION
    size_t winSize = 7; 
    //Precompute(PP.bitSize, winSize, g, pk); 

    wm_g.init(g, PP.bitSize, winSize);
    wm_pk.init(pk, PP.bitSize, winSize);
    cout << "PRECOMPUTATION enables" << endl; 
#else
    cout << "PRECOMPUTATION disables" << endl; 
#endif

    // encrypt a random message
    Ec PT, PT_prime;
    Zn s; 
    s.setRand();
    Ec::mul(PT, PP.g, s);  
  
    vector<ElGamal_CT> CT(TEST_NUM);
    vector<Zn> r(TEST_NUM); 

    for(auto i = 0; i < TEST_NUM; i++){
        r[i].setRand(); 
    }

    auto start_time = chrono::steady_clock::now(); 


    for(auto i = 0; i < TEST_NUM; i++){
        Encrypt(PP, pk, PT, CT[i]);
    }

    for(auto i = 0; i < TEST_NUM; i++){
        Decrypt(sk, CT[i], PT_prime); 
        #ifdef DEBUG 
        if (PT == PT_prime){
            cout << "enc/dec test succeeds" << endl;
        }
        else{
            cout << "enc/dec test fails" << endl;    
        }
        #endif
    }

    auto end_time = chrono::steady_clock::now(); 

    auto running_time = end_time - start_time;
    cout << "enc-rerand-dec takes time = " 
    << chrono::duration <double, milli> (running_time).count()/TEST_NUM << " ms" << endl;

    start_time = chrono::steady_clock::now(); 

    for(auto i = 0; i < TEST_NUM; i++) wm_pk.mul(PT, r[i]);

    end_time = chrono::steady_clock::now(); 
    running_time = end_time - start_time;
    cout << "fixed point exp with precomputation takes = " 
    << chrono::duration <double, milli> (running_time).count()/TEST_NUM << " ms" << endl;


    start_time = chrono::steady_clock::now(); 

    for(auto i = 0; i < TEST_NUM; i++) Ec::mul(PT, pk, r[i]);

    end_time = chrono::steady_clock::now(); 
    running_time = end_time - start_time;
    cout << "fixed point exp without precomputation takes = " 
    << chrono::duration <double, milli> (running_time).count()/TEST_NUM << " ms" << endl;


    print_line('-'); 
    cout << "benchmark test ends >>>" << endl;
    print_line('-'); 

    return 0; 
}

