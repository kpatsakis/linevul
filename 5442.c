BrotliState* BrotliCreateState(
    brotli_alloc_func alloc_func, brotli_free_func free_func, void* opaque) {
  BrotliState* state = 0;
  if (!alloc_func && !free_func) {
    state = (BrotliState*)malloc(sizeof(BrotliState));
  } else if (alloc_func && free_func) {
    state = (BrotliState*)alloc_func(opaque, sizeof(BrotliState));
  }
  if (state == 0) {
    (void)BROTLI_FAILURE();
    return 0;
  }
  BrotliStateInitWithCustomAllocators(state, alloc_func, free_func, opaque);
  return state;
}
