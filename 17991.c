GLES2Decoder* GLES2Decoder::Create(ContextGroup* group) {
  return new GLES2DecoderImpl(group);
}
