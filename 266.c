VOID ixheaacd_hbe_post_anal_xprod3(ia_esbr_hbe_txposer_struct *ptr_hbe_txposer,
                                   WORD32 qmf_voc_columns, WORD32 qmf_band_idx,
                                   FLOAT32 p, WORD32 pitch_in_bins_idx) {
  WORD32 i, inp_band_idx, rem;

  FLOAT32 *out_buf = &ptr_hbe_txposer->qmf_out_buf[2][2 * qmf_band_idx];

 for (; qmf_band_idx < ptr_hbe_txposer->x_over_qmf[2]; qmf_band_idx++) {
    FLOAT32 temp_r, temp_i;
    FLOAT32 temp_r1, temp_i1;
 const FLOAT32 *ptr_sel, *ptr_sel1;

    inp_band_idx = (2 * qmf_band_idx) / 3;
    ptr_sel = &ixheaacd_sel_case[(inp_band_idx + 1) & 3][0];
    ptr_sel1 = &ixheaacd_sel_case[((inp_band_idx + 1) & 3) + 1][0];
    rem = 2 * qmf_band_idx - 3 * inp_band_idx;

 if (rem == 0 || rem == 1) {
      FLOAT32 *in_buf = &ptr_hbe_txposer->qmf_in_buf[0][2 * inp_band_idx];

 for (i = 0; i < qmf_voc_columns; i += 1) {
        WORD32 k;
        FLOAT32 vec_x[2 * HBE_OPER_WIN_LEN];
        FLOAT32 *ptr_vec_x = &vec_x[0];
        FLOAT32 x_zero_band_r, x_zero_band_i;

        FLOAT32 mag_scaling_fac;

 for (k = 0; k < (HBE_OPER_BLK_LEN_3); k += 2) {
          FLOAT64 base1;
          FLOAT64 base = 1e-17;

          temp_r = in_buf[0];
          temp_i = in_buf[1];

          in_buf += 256;

          base1 = base + temp_r * temp_r;
          base1 = base1 + temp_i * temp_i;

          mag_scaling_fac = (FLOAT32)(ixheaacd_cbrt_calc((FLOAT32)base1));

          ptr_vec_x[0] = temp_r * mag_scaling_fac;
          ptr_vec_x[1] = temp_i * mag_scaling_fac;

          temp_r = in_buf[0];
          temp_i = in_buf[1];

          in_buf -= 128;

          temp_r1 = ptr_sel[0] * temp_r + ptr_sel[1] * temp_i;
          temp_i1 = ptr_sel[2] * temp_r + ptr_sel[3] * temp_i;

          temp_r = in_buf[0];
          temp_i = in_buf[1];

          temp_r1 += ptr_sel[4] * temp_r + ptr_sel[5] * temp_i;
          temp_i1 += ptr_sel[6] * temp_r + ptr_sel[7] * temp_i;

          temp_r1 *= 0.3984033437f;
          temp_i1 *= 0.3984033437f;

          base1 = base + temp_r1 * temp_r1;
          base1 = base1 + temp_i1 * temp_i1;
          mag_scaling_fac = (FLOAT32)(ixheaacd_cbrt_calc((FLOAT32)base1));

          ptr_vec_x[2] = temp_r1 * mag_scaling_fac;
          ptr_vec_x[3] = temp_i1 * mag_scaling_fac;

          ptr_vec_x += 4;
          in_buf += 256;
 }
        ptr_vec_x = &vec_x[0];
        temp_r = vec_x[2 * (HBE_ZERO_BAND_IDX - 2)];
        temp_i = vec_x[(2 * (HBE_ZERO_BAND_IDX - 2)) + 1];

        x_zero_band_r = temp_r * temp_r - temp_i * temp_i;
        x_zero_band_i = temp_r * temp_i + temp_i * temp_r;

 for (k = 0; k < (HBE_OPER_BLK_LEN_3); k++) {
          temp_r = ptr_vec_x[0] * x_zero_band_r - ptr_vec_x[1] * x_zero_band_i;
          temp_i = ptr_vec_x[0] * x_zero_band_i + ptr_vec_x[1] * x_zero_band_r;

          out_buf[0] += (temp_r * 0.4714045f);
          out_buf[1] += (temp_i * 0.4714045f);

          ptr_vec_x += 2;
          out_buf += 128;
 }

        ixheaacd_hbe_xprod_proc_3(ptr_hbe_txposer, qmf_band_idx, i, p,
                                  pitch_in_bins_idx);

        in_buf -= 128 * 11;
        out_buf -= 128 * 6;
 }
 } else {
      FLOAT32 *in_buf = &ptr_hbe_txposer->qmf_in_buf[0][2 * inp_band_idx];
      FLOAT32 *in_buf1 =
 &ptr_hbe_txposer->qmf_in_buf[0][2 * (inp_band_idx + 1)];

 for (i = 0; i < qmf_voc_columns; i++) {
        WORD32 k;
        FLOAT32 vec_x[2 * HBE_OPER_WIN_LEN];
        FLOAT32 vec_x_cap[2 * HBE_OPER_WIN_LEN];

        FLOAT32 x_zero_band_r, x_zero_band_i;
        FLOAT32 *ptr_vec_x = &vec_x[0];
        FLOAT32 *ptr_vec_x_cap = &vec_x_cap[0];

        FLOAT32 mag_scaling_fac;

 for (k = 0; k < (HBE_OPER_BLK_LEN_3); k += 2) {
          FLOAT32 tmp_vr, tmp_vi;
          FLOAT32 tmp_cr, tmp_ci;
          FLOAT64 base1;
          FLOAT64 base = 1e-17;

          temp_r1 = in_buf[0];
          temp_i1 = in_buf[1];
          temp_r = in_buf1[0];
          temp_i = in_buf1[1];

          base1 = base + temp_r * temp_r;
          base1 = base1 + temp_i * temp_i;

          mag_scaling_fac = (FLOAT32)(ixheaacd_cbrt_calc((FLOAT32)base1));

          ptr_vec_x[0] = temp_r * mag_scaling_fac;
          ptr_vec_x[1] = temp_i * mag_scaling_fac;

          base1 = base + temp_r1 * temp_r1;
          base1 = base1 + temp_i1 * temp_i1;

          mag_scaling_fac = (FLOAT32)(ixheaacd_cbrt_calc((FLOAT32)base1));

          ptr_vec_x_cap[0] = temp_r1 * mag_scaling_fac;
          ptr_vec_x_cap[1] = temp_i1 * mag_scaling_fac;

          in_buf += 256;

          temp_r = in_buf[0];
          temp_i = in_buf[1];

          temp_r1 = ptr_sel[0] * temp_r + ptr_sel[1] * temp_i;
          temp_i1 = ptr_sel[2] * temp_r + ptr_sel[3] * temp_i;

          in_buf -= 128;

          temp_r = in_buf[0];
          temp_i = in_buf[1];

          tmp_cr = temp_r1 + ptr_sel[4] * temp_r + ptr_sel[5] * temp_i;
          tmp_ci = temp_i1 + ptr_sel[6] * temp_r + ptr_sel[7] * temp_i;

          in_buf1 += 256;

          temp_r = in_buf1[0];
          temp_i = in_buf1[1];

          temp_r1 = ptr_sel1[0] * temp_r + ptr_sel1[1] * temp_i;
          temp_i1 = ptr_sel1[2] * temp_r + ptr_sel1[3] * temp_i;

          in_buf1 -= 128;

          temp_r = in_buf1[0];
          temp_i = in_buf1[1];

          tmp_vr = temp_r1 + ptr_sel1[4] * temp_r + ptr_sel1[5] * temp_i;
          tmp_vi = temp_i1 + ptr_sel1[6] * temp_r + ptr_sel1[7] * temp_i;

          tmp_cr *= 0.3984033437f;
          tmp_ci *= 0.3984033437f;

          tmp_vr *= 0.3984033437f;
          tmp_vi *= 0.3984033437f;

          base1 = base + tmp_vr * tmp_vr;
          base1 = base1 + tmp_vi * tmp_vi;

          mag_scaling_fac = (FLOAT32)(ixheaacd_cbrt_calc((FLOAT32)base1));

          ptr_vec_x[2] = tmp_vr * mag_scaling_fac;
          ptr_vec_x[3] = tmp_vi * mag_scaling_fac;

          base1 = base + tmp_cr * tmp_cr;
          base1 = base1 + tmp_ci * tmp_ci;

          mag_scaling_fac = (FLOAT32)(ixheaacd_cbrt_calc((FLOAT32)base1));

          ptr_vec_x_cap[2] = tmp_cr * mag_scaling_fac;
          ptr_vec_x_cap[3] = tmp_ci * mag_scaling_fac;

          in_buf += 256;
          in_buf1 += 256;
          ptr_vec_x += 4;
          ptr_vec_x_cap += 4;
 }
        ptr_vec_x = &vec_x[0];
        ptr_vec_x_cap = &vec_x_cap[0];

        temp_r = vec_x_cap[2 * (HBE_ZERO_BAND_IDX - 2)];
        temp_i = vec_x_cap[2 * (HBE_ZERO_BAND_IDX - 2) + 1];
        temp_r1 = vec_x[2 * (HBE_ZERO_BAND_IDX - 2)];
        temp_i1 = vec_x[2 * (HBE_ZERO_BAND_IDX - 2) + 1];

        x_zero_band_r = temp_r * temp_r - temp_i * temp_i;
        x_zero_band_i = temp_r * temp_i + temp_i * temp_r;

        temp_r = temp_r1 * temp_r1 - temp_i1 * temp_i1;
        temp_i = temp_r1 * temp_i1 + temp_i1 * temp_r1;

 for (k = 0; k < (HBE_OPER_BLK_LEN_3); k++) {
          temp_r1 = ptr_vec_x[0] * x_zero_band_r - ptr_vec_x[1] * x_zero_band_i;
          temp_i1 = ptr_vec_x[0] * x_zero_band_i + ptr_vec_x[1] * x_zero_band_r;

          temp_r1 += ptr_vec_x_cap[0] * temp_r - ptr_vec_x_cap[1] * temp_i;
          temp_i1 += ptr_vec_x_cap[0] * temp_i + ptr_vec_x_cap[1] * temp_r;

          out_buf[0] += (temp_r1 * 0.23570225f);
          out_buf[1] += (temp_i1 * 0.23570225f);

          out_buf += 128;
          ptr_vec_x += 2;
          ptr_vec_x_cap += 2;
 }

        ixheaacd_hbe_xprod_proc_3(ptr_hbe_txposer, qmf_band_idx, i, p,
                                  pitch_in_bins_idx);

        in_buf -= 128 * 11;
        in_buf1 -= 128 * 11;
        out_buf -= 128 * 6;
 }
 }

    out_buf -= (256 * qmf_voc_columns) - 2;
 }
}
