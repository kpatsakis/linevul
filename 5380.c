static void filter181(int16_t *data, int width, int height, ptrdiff_t stride)
{
    int x, y;

    /* horizontal filter */
    for (y = 1; y < height - 1; y++) {
        int prev_dc = data[0 + y * stride];

        for (x = 1; x < width - 1; x++) {
            int dc;
            dc = -prev_dc +
                 data[x     + y * stride] * 8 -
                 data[x + 1 + y * stride];
            dc = (av_clip(dc, INT_MIN/10923, INT_MAX/10923 - 32768) * 10923 + 32768) >> 16;
            prev_dc = data[x + y * stride];
            data[x + y * stride] = dc;
        }
    }

    /* vertical filter */
    for (x = 1; x < width - 1; x++) {
        int prev_dc = data[x];

        for (y = 1; y < height - 1; y++) {
            int dc;

            dc = -prev_dc +
                 data[x +  y      * stride] * 8 -
                 data[x + (y + 1) * stride];
            dc = (av_clip(dc, INT_MIN/10923, INT_MAX/10923 - 32768) * 10923 + 32768) >> 16;
            prev_dc = data[x + y * stride];
            data[x + y * stride] = dc;
        }
    }
}
