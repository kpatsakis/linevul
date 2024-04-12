int get_camera_metadata_entry(camera_metadata_t *src,
 size_t index,
 camera_metadata_entry_t *entry) {
 if (src == NULL || entry == NULL) return ERROR;
 if (index >= src->entry_count) return ERROR;

 camera_metadata_buffer_entry_t *buffer_entry = get_entries(src) + index;

    entry->index = index;
    entry->tag = buffer_entry->tag;
    entry->type = buffer_entry->type;
    entry->count = buffer_entry->count;
 if (buffer_entry->count *
            camera_metadata_type_size[buffer_entry->type] > 4) {
        entry->data.u8 = get_data(src) + buffer_entry->data.offset;
 } else {
        entry->data.u8 = buffer_entry->data.value;
 }
 return OK;
}
