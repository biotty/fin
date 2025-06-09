# fin

Note that this code is not financial in nature, which should be clear by
(as an example) the use of floating point types for monetary values.
This code contains functionality to track stock option contracts for
orientational, not accurate, purposes.  This is not financial advice.

## library content

```
price_delta Contract::at(MarketPoint m);
```

Price and delta calculation of an option contract given a stock price
and current IV in its option market.  The calculation is based on the
binomial option pricing model, which is roughly suitable for an American
style contract.
