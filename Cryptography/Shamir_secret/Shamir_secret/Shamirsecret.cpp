// Cpp CodeFile for class SSA header File 
#include "SSA.h"
using namespace std;

InfInt SSA::calculate_Y(int x, vector<InfInt>& poly)
{
    InfInt y = 0;
    InfInt temp = 1;

    for (auto& coeff : poly) {
        y = (y + (coeff * temp));
        temp = (temp * x);
    }

    return y;
}

void SSA::secret_sharing()
{
    vector<InfInt> poly(K);
    poly[0] = S;

    for (int j = 1; j < K; ++j) {
        InfInt p = 0;
        while (p == 0)
            p = (rand() % 997);
        poly[j] = p;
    }

    for (int j = 1; j <= N; ++j) {
        int x = j;
        InfInt y = calculate_Y(x, poly);

        points[j - 1] = { x, y };
    }
}

InfInt SSA::Generate_Secret(InfInt x[], InfInt y[], int M)
{
    struct fraction {
        InfInt num, den;
        fraction(InfInt n, InfInt d)
        {
            num = n, den = d;
        }

        InfInt gcd(InfInt a, InfInt b) {
            while (b != 0) {
                InfInt t = b;
                b = a % b;
                a = t;
            }
            return a;
        }

        void reduce_fraction(fraction& f)
        {
            InfInt gcd_value = gcd(f.num, f.den);
            f.num /= gcd_value, f.den /= gcd_value;
        }

        fraction operator*(fraction f)
        {
            fraction temp(num * f.num, den * f.den);
            reduce_fraction(temp);
            return temp;
        }

        fraction operator+(fraction f)
        {
            fraction temp(num * f.den + den * f.num,
                den * f.den);

            reduce_fraction(temp);
            return temp;
        }
    };

    fraction ans(0, 1);

    for (int i = 0; i < M; ++i) {
        fraction l(y[i], 1);
        for (int j = 0; j < M; ++j) {
            if (i != j) {
                fraction temp(-x[j], x[i] - x[j]);
                l = l * temp;
            }
        }
        ans = ans + l;
    }

    return ans.num;
}

SSA::SSA(string s, int n, int k) : S(s), N(n), K(k), points(n)
{
    secret_sharing();
}

void SSA::operation()
{
    cout << "Secret is divided to " << N
        << " Parts - " << endl;

    for (int i = 0; i < N; ++i) {
        cout << points
            [i].first << " " << points[i].second << endl;
    }
    cout << "We can generate Secret from any of "
        << K << " Parts" << endl;
    int m = 2;

    if (m < K) {
        cout << "Points are less than threshold "
            << K << " Points Required" << endl;
    }

    InfInt* x = new InfInt[m];
    InfInt* y = new InfInt[m];

    for (int i = 0; i < m; ++i) {
        x[i] = points[i].first;
        y[i] = points[i].second;
    }

    // Get back our result again.
    cout << "Our Secret Code is : "
        << Generate_Secret(x, y, m) << endl;
}