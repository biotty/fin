#ifndef FOM_HPP
#define FOM_hpp

#include <utility>

constexpr double days_of_year = 365.2422;
long round_cents(double price);

struct PriceDelta {
    double price;
    double delta;
};

struct MarketPoint
{
    long day;
    double price;
    double iv;
};

enum class ContractType {
    CALL,
    PUT,
};

struct Contract
{
    ContractType contract_type;
    long quantity;
    long expiration;
    double strike;

    PriceDelta at(MarketPoint m);
};

#endif

