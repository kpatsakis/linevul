status_t OMXCodec::allocateBuffers() {
 status_t err = allocateBuffersOnPort(kPortIndexInput);

 if (err != OK) {
 return err;
 }

 return allocateBuffersOnPort(kPortIndexOutput);
}
