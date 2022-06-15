#ifndef FOM_HPP
#define FOM_hpp

#include <utility>

constexpr double days_of_year = 365.2422;
long round_cents(double price);

struct price_delta {
    double price;
    double delta;
};

struct MarketPoint
{
    long day;
    double price;
    double iv;
};

enum ContractType {
    Call,
    Put,
};

struct Contract
{
    ContractType type;
    long quantity;
    long expiration;
    double strike;

    price_delta at(MarketPoint m);
};

#endif
