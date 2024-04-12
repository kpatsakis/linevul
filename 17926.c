static int add_entry(int idx, ecc_point *g)
{
   unsigned x, y;

   /* allocate base and LUT */
   fp_cache[idx].g = wc_ecc_new_point();
   if (fp_cache[idx].g == NULL) {
      return GEN_MEM_ERR;
   }

   /* copy x and y */
   if ((mp_copy(g->x, fp_cache[idx].g->x) != MP_OKAY) ||
       (mp_copy(g->y, fp_cache[idx].g->y) != MP_OKAY) ||
       (mp_copy(g->z, fp_cache[idx].g->z) != MP_OKAY)) {
      wc_ecc_del_point(fp_cache[idx].g);
      fp_cache[idx].g = NULL;
      return GEN_MEM_ERR;
   }

   for (x = 0; x < (1U<<FP_LUT); x++) {
      fp_cache[idx].LUT[x] = wc_ecc_new_point();
      if (fp_cache[idx].LUT[x] == NULL) {
         for (y = 0; y < x; y++) {
            wc_ecc_del_point(fp_cache[idx].LUT[y]);
            fp_cache[idx].LUT[y] = NULL;
         }
         wc_ecc_del_point(fp_cache[idx].g);
         fp_cache[idx].g         = NULL;
         fp_cache[idx].lru_count = 0;
         return GEN_MEM_ERR;
      }
   }

   fp_cache[idx].lru_count = 0;

   return MP_OKAY;
}
