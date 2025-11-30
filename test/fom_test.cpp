#include "fom.hpp"
#include "gtest/gtest.h"

TEST(fom, call)
{
    Contract c { .contract_type = ContractType::CALL,
        .quantity = 100, .expiration = 40, .strike = 15 };
    PriceDelta pd = c.at(MarketPoint{ 0, 15, .7 });
    ASSERT_EQ(13725, round_cents(pd.price));
    ASSERT_EQ(5457, round_cents(pd.delta));
}

TEST(fom, put)
{
    Contract c { .contract_type = ContractType::PUT,
        .quantity = 100, .expiration = 40, .strike = 15 };
    PriceDelta pd = c.at(MarketPoint{ 0, 15, .7 });
    ASSERT_EQ(13725, round_cents(pd.price));
    ASSERT_EQ(-4543, round_cents(pd.delta));
}
