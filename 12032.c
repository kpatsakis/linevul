ALWAYS_INLINE bool GLES2DecoderImpl::CheckMultiDrawElementsVertices(
    const char* function_name,
    bool instanced,
    const GLsizei* counts,
    GLenum type,
    const int32_t* offsets,
    const GLsizei* primcounts,
    GLsizei drawcount,
    Buffer* element_array_buffer,
    GLuint* total_max_vertex_accessed,
    GLsizei* total_max_primcount) {
  DCHECK_GE(drawcount, 0);
  for (GLsizei draw_id = 0; draw_id < drawcount; ++draw_id) {
    GLsizei count = counts[draw_id];
    GLsizei offset = offsets[draw_id];
    GLsizei primcount = instanced ? primcounts[draw_id] : 1;

    if (count < 0) {
      LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, function_name, "count < 0");
      return false;
    }
    if (offset < 0) {
      LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, function_name, "offset < 0");
      return false;
    }
    if (primcount < 0) {
      LOCAL_SET_GL_ERROR(GL_INVALID_VALUE, function_name, "primcount < 0");
      return false;
    }
    if (count == 0 || primcount == 0) {
      continue;
    }

    GLuint max_vertex_accessed;
    if (!element_array_buffer->GetMaxValueForRange(
            offset, count, type,
            state_.enable_flags.primitive_restart_fixed_index,
            &max_vertex_accessed)) {
      LOCAL_SET_GL_ERROR(GL_INVALID_OPERATION, function_name,
                         "range out of bounds for buffer");
      return false;
    }

    if (!IsDrawValid(function_name, max_vertex_accessed, instanced,
                     primcount)) {
      return false;
    }

    *total_max_vertex_accessed =
        std::max(*total_max_vertex_accessed, max_vertex_accessed);
    *total_max_primcount = std::max(*total_max_primcount, primcount);
  }
  return true;
}
