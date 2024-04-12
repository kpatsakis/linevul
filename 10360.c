const SamplerState& GLES2DecoderImpl::GetSamplerStateForTextureUnit(
    GLenum target, GLuint unit) {
  if (features().enable_samplers) {
    Sampler* sampler = state_.sampler_units[unit].get();
    if (sampler)
      return sampler->sampler_state();
  }
  TextureUnit& texture_unit = state_.texture_units[unit];
  TextureRef* texture_ref = texture_unit.GetInfoForSamplerType(target);
  if (texture_ref)
    return texture_ref->texture()->sampler_state();

  return default_sampler_state_;
}
