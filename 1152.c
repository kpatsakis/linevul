void vp8mt_alloc_temp_buffers(VP8D_COMP *pbi, int width, int prev_mb_rows)
{
    VP8_COMMON *const pc = & pbi->common;
 int i;
 int uv_width;

 if (pbi->b_multithreaded_rd)
 {
        vp8mt_de_alloc_temp_buffers(pbi, prev_mb_rows);

 /* our internal buffers are always multiples of 16 */
 if ((width & 0xf) != 0)
            width += 16 - (width & 0xf);

 if (width < 640) pbi->sync_range = 1;
 else if (width <= 1280) pbi->sync_range = 8;
 else if (width <= 2560) pbi->sync_range =16;
 else pbi->sync_range = 32;

        uv_width = width >>1;

 /* Allocate an int for each mb row. */
        CALLOC_ARRAY(pbi->mt_current_mb_col, pc->mb_rows);

 /* Allocate memory for above_row buffers. */
        CALLOC_ARRAY(pbi->mt_yabove_row, pc->mb_rows);
 for (i = 0; i < pc->mb_rows; i++)
            CHECK_MEM_ERROR(pbi->mt_yabove_row[i], vpx_memalign(16,sizeof(unsigned char) * (width + (VP8BORDERINPIXELS<<1))));

        CALLOC_ARRAY(pbi->mt_uabove_row, pc->mb_rows);
 for (i = 0; i < pc->mb_rows; i++)
            CHECK_MEM_ERROR(pbi->mt_uabove_row[i], vpx_memalign(16,sizeof(unsigned char) * (uv_width + VP8BORDERINPIXELS)));

        CALLOC_ARRAY(pbi->mt_vabove_row, pc->mb_rows);
 for (i = 0; i < pc->mb_rows; i++)
            CHECK_MEM_ERROR(pbi->mt_vabove_row[i], vpx_memalign(16,sizeof(unsigned char) * (uv_width + VP8BORDERINPIXELS)));

 /* Allocate memory for left_col buffers. */
        CALLOC_ARRAY(pbi->mt_yleft_col, pc->mb_rows);
 for (i = 0; i < pc->mb_rows; i++)
            CHECK_MEM_ERROR(pbi->mt_yleft_col[i], vpx_calloc(sizeof(unsigned char) * 16, 1));

        CALLOC_ARRAY(pbi->mt_uleft_col, pc->mb_rows);
 for (i = 0; i < pc->mb_rows; i++)
            CHECK_MEM_ERROR(pbi->mt_uleft_col[i], vpx_calloc(sizeof(unsigned char) * 8, 1));

        CALLOC_ARRAY(pbi->mt_vleft_col, pc->mb_rows);
 for (i = 0; i < pc->mb_rows; i++)
            CHECK_MEM_ERROR(pbi->mt_vleft_col[i], vpx_calloc(sizeof(unsigned char) * 8, 1));
 }

 }
