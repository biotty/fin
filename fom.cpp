#include "fom.hpp"

#include <utility>
#include <cmath>

namespace {
    const double a = sqrt(M_PI / 8);
    const double b = 1 / sqrt(2 * M_PI);

    double phi(double x)
    {
        return b * exp(-x * x * .5);
    }

    double abcdf(double x)
    {
        const double y = .5 + .5 * sqrt(1 - exp(-x * x * a));
        return (x > 0) ? y : 1 - y;
    }

    double yt(long d, long e) {
        return (d >= e) ? 0 : (e - d) / days_of_year;
    }

    bool xdom(double tt, double iv, double k)
    {
        return tt <= 0 or iv <= 0 or k <= 0;
    }

    std::pair<double, double> z(double tt, double iv, double s, double k) {
        const double v = sqrt(tt) * iv;
        const double r = (.5 * tt * iv * iv + log(s / k)) / v;
        return { r, r - v };
    }
}

long round_cents(double price) { return lrint(price * 100); }

PriceDelta Contract::at(MarketPoint m)
{
    const int u = (contract_type == ContractType::CALL) ? 1 : -1;
    if (m.price <= 0) /*[[ unlikely ]]*/ {
        return (u > 0)
                ? PriceDelta{ 0, 0 }
                : PriceDelta{ strike - m.price, 1 };
    }
    const double tt = yt(m.day, expiration);
    if (xdom(tt, m.iv, strike)) /*[[ unlikely ]]*/ {
        const double p = (m.price - strike) * u;
        return (p <= 0)
                ? PriceDelta{ 0, 0 }
                : PriceDelta{ p, static_cast<double>(u) };
    }
    auto w = z(tt, m.iv * u, m.price, strike);
    auto q = quantity * u;
    auto d = q * abcdf(w.first);
    auto k = q * abcdf(w.second);
    return { m.price * d - strike * k, d };
}

