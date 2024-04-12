static void initialize_dec(void) {
 static volatile int init_done = 0;

 if (!init_done)
 {
        vpx_dsp_rtcd();
        vp8_init_intra_predictors();
        init_done = 1;
 }
}
