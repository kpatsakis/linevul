static int accel_fp_mul(int idx, mp_int* k, ecc_point *R, mp_int* a,
                        mp_int* modulus, mp_digit mp, int map)
{
#define KB_SIZE 128

#ifdef WOLFSSL_SMALL_STACK
   unsigned char* kb = NULL;
#else
   unsigned char kb[KB_SIZE];
#endif
   int      x, err;
   unsigned y, z = 0, bitlen, bitpos, lut_gap, first;
   mp_int   tk, order;

   if (mp_init_multi(&tk, &order, NULL, NULL, NULL, NULL) != MP_OKAY)
       return MP_INIT_E;

   /* if it's smaller than modulus we fine */
   if (mp_unsigned_bin_size(k) > mp_unsigned_bin_size(modulus)) {
      /* find order */
      y = mp_unsigned_bin_size(modulus);
      for (x = 0; ecc_sets[x].size; x++) {
         if (y <= (unsigned)ecc_sets[x].size) break;
      }

      /* back off if we are on the 521 bit curve */
      if (y == 66) --x;

      if ((err = mp_read_radix(&order, ecc_sets[x].order,
                                                MP_RADIX_HEX)) != MP_OKAY) {
         goto done;
      }

      /* k must be less than modulus */
      if (mp_cmp(k, &order) != MP_LT) {
         if ((err = mp_mod(k, &order, &tk)) != MP_OKAY) {
            goto done;
         }
      } else {
         if ((err = mp_copy(k, &tk)) != MP_OKAY) {
            goto done;
         }
      }
   } else {
      if ((err = mp_copy(k, &tk)) != MP_OKAY) {
         goto done;
      }
   }

   /* get bitlen and round up to next multiple of FP_LUT */
   bitlen  = mp_unsigned_bin_size(modulus) << 3;
   x       = bitlen % FP_LUT;
   if (x) {
      bitlen += FP_LUT - x;
   }
   lut_gap = bitlen / FP_LUT;

   /* get the k value */
   if (mp_unsigned_bin_size(&tk) > (int)(KB_SIZE - 2)) {
      err = BUFFER_E; goto done;
   }

   /* store k */
#ifdef WOLFSSL_SMALL_STACK
   kb = (unsigned char*)XMALLOC(KB_SIZE, NULL, DYNAMIC_TYPE_ECC_BUFFER);
   if (kb == NULL) {
      err = MEMORY_E; goto done;
   }
#endif

   XMEMSET(kb, 0, KB_SIZE);
   if ((err = mp_to_unsigned_bin(&tk, kb)) == MP_OKAY) {
      /* let's reverse kb so it's little endian */
      x = 0;
      y = mp_unsigned_bin_size(&tk);
      if (y > 0) {
          y -= 1;
      }

      while ((unsigned)x < y) {
         z = kb[x]; kb[x] = kb[y]; kb[y] = (byte)z;
         ++x; --y;
      }

      /* at this point we can start, yipee */
      first = 1;
      for (x = lut_gap-1; x >= 0; x--) {
          /* extract FP_LUT bits from kb spread out by lut_gap bits and offset
             by x bits from the start */
          bitpos = x;
          for (y = z = 0; y < FP_LUT; y++) {
             z |= ((kb[bitpos>>3] >> (bitpos&7)) & 1) << y;
             bitpos += lut_gap;  /* it's y*lut_gap + x, but here we can avoid
                                    the mult in each loop */
          }

          /* double if not first */
          if (!first) {
             if ((err = ecc_projective_dbl_point(R, R, a, modulus,
                                                             mp)) != MP_OKAY) {
                break;
             }
          }

          /* add if not first, otherwise copy */
          if (!first && z) {
             if ((err = ecc_projective_add_point(R, fp_cache[idx].LUT[z], R,
                                                 a, modulus, mp)) != MP_OKAY) {
                break;
             }
          } else if (z) {
             if ((mp_copy(fp_cache[idx].LUT[z]->x, R->x) != MP_OKAY) ||
                 (mp_copy(fp_cache[idx].LUT[z]->y, R->y) != MP_OKAY) ||
                 (mp_copy(&fp_cache[idx].mu,       R->z) != MP_OKAY)) {
                 err = GEN_MEM_ERR;
                 break;
             }
                 first = 0;
          }
      }
   }

   if (err == MP_OKAY) {
      (void) z; /* Acknowledge the unused assignment */
      ForceZero(kb, KB_SIZE);

      /* map R back from projective space */
      if (map) {
         err = ecc_map(R, modulus, mp);
      } else {
         err = MP_OKAY;
      }
   }

done:
   /* cleanup */
   mp_clear(&order);
   mp_clear(&tk);

#ifdef WOLFSSL_SMALL_STACK
   XFREE(kb, NULL, DYNAMIC_TYPE_ECC_BUFFER);
#endif

#undef KB_SIZE

   return err;
}
