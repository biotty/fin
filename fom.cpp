#include "fom.hpp"

#include <iostream>
#include <iomanip>
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
        return x > 0 ? y : 1 - y;
    }

    double yt(long d, long e) {
        return d >= e ? 0 : (e - d) / days_of_year;
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

price_delta Contract::at(MarketPoint m)
{
    switch (type) {
    case Call:
        if (m.price <= 0)
            return { 0, 0 };

        {
            double tt = yt(m.day, expiration);
            if (xdom(tt, m.iv, strike)) {
                if (m.price <= strike) return { 0, 0 };
                else return { m.price - strike, 1 };
            }
            auto [ d1, d2 ] = z(tt, m.iv, m.price, strike);
            double delta = abcdf(d1) * quantity;
            double kd = abcdf(d2) * quantity;
            return { m.price * delta - strike * kd, delta };
        }
    case Put:
        break;
    }

    if (m.price <= 0)
        return { strike - m.price, 1 };

    double tt = yt(m.day, expiration);
    if (xdom(tt, m.iv, strike)) {
        if (strike <= m.price) return { 0, 0 };
        else return { strike - m.price, -1 };
    }
    auto [ d1, d2 ] = z(tt, m.iv, m.price, strike);
    double delta = abcdf(-d1) * quantity;
    double kd = abcdf(-d2) * quantity;
    return { strike * kd - m.price * delta, -delta };
}
