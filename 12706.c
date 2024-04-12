config_t *config_new_clone(const config_t *src) {
  assert(src != NULL);

 config_t *ret = config_new_empty();

  assert(ret != NULL);

 for (const list_node_t *node = list_begin(src->sections);
       node != list_end(src->sections);
       node = list_next(node)) {
 section_t *sec = list_node(node);

 for (const list_node_t *node_entry = list_begin(sec->entries);
         node_entry != list_end(sec->entries);
         node_entry = list_next(node_entry)) {
 entry_t *entry = list_node(node_entry);

      config_set_string(ret, sec->name, entry->key, entry->value);
 }
 }

 return ret;
}
