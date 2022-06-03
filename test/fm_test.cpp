#include "fm.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("foo", "[foo]")
{
    Contract c = Contract::make_call(100, 15, 40);
    MarketSpot ms { 0, 15, .7 };
    price_delta pd = c.at(ms);
    REQUIRE(cents(pd.price) == 13725);
    REQUIRE(cents(pd.delta) == 5457);
}
