int yr_arena_write_data(
    YR_ARENA* arena,
    void* data,
    size_t size,
    void** written_data)
{
  void* output;
  int result;

  if (size > free_space(arena->current_page))
  {
    result = yr_arena_allocate_memory(arena, size, &output);

    if (result != ERROR_SUCCESS)
      return result;
  }
  else
  {
    output = arena->current_page->address + arena->current_page->used;
    arena->current_page->used += size;
  }

  memcpy(output, data, size);

  if (written_data != NULL)
    *written_data = output;

  return ERROR_SUCCESS;
}
