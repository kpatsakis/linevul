int do_mp_jacobi(mp_int* a, mp_int* n, int* c)
{
  int      k, s, res;
  int      r = 0; /* initialize to help static analysis out */
  mp_digit residue;

  /* if a < 0 return MP_VAL */
  if (mp_isneg(a) == MP_YES) {
     return MP_VAL;
  }

  /* if n <= 0 return MP_VAL */
  if (mp_cmp_d(n, 0) != MP_GT) {
     return MP_VAL;
  }

  /* step 1. handle case of a == 0 */
  if (mp_iszero (a) == MP_YES) {
     /* special case of a == 0 and n == 1 */
     if (mp_cmp_d (n, 1) == MP_EQ) {
       *c = 1;
     } else {
       *c = 0;
     }
     return MP_OKAY;
  }

  /* step 2.  if a == 1, return 1 */
  if (mp_cmp_d (a, 1) == MP_EQ) {
    *c = 1;
    return MP_OKAY;
  }

  /* default */
  s = 0;

  /* divide out larger power of two */
  k = mp_cnt_lsb(a);
  res = mp_div_2d(a, k, a, NULL);

  if (res == MP_OKAY) {
    /* step 4.  if e is even set s=1 */
    if ((k & 1) == 0) {
      s = 1;
    } else {
      /* else set s=1 if p = 1/7 (mod 8) or s=-1 if p = 3/5 (mod 8) */
      residue = n->dp[0] & 7;

      if (residue == 1 || residue == 7) {
        s = 1;
      } else if (residue == 3 || residue == 5) {
        s = -1;
      }
    }

    /* step 5.  if p == 3 (mod 4) *and* a == 3 (mod 4) then s = -s */
    if ( ((n->dp[0] & 3) == 3) && ((a->dp[0] & 3) == 3)) {
      s = -s;
    }
  }

  if (res == MP_OKAY) {
    /* if a == 1 we're done */
    if (mp_cmp_d(a, 1) == MP_EQ) {
      *c = s;
    } else {
      /* n1 = n mod a */
      res = mp_mod (n, a, n);
      if (res == MP_OKAY)
        res = do_mp_jacobi(n, a, &r);

      if (res == MP_OKAY)
        *c = s * r;
    }
  }

  return res;
}
