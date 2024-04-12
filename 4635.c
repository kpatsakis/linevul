static section_t *section_new(const char *name) {
 section_t *section = osi_calloc(sizeof(section_t));
 if (!section)
 return NULL;

  section->name = osi_strdup(name);
  section->entries = list_new(entry_free);
 return section;
}
