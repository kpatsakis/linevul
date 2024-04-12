uarb_copy(uarb to, uarb from, int idigits)
 /* Copy a uarb, may reduce the digit count */
{
 int d, odigits;

 for (d=odigits=0; d<idigits; ++d)
 if ((to[d] = from[d]) != 0)
         odigits = d+1;

 return odigits;
}
