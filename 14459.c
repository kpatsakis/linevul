static entry_t *entry_new(const char *key, const char *value) {
 entry_t *entry = osi_calloc(sizeof(entry_t));
 if (!entry)
 return NULL;

  entry->key = osi_strdup(key);
  entry->value = osi_strdup(value);
 return entry;
}
