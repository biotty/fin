# fin

First of all, the following does not yet exist, but is a description of
what is desired as part of this project.  For a description of what is
already in there, jump to the next section, below.

Note that this code is not financial in nature, which should be clear by
(as an example) the use of floating point types for monetary values.
This code contains functionality to track stock option contracts for
orientational, not accurate, purposes.  The input format for importing
of current positions is documented so that a user-provided script may
convert from a specific broker.  Given a file of the daily IV per stock,
the code contains routines that will track on underlyings where open
positions are seen.  Daily price plots may be produced together with
representations of the current contracts and history of opened and
closed contracts.  The code also contains some stock price indicators.
Price plots may be produced augmented with these, on any time unit,
as well as a bubble chart display of price and volume.  A positions
status report visualizing comparable values related to delta and theta
per stock may be produced.

## library content

```
price_delta Contract::at(MarketPoint m);
```

Price and delta calculation of an option contract given a stock price
and current IV in its option market.  The calculation is based on the
binomial option pricing model, which is roughly suitable for an American
style contract.
