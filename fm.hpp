#ifndef FMATH_HPP
#define FMATH_hpp

#include <utility>

constexpr double days_of_year = 365.2422;
long cents(double price);
struct price_delta {
    double price;
    double delta;
};
struct MarketSpot
{
    long d;
    double s;
    double iv;
};
class Contract
{
    long q;  // quantity of contracted assets, or of owned assets
    long e;  // expiration of call, negated when put, or 0: owned asset
    double k;  // strike price of contract

    Contract(long q, long e, double k) : q(q), e(e), k(k) {}
public:
    static Contract make_call(long q, double k, long e) { return { q, e, k }; }
    static Contract make_put(long q, double k, long e) { return { q, -e, k }; }
    static Contract make_own(long q, double k) { return { q, 0, k }; }
    price_delta at(MarketSpot m);
};

#endif
