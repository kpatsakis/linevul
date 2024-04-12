static int find_hole(void)
{
   unsigned x;
   int      y, z;
   for (z = -1, y = INT_MAX, x = 0; x < FP_ENTRIES; x++) {
       if (fp_cache[x].lru_count < y && fp_cache[x].lock == 0) {
          z = x;
          y = fp_cache[x].lru_count;
       }
   }

   /* decrease all */
   for (x = 0; x < FP_ENTRIES; x++) {
      if (fp_cache[x].lru_count > 3) {
         --(fp_cache[x].lru_count);
      }
   }

   /* free entry z */
   if (z >= 0 && fp_cache[z].g) {
      mp_clear(&fp_cache[z].mu);
      wc_ecc_del_point(fp_cache[z].g);
      fp_cache[z].g  = NULL;
      for (x = 0; x < (1U<<FP_LUT); x++) {
         wc_ecc_del_point(fp_cache[z].LUT[x]);
         fp_cache[z].LUT[x] = NULL;
      }
      fp_cache[z].lru_count = 0;
   }
   return z;
}
