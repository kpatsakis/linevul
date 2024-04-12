 virtual void BeginPassHook(unsigned int /*pass*/) {
#if WRITE_COMPRESSED_STREAM
    outfile_ = fopen("vp90-2-05-resize.ivf", "wb");
#endif
 }
