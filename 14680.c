void vpx_img_flip(vpx_image_t *img) {
 /* Note: In the calculation pointer adjustment calculation, we want the
   * rhs to be promoted to a signed type. Section 6.3.1.8 of the ISO C99
   * standard indicates that if the adjustment parameter is unsigned, the
   * stride parameter will be promoted to unsigned, causing errors when
   * the lhs is a larger type than the rhs.
   */
  img->planes[VPX_PLANE_Y] += (signed)(img->d_h - 1) * img->stride[VPX_PLANE_Y];
  img->stride[VPX_PLANE_Y] = -img->stride[VPX_PLANE_Y];

  img->planes[VPX_PLANE_U] += (signed)((img->d_h >> img->y_chroma_shift) - 1) *
                              img->stride[VPX_PLANE_U];
  img->stride[VPX_PLANE_U] = -img->stride[VPX_PLANE_U];

  img->planes[VPX_PLANE_V] += (signed)((img->d_h >> img->y_chroma_shift) - 1) *
                              img->stride[VPX_PLANE_V];
  img->stride[VPX_PLANE_V] = -img->stride[VPX_PLANE_V];

  img->planes[VPX_PLANE_ALPHA] +=
 (signed)(img->d_h - 1) * img->stride[VPX_PLANE_ALPHA];
  img->stride[VPX_PLANE_ALPHA] = -img->stride[VPX_PLANE_ALPHA];
}
