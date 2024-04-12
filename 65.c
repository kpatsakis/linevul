void show_rate_histogram(struct rate_hist *hist,
 const vpx_codec_enc_cfg_t *cfg, int max_buckets) {
 int i, scale;
 int buckets = 0;

 for (i = 0; i < RATE_BINS; i++) {
 if (hist->bucket[i].low == INT_MAX)
 continue;
    hist->bucket[buckets++] = hist->bucket[i];
 }

  fprintf(stderr, "\nRate (over %dms window):\n", cfg->rc_buf_sz);
  scale = merge_hist_buckets(hist->bucket, max_buckets, &buckets);
  show_histogram(hist->bucket, buckets, hist->total, scale);
}
