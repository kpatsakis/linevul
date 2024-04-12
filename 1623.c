void GLES2DecoderImpl::DoMatrixLoadfCHROMIUM(GLenum matrix_mode,
                                             const volatile GLfloat* matrix) {
  DCHECK(matrix_mode == GL_PATH_PROJECTION_CHROMIUM ||
         matrix_mode == GL_PATH_MODELVIEW_CHROMIUM);

  GLfloat* target_matrix = matrix_mode == GL_PATH_PROJECTION_CHROMIUM
                               ? state_.projection_matrix
                               : state_.modelview_matrix;
  memcpy(target_matrix, const_cast<const GLfloat*>(matrix),
         sizeof(GLfloat) * 16);
  api()->glMatrixLoadfEXTFn(matrix_mode, target_matrix);
}
