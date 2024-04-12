int yr_arena_create(
    size_t initial_size,
    int flags,
    YR_ARENA** arena)
{
  YR_ARENA* new_arena;
  YR_ARENA_PAGE* new_page;

  *arena = NULL;
  new_arena = (YR_ARENA*) yr_malloc(sizeof(YR_ARENA));

  if (new_arena == NULL)
    return ERROR_INSUFFICIENT_MEMORY;

  new_page = _yr_arena_new_page(initial_size);

  if (new_page == NULL)
  {
    yr_free(new_arena);
    return ERROR_INSUFFICIENT_MEMORY;
  }

  new_arena->page_list_head = new_page;
  new_arena->current_page = new_page;
  new_arena->flags = flags | ARENA_FLAGS_COALESCED;

  *arena = new_arena;
  return ERROR_SUCCESS;
}
