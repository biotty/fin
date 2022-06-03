#include "fm.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("deriv", "[call]")
{
    Contract c = Contract::make_call(100, 15, 40);
    price_delta pd = c.at({ 0, 15, .7 });
    REQUIRE(round_cents(pd.price) == 13725);
    REQUIRE(round_cents(pd.delta) == 5457);
}
