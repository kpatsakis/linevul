static entry_t *entry_find(const config_t *config, const char *section, const char *key) {
 section_t *sec = section_find(config, section);
 if (!sec)
 return NULL;

 for (const list_node_t *node = list_begin(sec->entries); node != list_end(sec->entries); node = list_next(node)) {
 entry_t *entry = list_node(node);
 if (!strcmp(entry->key, key))
 return entry;
 }

 return NULL;
}
