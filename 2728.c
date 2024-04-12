int strcmp16(const char16_t *s1, const char16_t *s2)
{
 char16_t ch;
 int d = 0;

 while ( 1 ) {
    d = (int)(ch = *s1++) - (int)*s2++;
 if ( d || !ch )
 break;
 }

 return d;
}
