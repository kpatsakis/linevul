int update_camera_metadata_entry(camera_metadata_t *dst,
 size_t index,
 const void *data,
 size_t data_count,
 camera_metadata_entry_t *updated_entry) {
 if (dst == NULL) return ERROR;
 if (index >= dst->entry_count) return ERROR;

 camera_metadata_buffer_entry_t *entry = get_entries(dst) + index;

 size_t data_bytes =
            calculate_camera_metadata_entry_data_size(entry->type,
                    data_count);
 size_t data_payload_bytes =
            data_count * camera_metadata_type_size[entry->type];

 size_t entry_bytes =
            calculate_camera_metadata_entry_data_size(entry->type,
                    entry->count);
 if (data_bytes != entry_bytes) {
 if (dst->data_capacity < dst->data_count + data_bytes - entry_bytes) {
 return ERROR;
 }
 if (entry_bytes != 0) {
 uint8_t *start = get_data(dst) + entry->data.offset;
 uint8_t *end = start + entry_bytes;
 size_t length = dst->data_count - entry->data.offset - entry_bytes;
            memmove(start, end, length);
            dst->data_count -= entry_bytes;

 camera_metadata_buffer_entry_t *e = get_entries(dst);
 size_t i;
 for (i = 0; i < dst->entry_count; i++) {
 if (calculate_camera_metadata_entry_data_size(
                        e->type, e->count) > 0 &&
                        e->data.offset > entry->data.offset) {
                    e->data.offset -= entry_bytes;
 }
 ++e;
 }
 }

 if (data_bytes != 0) {
            entry->data.offset = dst->data_count;

            memcpy(get_data(dst) + entry->data.offset, data, data_payload_bytes);
            dst->data_count += data_bytes;
 }
 } else if (data_bytes != 0) {
        memcpy(get_data(dst) + entry->data.offset, data, data_payload_bytes);
 }

 if (data_bytes == 0) {
        memcpy(entry->data.value, data,
                data_payload_bytes);
 }

    entry->count = data_count;

 if (updated_entry != NULL) {
        get_camera_metadata_entry(dst,
                index,
                updated_entry);
 }

    assert(validate_camera_metadata_structure(dst, NULL) == OK);
 return OK;
}
