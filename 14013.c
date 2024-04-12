static HuffReader *get_huffman_group(WebPContext *s, ImageContext *img,
                                     int x, int y)
{
    ImageContext *gimg = &s->image[IMAGE_ROLE_ENTROPY];
    int group = 0;

    if (gimg->size_reduction > 0) {
        int group_x = x >> gimg->size_reduction;
        int group_y = y >> gimg->size_reduction;
        int g0      = GET_PIXEL_COMP(gimg->frame, group_x, group_y, 1);
        int g1      = GET_PIXEL_COMP(gimg->frame, group_x, group_y, 2);
        group       = g0 << 8 | g1;
    }

    return &img->huffman_groups[group * HUFFMAN_CODES_PER_META_CODE];
}
