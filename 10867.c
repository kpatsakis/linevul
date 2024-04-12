static void fill_block8_c(uint8_t *block, uint8_t value, int line_size, int h)
{
    int i;

    for (i = 0; i < h; i++) {
        memset(block, value, 8);
        block += line_size;
    }
}
