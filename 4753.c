DrawingBuffer::TextureColorBufferParameters() {
  ColorBufferParameters parameters;
  parameters.target = GL_TEXTURE_2D;
  if (want_alpha_channel_) {
    parameters.allocate_alpha_channel = true;
  } else if (ContextProvider()
                 ->GetCapabilities()
                 .emulate_rgb_buffer_with_rgba) {
    parameters.allocate_alpha_channel = true;
  } else {
    parameters.allocate_alpha_channel =
        DefaultBufferRequiresAlphaChannelToBePreserved();
  }
  return parameters;
}
