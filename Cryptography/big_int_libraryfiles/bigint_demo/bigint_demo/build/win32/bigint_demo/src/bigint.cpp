#ifdef _WIN32
#include <Windows.h>
#include "crtdefs.h"
#endif
#include <ctime>
#ifndef __ANDROID__
#define USE_GMPLIB
#endif
#ifndef USE_GMPLIB
#include <random>
#endif
#include <map>
#include <mutex>
#include <array>
#include <functional>
#include <vector>
#include <algorithm>
#include <cassert>
#include <iostream>
#include <cstdlib>
#ifndef USE_GMPLIB
#include "mini-gmp.h"
#elif defined _WIN32
#include <mpir.h>
#else
#include "gmpxx.h"
#include "gmp.h"
#endif

//#include "LockCS.h"
#include "bigint.h"

namespace iamtcs {
#ifdef USE_GMPLIB
    class _RandState_ {
        gmp_randstate_t rs;
        std::mutex bigMutex;
    public:
        _RandState_() {
            std::lock_guard<std::mutex> guard(bigMutex);
            gmp_randinit_default(rs);
            time_t tm = 0;
            srand(static_cast<unsigned int>(time(&tm)));
            gmp_randseed_ui(rs, rand());
        }
        ~_RandState_() { gmp_randclear(rs); }
        void random(mpz_t& z, const unsigned long int& nb) {
            mpz_urandomb(z, rs, nb);
        }
    }; /* class __RandStateInitializer__ */
    static _RandState_ RS;
#endif
    BigInt::BigInt() {
        //Log(logger::getInstance()) {
        mpz_init(z);
    }
    BigInt::BigInt(const BigInt& Ithat) {
        //Log(logger::getInstance()) {
        mpz_init_set(z, Ithat.z);
    }
    BigInt::BigInt(const unsigned long int that)  {
        //Log(logger::getInstance()) {
        mpz_init_set_ui(z, that);
    }
    BigInt::BigInt(const char* strIn, const unsigned int len, unsigned char base)  {
        //Log(logger::getInstance()) {
        fmStr(strIn, len, base);
    }
    BigInt::~BigInt() {
        mpz_clear(z);
    }
    bool BigInt::fmStr(const char* strIn,
        const unsigned int len,
        unsigned char base)
    {
        if (!strIn)
            return false;
        char* str = const_cast<char*>(strIn);
        char c = 0;
        if (len && ((c = *(str + len)))) {
            *(str + len) = 0;
        }
        if (0 != mpz_set_str(z, str, static_cast<int>(base)))
            return false;
        if (c)
            *(str + len) = c;
        return true;
    }
    bool BigInt::toStr(char*& str,
        unsigned int& len,
        unsigned char base) const
    {
        if (base < 2 || 36 < base)
            return false;
        if (!str || len < (2 + mpz_sizeinbase(z, base))) {
            str = nullptr;
            len = 0;
        }
        char* ret = mpz_get_str(const_cast<char*>(str), base, z);
        if (!ret) return false;
        if (ret != str)
            str = ret;
        unsigned int retlen = 0;
        while (*ret++)
            ++retlen;
        len = retlen;
        return true;
    }
    bool BigInt::toUL(unsigned long int& ret) const { ret = mpz_get_ui(z); return true; }
    bool BigInt::isZero() const { return !mpz_sgn(z); }
    void BigInt::zero() { mpz_set_ui(z, 0); }
    size_t BigInt::MSB() const { return mpz_sizeinbase(z, 2); }
    const mpz_t& BigInt::MPZ() const { return z; }
    /**
    * Return Value:
    *       2 : Definitely Prime
    *       1 : Probably   Prime
    *       0 : Definitely Composite
    **/
    int BigInt::isPrime(unsigned int iterations) const {
        if (!iterations)
            iterations = 7;
        return mpz_probab_prime_p(z, static_cast<int>(iterations));
    }
    int BigInt::compare(const BigInt& Ithat) const { return mpz_cmp(z, Ithat.z); }
    int BigInt::compare(const unsigned long int that) const { return mpz_cmp_ui(z, that); }
    void BigInt::assign(const BigInt& Ithat) { mpz_set(z, Ithat.z); }
    void BigInt::assign(const unsigned long int that) { mpz_set_ui(z, that); }
    void BigInt::AND(const BigInt& Ithat, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_and(Ires->z, z, Ithat.z);
    }
    void BigInt::IOR(const BigInt& Ithat, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_ior(Ires->z, z, Ithat.z);
    }
    void BigInt::XOR(const BigInt& Ithat, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_xor(Ires->z, z, Ithat.z);
    }
    void BigInt::COM(BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_com(Ires->z, z);
    }
    void BigInt::LSH(const unsigned long int l, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_mul_2exp(Ires->z, z, l);
    }
    void BigInt::RSH(const unsigned long int l, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_tdiv_q_2exp(Ires->z, z, l);
    }
    bool BigInt::add(const BigInt& Ithat, BigInt* Isum) {
        if (!Isum)
            Isum = this;
        mpz_add(Isum->z, z, Ithat.z);
        return true;
    }
    bool BigInt::subtract(const BigInt& Ithat, BigInt* Idiff) {
        if (!Idiff)
            Idiff = this;
        mpz_sub(Idiff->z, z, Ithat.z);
        return true;
    }
    bool BigInt::divideBy(const BigInt& Ithat, BigInt* Iquot, BigInt* Irem) {
        if (!Iquot)
            Iquot = this;
        if (Irem && this == Irem)
            return false;
        if (Irem)
            mpz_tdiv_qr(Iquot->z, Irem->z, z, Ithat.z);
        else
            mpz_tdiv_q(Iquot->z, z, Ithat.z);
        return true;
    }
    bool BigInt::multiply(const BigInt& Ithat, BigInt* Iprod) {
        if (!Iprod)
            Iprod = this;
        mpz_mul(Iprod->z, z, Ithat.z);
        return true;
    }
    bool BigInt::modulo(const BigInt& Ithat, BigInt* Irem) {
        if (!Irem)
            Irem = this;
        mpz_mod(Irem->z, z, Ithat.z);
        return true;
    }
    bool BigInt::add(const unsigned long int that, BigInt* Isum) {
        if (!Isum)
            Isum = this;
        mpz_add_ui(Isum->z, z, that);
        return true;
    }
    bool BigInt::subtract(const unsigned long int that, BigInt* Idiff) {
        if (!Idiff)
            Idiff = this;
        mpz_sub_ui(Idiff->z, z, that);
        return true;
    }
    bool BigInt::divideBy(const unsigned long int that, BigInt* Iquot, BigInt* Irem) {
        if (!Iquot)
            Iquot = this;
        if (Irem && this == Irem)
            return false;
        if (Irem)
            mpz_tdiv_qr_ui(Iquot->z, Irem->z, z, that);
        else
            mpz_tdiv_q_ui(Iquot->z, z, that);
        return true;
    }
    bool BigInt::multiply(const unsigned long int that, BigInt* Iprod) {
        if (!Iprod)
            Iprod = this;
        mpz_mul_ui(Iprod->z, z, that);
        return true;
    }
    bool BigInt::modulo(const unsigned long int that, BigInt* Irem) {
        if (!Irem)
            Irem = this;
        mpz_mod_ui(Irem->z, z, that);
        return true;
    }
    bool BigInt::raisedTo(const BigInt& Ithat, const BigInt& Ithat1, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_powm(Ires->z, z, Ithat.z, Ithat1.z);
        return true;
    }
    bool BigInt::raisedTo(const unsigned long int that, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_pow_ui(Ires->z, z, that);
        return true;
    }
    bool BigInt::powm(BigInt exp, BigInt mod, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_powm(Ires->z, z, exp.z, mod.z);
        return true;
    }
    bool BigInt::powr(BigInt const& n) {
        BigInt res;
        if (n.compare(0) == 0)
            res.assign(1);
        else {
            mpz_set(res.z, z);
            const int bts = n.sizeinbase(2);
            for (int i = bts - 2; i >= 0; i--) {
                res.raisedTo(2);
                if (n.tstbit(i))
                    mpz_mul(res.z, res.z, z);
            }
        }
        mpz_set(z, res.z);
        return true;
    }
    bool BigInt::inverse_mod(const BigInt& Ithat, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_invert(Ires->z, z, Ithat.z);
        return true;
    }
    bool BigInt::square_Root(const BigInt& Ithat, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_sqrt(Ires->z, Ithat.z);
        return true;
    }
    bool BigInt::square_Root(const unsigned long int, BigInt* Ires) {
        if (!Ires)
            Ires = this;
        mpz_sqrt(Ires->z, z);
        return true;
    }
    int BigInt::sizeinbase(int that) const
    {
        return mpz_sizeinbase(z, that);
    }
    int BigInt::tstbit(unsigned long int that) const
    {
        return mpz_tstbit(z, that);
    }
    int BigInt::size_bigint() const
    {
        const size_t t = mpz_size(z);
        return static_cast<int>(t);
    }
    bool BigInt::set_str(char c[], int n) {
        mpz_init_set_str(z, c, n);
        return true;
    }
    int BigInt::divisible(const BigInt& Ithat) const
    {
        return mpz_divisible_p(z, Ithat.z);
    }
    bool BigInt::cdiv(unsigned long int d) {
        mpz_cdiv_q_ui(z, z, d);
        return true;
    }
    bool BigInt::powmod(const BigInt& Iexp, const BigInt& Imod, BigInt* Irem) {
        if (!Irem)
            Irem = this;
        mpz_powm(Irem->z, z, Iexp.z, Imod.z);
        return true;
    }
    bool BigInt::powmod(const unsigned long int exp, const BigInt& Imod, BigInt* Irem) {
        if (!Irem)
            Irem = this;
        mpz_powm_ui(Irem->z, z, exp, Imod.z);
        return true;
    }
    bool BigInt::root(const unsigned long int nth, BigInt* Iroot, BigInt*) {
        if (!Iroot)
            Iroot = this;
        mpz_root(Iroot->z, z, nth);
        return true;
    }
    int BigInt::cmp(const BigInt* i, const BigInt* j) {
        if (!i)
            return j ? -1 : 0;
        else if (!j)
            return +1;
        else
            return i->compare(*j);
    }
    void BigInt::print() const {
        char* ch = nullptr;
        unsigned int len = 0;
        this->toStr(ch, len);
        std::cout << std::endl << ch << std::endl;
        //this->Log.v(ch);
        gmp_printf("%Zx\n\n",z);
    }

#ifdef USE_GMPLIB
    void BigInt::random(const unsigned long int& numBits) { RS.random(z, numBits); }
#else
    template<class T = std::mt19937, std::size_t N = T::state_size>
    auto ProperlySeededRandomEngine() -> typename std::enable_if<!!N, T>::type {
        typename T::result_type random_data[N];
        std::random_device source;
        std::generate(std::begin(random_data), std::end(random_data), std::ref(source));
        std::seed_seq seeds(std::begin(random_data), std::end(random_data));
        T seededEngine(seeds);
        return seededEngine;
    }
    void BigInt::random(const unsigned long int& nb) {
        if (!nb) return;
        const unsigned int nlimbs = nb / (sizeof(unsigned long int) * 8);
        auto rng = ProperlySeededRandomEngine();
        BigInt temp;
        mpz_set_ui(temp.z, nlimbs);
        const mp_ptr limbs = mpz_limbs_write(temp.z, nlimbs);
        for (unsigned int i = 0; i < nlimbs; i++)
            limbs[i] = rng();
        mpz_limbs_finish(temp.z, nlimbs);
        mpz_set(z, temp.z);
    }
#endif
}
