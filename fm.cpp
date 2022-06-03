#include "fm.hpp"

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
    if (e > 0) {  // call
        if (m.s <= 0) return { 0, 0 };
        double tt = yt(m.d, e);
        if (xdom(tt, m.iv, k)) {
            if (m.s <= k) return { 0, 0 };
            else return { m.s - k, 1 };
        }
        auto [ d1, d2 ] = z(tt, m.iv, m.s, k);
        double delta = abcdf(d1) * q;
        double kd = abcdf(d2) * q;
        return { m.s * delta - k * kd, delta };
    } else if (e < 0) {  // put
        if (m.s <= 0) return { k - m.s, 1 };
        double tt = yt(m.d, -e);
        if (xdom(tt, m.iv, k)) {
            if (k <= m.s) return { 0, 0 };
            else return { k - m.s, -1 };
        }
        auto [ d1, d2 ] = z(tt, m.iv, m.s, k);
        double delta = abcdf(-d1) * q;
        double kd = abcdf(-d2) * q;
        return { k * kd - m.s * delta, -delta };
    }
    // own
    return { (k - m.s) * q , static_cast<double>(q) };
}
