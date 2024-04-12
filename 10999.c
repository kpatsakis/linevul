static void ref_cnt_fb (int *buf, int *idx, int new_idx)
{
 if (buf[*idx] > 0)
        buf[*idx]--;

 *idx = new_idx;

    buf[new_idx]++;
}
