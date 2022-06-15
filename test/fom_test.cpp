#include "fom.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("call value", "[call]")
{
    Contract c { Call, 100, 40, 15 };
    price_delta pd = c.at({ 0, 15, .7 });
    REQUIRE(round_cents(pd.price) == 13725);
    REQUIRE(round_cents(pd.delta) == 5457);
}

TEST_CASE("put value", "[put]")
{
    Contract c { Put, 100, 40, 15 };
    price_delta pd = c.at({ 0, 15, .7 });
    REQUIRE(round_cents(pd.price) == 13725);
    REQUIRE(round_cents(pd.delta) == -4543);
}
