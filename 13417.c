void dump_indented_camera_metadata(const camera_metadata_t *metadata,
 int fd,
 int verbosity,
 int indentation) {
 if (metadata == NULL) {
        dprintf(fd, "%*sDumping camera metadata array: Not allocated\n",
                indentation, "");
 return;
 }
 unsigned int i;
    dprintf(fd,
 "%*sDumping camera metadata array: %" PRIu32 " / %" PRIu32 " entries, "
 "%" PRIu32 " / %" PRIu32 " bytes of extra data.\n", indentation, "",
            metadata->entry_count, metadata->entry_capacity,
            metadata->data_count, metadata->data_capacity);
    dprintf(fd, "%*sVersion: %d, Flags: %08x\n",
            indentation + 2, "",
            metadata->version, metadata->flags);
 camera_metadata_buffer_entry_t *entry = get_entries(metadata);
 for (i=0; i < metadata->entry_count; i++, entry++) {

 const char *tag_name, *tag_section;
        tag_section = get_camera_metadata_section_name(entry->tag);
 if (tag_section == NULL) {
            tag_section = "unknownSection";
 }
        tag_name = get_camera_metadata_tag_name(entry->tag);
 if (tag_name == NULL) {
            tag_name = "unknownTag";
 }
 const char *type_name;
 if (entry->type >= NUM_TYPES) {
            type_name = "unknown";
 } else {
            type_name = camera_metadata_type_names[entry->type];
 }
        dprintf(fd, "%*s%s.%s (%05x): %s[%" PRIu32 "]\n",
             indentation + 2, "",
             tag_section,
             tag_name,
             entry->tag,
             type_name,
             entry->count);

 if (verbosity < 1) continue;

 if (entry->type >= NUM_TYPES) continue;

 size_t type_size = camera_metadata_type_size[entry->type];
 uint8_t *data_ptr;
 if ( type_size * entry->count > 4 ) {
 if (entry->data.offset >= metadata->data_count) {
                ALOGE("%s: Malformed entry data offset: %" PRIu32 " (max %" PRIu32 ")",
                        __FUNCTION__,
                        entry->data.offset,
                        metadata->data_count);
 continue;
 }
            data_ptr = get_data(metadata) + entry->data.offset;
 } else {
            data_ptr = entry->data.value;
 }
 int count = entry->count;
 if (verbosity < 2 && count > 16) count = 16;

        print_data(fd, data_ptr, entry->tag, entry->type, count, indentation);
 }
}
