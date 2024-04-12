static BROTLI_INLINE int DecodeBlockTypeAndLength(int safe,
    BrotliState* s, int tree_type) {
  uint32_t max_block_type = s->num_block_types[tree_type];
  int tree_offset = tree_type * BROTLI_HUFFMAN_MAX_TABLE_SIZE;
  const HuffmanCode* type_tree = &s->block_type_trees[tree_offset];
  const HuffmanCode* len_tree = &s->block_len_trees[tree_offset];
  BrotliBitReader* br = &s->br;
  uint32_t* ringbuffer = &s->block_type_rb[tree_type * 2];
  uint32_t block_type;

  /* Read 0..15 + 3..39 bits */
  if (!safe) {
    block_type = ReadSymbol(type_tree, br);
    s->block_length[tree_type] = ReadBlockLength(len_tree, br);
  } else {
    BrotliBitReaderState memento;
    BrotliBitReaderSaveState(br, &memento);
    if (!SafeReadSymbol(type_tree, br, &block_type)) return 0;
    if (!SafeReadBlockLength(s, &s->block_length[tree_type], len_tree, br)) {
      s->substate_read_block_length = BROTLI_STATE_READ_BLOCK_LENGTH_NONE;
      BrotliBitReaderRestoreState(br, &memento);
      return 0;
    }
  }

  if (block_type == 1) {
    block_type = ringbuffer[1] + 1;
  } else if (block_type == 0) {
    block_type = ringbuffer[0];
  } else {
    block_type -= 2;
  }
  if (block_type >= max_block_type) {
    block_type -= max_block_type;
  }
  ringbuffer[0] = ringbuffer[1];
  ringbuffer[1] = block_type;
  return 1;
}
