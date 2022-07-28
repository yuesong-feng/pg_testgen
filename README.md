# PostgreSQL test data generator

| func | descryption |
| -- | -- |
| rand_int() | random 32 bits integer |
| rand_int(a, b) | random 32 bits integer between [a, b] |
| rand_text() | random text (size in [1, 32]) |
| rand_text(a) | random text (size is a) |
| rand_text(a, b) | random text (size between [a, b]) |
| rows_int(r) | r rows of rand_int() |
| rows_int(r, a, b) | r rows of rand_int(a, b) |
| rows_text(r) | r rows of rand_text()|
| rows_text(r, a) | r rows of rand_text(a) |
| rows_text(r, a, b) | r rows of rand_text(a, b) |
