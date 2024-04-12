static BROTLI_INLINE void ProcessSingleCodeLength(uint32_t code_len,
    uint32_t* symbol, uint32_t* repeat, uint32_t* space,
    uint32_t* prev_code_len, uint16_t* symbol_lists,
    uint16_t* code_length_histo, int* next_symbol) {
  *repeat = 0;
  if (code_len != 0) { /* code_len == 1..15 */
    symbol_lists[next_symbol[code_len]] = (uint16_t)(*symbol);
    next_symbol[code_len] = (int)(*symbol);
    *prev_code_len = code_len;
    *space -= 32768U >> code_len;
    code_length_histo[code_len]++;
  }
  (*symbol)++;
}
