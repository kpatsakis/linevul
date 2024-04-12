VOID ixheaacd_norm_qmf_in_buf_2(ia_esbr_hbe_txposer_struct *ptr_hbe_txposer,
                                WORD32 qmf_band_idx) {
  WORD32 i;
  FLOAT32 *in_buf = &ptr_hbe_txposer->qmf_in_buf[0][2 * qmf_band_idx];
  FLOAT32 *norm_buf = &ptr_hbe_txposer->norm_qmf_in_buf[0][2 * qmf_band_idx];

 for (; qmf_band_idx <= ptr_hbe_txposer->x_over_qmf[1]; qmf_band_idx++) {
 for (i = 0; i < ptr_hbe_txposer->hbe_qmf_in_len; i++) {
      FLOAT32 mag_scaling_fac = 0.0f;
      FLOAT32 x_r, x_i, temp;
      FLOAT64 base = 1e-17;
      x_r = in_buf[0];
      x_i = in_buf[1];

      temp = x_r * x_r;
      base = base + temp;
      temp = x_i * x_i;
      base = base + x_i * x_i;

      mag_scaling_fac = (FLOAT32)(1.0f / base);
      mag_scaling_fac = (FLOAT32)sqrt(sqrt(mag_scaling_fac));

      x_r *= mag_scaling_fac;
      x_i *= mag_scaling_fac;

      norm_buf[0] = x_r;
      norm_buf[1] = x_i;

      in_buf += 128;
      norm_buf += 128;
 }

    in_buf -= (128 * (ptr_hbe_txposer->hbe_qmf_in_len) - 2);
    norm_buf -= (128 * (ptr_hbe_txposer->hbe_qmf_in_len) - 2);
 }
}
