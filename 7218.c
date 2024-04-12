GLenum GLES2DecoderImpl::AdjustGetPname(GLenum pname) {
  if (GL_MAX_SAMPLES == pname &&
      features().use_img_for_multisampled_render_to_texture) {
    return GL_MAX_SAMPLES_IMG;
  }
  if (GL_ALIASED_POINT_SIZE_RANGE == pname &&
      gl_version_info().is_desktop_core_profile) {
    return GL_POINT_SIZE_RANGE;
  }
  return pname;
}
