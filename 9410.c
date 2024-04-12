static BROTLI_INLINE uint32_t ReadBlockLength(const HuffmanCode* table,
                                              BrotliBitReader* br) {
  uint32_t code;
  uint32_t nbits;
  code = ReadSymbol(table, br);
  nbits = kBlockLengthPrefixCode[code].nbits; /* nbits == 2..24 */
  return kBlockLengthPrefixCode[code].offset + BrotliReadBits(br, nbits);
}
