int yr_arena_write_string(
    YR_ARENA* arena,
    const char* string,
    char** written_string)
{
  return yr_arena_write_data(
      arena,
      (void*) string,
      strlen(string) + 1,
      (void**) written_string);
}
