 virtual void FramePktHook(const vpx_codec_cx_pkt_t *pkt) {
    file_size_ += pkt->data.frame.sz;
 }
