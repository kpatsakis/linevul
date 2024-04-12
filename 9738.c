VOID ixheaacd_esbr_postradixcompute4(WORD32 *ptr_y, WORD32 *ptr_x,
 const WORD32 *p_dig_rev_tbl,
                                     WORD32 npoints) {
  WORD32 i, k;
  WORD32 h2;
  WORD32 xh0_0, xh1_0, xl0_0, xl1_0;
  WORD32 xh0_1, xh1_1, xl0_1, xl1_1;
  WORD32 x_0, x_1, x_2, x_3;
  WORD32 xh0_2, xh1_2, xl0_2, xl1_2, xh0_3, xh1_3, xl0_3, xl1_3;
  WORD32 x_4, x_5, x_6, x_7;
  WORD32 x_8, x_9, x_a, x_b, x_c, x_d, x_e, x_f;
  WORD32 n00, n10, n20, n30, n01, n11, n21, n31;
  WORD32 n02, n12, n22, n32, n03, n13, n23, n33;
  WORD32 n0, j0;
  WORD32 *x2, *x0;
  WORD32 *y0, *y1, *y2, *y3;

  y0 = ptr_y;
  y2 = ptr_y + (WORD32)npoints;
  x0 = ptr_x;
  x2 = ptr_x + (WORD32)(npoints >> 1);

  y1 = y0 + (WORD32)(npoints >> 1);
  y3 = y2 + (WORD32)(npoints >> 1);

  j0 = 4;
  n0 = npoints >> 2;

 for (k = 0; k < 2; k++) {
 for (i = 0; i<npoints>> 1; i += 8) {
      h2 = *p_dig_rev_tbl++ >> 2;
      x_0 = *x0++;
      x_1 = *x0++;
      x_2 = *x0++;
      x_3 = *x0++;
      x_4 = *x0++;
      x_5 = *x0++;
      x_6 = *x0++;
      x_7 = *x0++;

      xh0_0 = x_0 + x_4;
      xh1_0 = x_1 + x_5;
      xl0_0 = x_0 - x_4;
      xl1_0 = x_1 - x_5;
      xh0_1 = x_2 + x_6;
      xh1_1 = x_3 + x_7;
      xl0_1 = x_2 - x_6;
      xl1_1 = x_3 - x_7;

      n00 = xh0_0 + xh0_1;
      n01 = xh1_0 + xh1_1;
      n10 = xl0_0 + xl1_1;
      n11 = xl1_0 - xl0_1;
      n20 = xh0_0 - xh0_1;
      n21 = xh1_0 - xh1_1;
      n30 = xl0_0 - xl1_1;
      n31 = xl1_0 + xl0_1;

      y0[h2] = n00;
      y0[h2 + 1] = n01;
      y1[h2] = n10;
      y1[h2 + 1] = n11;
      y2[h2] = n20;
      y2[h2 + 1] = n21;
      y3[h2] = n30;
      y3[h2 + 1] = n31;

      x_8 = *x2++;
      x_9 = *x2++;
      x_a = *x2++;
      x_b = *x2++;
      x_c = *x2++;
      x_d = *x2++;
      x_e = *x2++;
      x_f = *x2++;

      xh0_2 = x_8 + x_c;
      xh1_2 = x_9 + x_d;
      xl0_2 = x_8 - x_c;
      xl1_2 = x_9 - x_d;
      xh0_3 = x_a + x_e;
      xh1_3 = x_b + x_f;
      xl0_3 = x_a - x_e;
      xl1_3 = x_b - x_f;

      n02 = xh0_2 + xh0_3;
      n03 = xh1_2 + xh1_3;
      n12 = xl0_2 + xl1_3;
      n13 = xl1_2 - xl0_3;
      n22 = xh0_2 - xh0_3;
      n23 = xh1_2 - xh1_3;
      n32 = xl0_2 - xl1_3;
      n33 = xl1_2 + xl0_3;

      y0[h2 + 2] = n02;
      y0[h2 + 3] = n03;
      y1[h2 + 2] = n12;
      y1[h2 + 3] = n13;
      y2[h2 + 2] = n22;
      y2[h2 + 3] = n23;
      y3[h2 + 2] = n32;
      y3[h2 + 3] = n33;
 }
    x0 += (WORD32)npoints >> 1;
    x2 += (WORD32)npoints >> 1;
 }
}
