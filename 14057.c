void read_frame_header(decoder_info_t *dec_info, stream_t *stream) {
  frame_info_t *frame_info = &dec_info->frame_info;
  frame_info->frame_type = get_flc(1, stream);
  frame_info->qp = get_flc(8, stream);
  frame_info->num_intra_modes = get_flc(4, stream);
  if (frame_info->frame_type != I_FRAME) {
    frame_info->num_ref = get_flc(2, stream) + 1;
    int r;
    for (r = 0; r < frame_info->num_ref; r++) {
      frame_info->ref_array[r] = get_flc(6, stream) - 1;
    }
    if (frame_info->num_ref == 2 && frame_info->ref_array[0] == -1) {
      frame_info->ref_array[frame_info->num_ref++] = get_flc(5, stream) - 1;
    }
  }
  else {
    frame_info->num_ref = 0;
  }
  frame_info->display_frame_num = get_flc(16, stream);

#if CDEF
  dec_info->cdef_damping[1] = dec_info->cdef_damping[0] = get_flc(2, stream) + 3;
  dec_info->cdef_bits = get_flc(2, stream);

  for (int i = 0; i < (1 << dec_info->cdef_bits); i++) {
    dec_info->cdef_presets[i].pri_strength[0] = get_flc(4, stream);
    dec_info->cdef_presets[i].skip_condition[0] = get_flc(1, stream);
    dec_info->cdef_presets[i].sec_strength[0] = get_flc(2, stream);
    if (dec_info->subsample != 400) {
      dec_info->cdef_presets[i].pri_strength[1] = get_flc(4, stream);
      dec_info->cdef_presets[i].skip_condition[1] = get_flc(1, stream);
      dec_info->cdef_presets[i].sec_strength[1] = get_flc(2, stream);
    }
  }
#endif
}
