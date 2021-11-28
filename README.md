This project is pretty straight forward. I had to recode printf. Fortunetaly I`ll be able to reuse it in future projects as a legit function of your libft.

# TLDR: this project consists of recoding a simplified version of the printf function.

It manage the following conversions: cspdiuxX%

Any combination of the following flags: ’-0.’ and minimum field width
with all conversions

And all the following flags: ’# +’.


# Instructions

1 - Compiling

Clone this repo -> cd into it -> then type make

2 - To use in your own code

include its header:

#include "ft_printf.h"

and then add these flags, when compiling.

-L <libftprintf.a path> -lftprintf -I <ft_printf.h path>
