static void compute_accelerated_huffman(Codebook *c)
{
   int i, len;
   for (i=0; i < FAST_HUFFMAN_TABLE_SIZE; ++i)
      c->fast_huffman[i] = -1;

   len = c->sparse ? c->sorted_entries : c->entries;
   #ifdef STB_VORBIS_FAST_HUFFMAN_SHORT
   if (len > 32767) len = 32767; // largest possible value we can encode!
   #endif
   for (i=0; i < len; ++i) {
      if (c->codeword_lengths[i] <= STB_VORBIS_FAST_HUFFMAN_LENGTH) {
         uint32 z = c->sparse ? bit_reverse(c->sorted_codewords[i]) : c->codewords[i];
         while (z < FAST_HUFFMAN_TABLE_SIZE) {
             c->fast_huffman[z] = i;
             z += 1 << c->codeword_lengths[i];
         }
      }
   }
}
