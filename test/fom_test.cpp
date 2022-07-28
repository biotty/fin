#include "fom.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("call value", "[call]")
{
    Contract c { .contract_type = ContractType::CALL,
        .quantity = 100, .expiration = 40, .strike = 15 };
    PriceDelta pd = c.at(MarketPoint{ .price = 15, .iv = .7 });
    REQUIRE(round_cents(pd.price) == 13725);
    REQUIRE(round_cents(pd.delta) == 5457);
}

TEST_CASE("put value", "[put]")
{
    Contract c { .contract_type = ContractType::PUT,
        .quantity = 100, .expiration = 40, .strike = 15 };
    PriceDelta pd = c.at(MarketPoint{ .price = 15, .iv = .7 });
    REQUIRE(round_cents(pd.price) == 13725);
    REQUIRE(round_cents(pd.delta) == -4543);
}
