static void put_mspel8_mc32_c(uint8_t *dst, uint8_t *src, ptrdiff_t stride)
{
    uint8_t halfH[88];
    uint8_t halfV[64];
    uint8_t halfHV[64];
    wmv2_mspel8_h_lowpass(halfH, src-stride, 8, stride, 11);
    wmv2_mspel8_v_lowpass(halfV, src+1, 8, stride, 8);
    wmv2_mspel8_v_lowpass(halfHV, halfH+8, 8, 8, 8);
    put_pixels8_l2_8(dst, halfV, halfHV, stride, 8, 8, 8);
}
