int add_camera_metadata_entry(camera_metadata_t *dst,
 uint32_t tag,
 const void *data,
 size_t data_count) {

 int type = get_camera_metadata_tag_type(tag);
 if (type == -1) {
        ALOGE("%s: Unknown tag %04x.", __FUNCTION__, tag);
 return ERROR;
 }

 return add_camera_metadata_entry_raw(dst,
            tag,
            type,
            data,
            data_count);
}
