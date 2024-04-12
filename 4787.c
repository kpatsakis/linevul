static uint8_t *get_data(const camera_metadata_t *metadata) {
 return (uint8_t*)metadata + metadata->data_start;
}
