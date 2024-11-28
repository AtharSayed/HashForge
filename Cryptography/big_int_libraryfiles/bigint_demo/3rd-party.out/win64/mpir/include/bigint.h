#ifndef __BIG_INT_CLASS_DEFINITION_HEADER_INCLUDED__
#define __BIG_INT_CLASS_DEFINITION_HEADER_INCLUDED__
#if defined(__cplusplus)
#endif /* __cplusplus */
namespace iamtcs {
    /**@brief This class is encapsulating the big Int properties and functions
     **/
    class BigInt {
    private:
        mpz_t z{};
    public:
        static constexpr int EXPORT_WORD_SIZE = sizeof(unsigned char);
        BigInt();
        BigInt(const BigInt& Ithat);
        BigInt(unsigned long int that);
        BigInt(const char* str, unsigned int len, unsigned char base = 16);
        virtual ~BigInt();
        bool fmStr(const char* str, unsigned int  len, unsigned char base = 16);
        bool toStr(char*& str, unsigned int& len, unsigned char base = 16) const;
        bool toUL(unsigned long int& ret) const;
        bool isZero() const;
        void zero();
        size_t MSB() const;
        const mpz_t& MPZ() const;
        int  isPrime(unsigned int iterations = 7) const;
        int  compare(const BigInt& Ithat) const;
        int  compare(unsigned long int that) const;
        void assign(const BigInt& Ithat);
        void assign(unsigned long int that);
#ifdef USE_GMPLIB
        void random(const unsigned long int& numBits);
#else
        void random(const unsigned long int&);
#endif
        inline void setbit(const unsigned long int offset) { mpz_setbit(z, offset); }
        inline void clrbit(const unsigned long int offset) { mpz_clrbit(z, offset); }
        inline void combit(const unsigned long int offset) { mpz_combit(z, offset); }
        inline int  getbit(const unsigned long int offset) const { return mpz_tstbit(z, offset); }
        void AND(const BigInt& Ithat, BigInt* Ires = nullptr);
        void IOR(const BigInt& Ithat, BigInt* Ires = nullptr);
        void XOR(const BigInt& Ithat, BigInt* Ires = nullptr);
        void COM(BigInt* Ires = nullptr);
        void LSH(unsigned long int l, BigInt* Ires = nullptr);
        void RSH(unsigned long int l, BigInt* Ires = nullptr);
        bool add(const BigInt& Ithat, BigInt* Isum = nullptr);
        bool subtract(const BigInt& Ithat, BigInt* Idiff = nullptr);
        bool divideBy(const BigInt& Ithat, BigInt* Iquot = nullptr, BigInt* Irem = nullptr);
        bool multiply(const BigInt& Ithat, BigInt* Iprod = nullptr);
        bool modulo(const BigInt& Ithat, BigInt* Irem = nullptr);
        bool add(unsigned long int that, BigInt* Isum = nullptr);
        bool subtract(unsigned long int that, BigInt* Idiff = nullptr);
        bool divideBy(unsigned long int that, BigInt* Iquot = nullptr, BigInt* Irem = nullptr);
        bool multiply(unsigned long int that, BigInt* Iprod = nullptr);
        bool modulo(unsigned long int that, BigInt* Irem = nullptr);
        bool raisedTo(const BigInt& Ithat, const BigInt& Ithat1, BigInt* Ires = nullptr);
        bool raisedTo(unsigned long int that, BigInt* Ires = nullptr);
        bool powm(BigInt, BigInt, BigInt* Ires = nullptr);
        bool powr(BigInt const&);
        bool inverse_mod(const BigInt& Ithat, BigInt* Ires = nullptr);
        bool square_Root(const BigInt& Ithat, BigInt* Ires = nullptr);
        bool square_Root(unsigned long int that, BigInt* Ires = nullptr);
        int sizeinbase(int that) const;
        int tstbit(unsigned long int that) const;
        bool set_str(char c[], int n);
        int size_bigint() const;
        int divisible(const BigInt& Ithat) const;
        bool cdiv(unsigned long int d);
        bool powmod(unsigned long int  exp, const BigInt& Imod, BigInt* Irem = nullptr);
        bool powmod(const BigInt& Iexp, const BigInt& Imod, BigInt* Irem = nullptr);
        bool root(unsigned long int  nth = 2, BigInt* Iroot = nullptr, BigInt* Irem = nullptr);
        static int cmp(const BigInt* i, const BigInt* j);
        void print() const;
    }; /* class BigInt */
}  // namespace iamtcs
#endif /* __BIG_INT_CLASS_DEFINITION_HEADER_INCLUDED__ */