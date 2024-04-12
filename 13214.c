static int swap_frame_buffers (VP8_COMMON *cm)
{
 int err = 0;

 /* The alternate reference frame or golden frame can be updated
     *  using the new, last, or golden/alt ref frame.  If it
     *  is updated using the newly decoded frame it is a refresh.
     *  An update using the last or golden/alt ref frame is a copy.
     */
 if (cm->copy_buffer_to_arf)
 {
 int new_fb = 0;

 if (cm->copy_buffer_to_arf == 1)
            new_fb = cm->lst_fb_idx;
 else if (cm->copy_buffer_to_arf == 2)
            new_fb = cm->gld_fb_idx;
 else
            err = -1;

        ref_cnt_fb (cm->fb_idx_ref_cnt, &cm->alt_fb_idx, new_fb);
 }

 if (cm->copy_buffer_to_gf)
 {
 int new_fb = 0;

 if (cm->copy_buffer_to_gf == 1)
            new_fb = cm->lst_fb_idx;
 else if (cm->copy_buffer_to_gf == 2)
            new_fb = cm->alt_fb_idx;
 else
            err = -1;

        ref_cnt_fb (cm->fb_idx_ref_cnt, &cm->gld_fb_idx, new_fb);
 }

 if (cm->refresh_golden_frame)
        ref_cnt_fb (cm->fb_idx_ref_cnt, &cm->gld_fb_idx, cm->new_fb_idx);

 if (cm->refresh_alt_ref_frame)
        ref_cnt_fb (cm->fb_idx_ref_cnt, &cm->alt_fb_idx, cm->new_fb_idx);

 if (cm->refresh_last_frame)
 {
        ref_cnt_fb (cm->fb_idx_ref_cnt, &cm->lst_fb_idx, cm->new_fb_idx);

        cm->frame_to_show = &cm->yv12_fb[cm->lst_fb_idx];
 }
 else
        cm->frame_to_show = &cm->yv12_fb[cm->new_fb_idx];

    cm->fb_idx_ref_cnt[cm->new_fb_idx]--;

 return err;
}
