entry_guards_update_confirmed(guard_selection_t *gs)
{
  smartlist_clear(gs->confirmed_entry_guards);
  SMARTLIST_FOREACH_BEGIN(gs->sampled_entry_guards, entry_guard_t *, guard) {
    if (guard->confirmed_idx >= 0)
      smartlist_add(gs->confirmed_entry_guards, guard);
  } SMARTLIST_FOREACH_END(guard);

  smartlist_sort(gs->confirmed_entry_guards, compare_guards_by_confirmed_idx);

  int any_changed = 0;
  SMARTLIST_FOREACH_BEGIN(gs->confirmed_entry_guards, entry_guard_t *, guard) {
    if (guard->confirmed_idx != guard_sl_idx) {
      any_changed = 1;
      guard->confirmed_idx = guard_sl_idx;
    }
  } SMARTLIST_FOREACH_END(guard);

  gs->next_confirmed_idx = smartlist_len(gs->confirmed_entry_guards);

  if (any_changed) {
    entry_guards_changed_for_guard_selection(gs);
  }
}
