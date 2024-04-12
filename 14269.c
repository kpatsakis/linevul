void wc_ecc_fp_free(void)
{
#ifndef WOLFSSL_SP_MATH
#ifndef HAVE_THREAD_LS
   if (initMutex == 0) {
        wc_InitMutex(&ecc_fp_lock);
        initMutex = 1;
   }

   if (wc_LockMutex(&ecc_fp_lock) == 0) {
#endif /* HAVE_THREAD_LS */

       wc_ecc_fp_free_cache();

#ifndef HAVE_THREAD_LS
       wc_UnLockMutex(&ecc_fp_lock);
       wc_FreeMutex(&ecc_fp_lock);
       initMutex = 0;
   }
#endif /* HAVE_THREAD_LS */
#endif
}
