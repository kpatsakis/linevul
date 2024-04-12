rechunk_length(struct IDAT *idat)
 /* Return the length for the next IDAT chunk, taking into account
    * rechunking.
    */
{
   png_uint_32 len = idat->global->idat_max;

 if (len == 0) /* use original chunk lengths */
 {
 const struct IDAT_list *cur;
 unsigned int count;

 if (idat->idat_index == 0) /* at the new chunk (first time) */
 return idat->idat_length; /* use the cache */

 /* Otherwise rechunk_length is called at the end of a chunk for the length
       * of the next one.
       */
      cur = idat->idat_cur;
      count = idat->idat_count;

      assert(idat->idat_index == idat->idat_length &&
         idat->idat_length == cur->lengths[count]);

 /* Return length of the *next* chunk */
 if (++count < cur->count)
 return cur->lengths[count];

 /* End of this list */
      assert(cur != idat->idat_list_tail);
      cur = cur->next;
      assert(cur != NULL && cur->count > 0);
 return cur->lengths[0];
 }

 else /* rechunking */
 {
 /* The chunk size is the lesser of file->idat_max and the number
       * of remaining bytes.
       */
      png_uint_32 have = idat->idat_length - idat->idat_index;

 if (len > have)
 {
 struct IDAT_list *cur = idat->idat_cur;
 unsigned int j = idat->idat_count+1; /* the next IDAT in the list */

 do
 {
 /* Add up the remaining bytes.  This can't overflow because the
             * individual lengths are always <= 0x7fffffff, so when we add two
             * of them overflow is not possible.
             */
            assert(cur != NULL);

 for (;;)
 {
 /* NOTE: IDAT_list::count here, not IDAT_list::length */
 for (; j < cur->count; ++j)
 {
                  have += cur->lengths[j];
 if (len <= have)
 return len;
 }

 /* If this was the end return the count of the available bytes */
 if (cur == idat->idat_list_tail)
 return have;

               cur = cur->next;
               j = 0;
 }
 }
 while (len > have);
 }

 return len;
 }
}
