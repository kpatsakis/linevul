bool GLES2DecoderImpl::SimulateFixedAttribs(
    const char* function_name,
    GLuint max_vertex_accessed, bool* simulated, GLsizei primcount) {
  DCHECK(simulated);
  *simulated = false;
  if (gfx::GetGLImplementation() == gfx::kGLImplementationEGLGLES2)
    return true;

  if (!state_.vertex_attrib_manager->HaveFixedAttribs()) {
    return true;
  }

  LOCAL_PERFORMANCE_WARNING(
      "GL_FIXED attributes have a signficant performance penalty");


  GLuint elements_needed = 0;
  const VertexAttribManager::VertexAttribList& enabled_attribs =
      state_.vertex_attrib_manager->GetEnabledVertexAttribs();
  for (VertexAttribManager::VertexAttribList::const_iterator it =
       enabled_attribs.begin(); it != enabled_attribs.end(); ++it) {
    const VertexAttrib* attrib = *it;
    const Program::VertexAttrib* attrib_info =
        state_.current_program->GetAttribInfoByLocation(attrib->index());
    GLuint max_accessed = attrib->MaxVertexAccessed(primcount,
                                                    max_vertex_accessed);
    GLuint num_vertices = max_accessed + 1;
    if (num_vertices == 0) {
      LOCAL_SET_GL_ERROR(
          GL_OUT_OF_MEMORY, function_name, "Simulating attrib 0");
      return false;
    }
    if (attrib_info &&
        attrib->CanAccess(max_accessed) &&
        attrib->type() == GL_FIXED) {
      uint32 elements_used = 0;
      if (!SafeMultiplyUint32(num_vertices, attrib->size(), &elements_used) ||
          !SafeAddUint32(elements_needed, elements_used, &elements_needed)) {
        LOCAL_SET_GL_ERROR(
            GL_OUT_OF_MEMORY, function_name, "simulating GL_FIXED attribs");
        return false;
      }
    }
  }

  const uint32 kSizeOfFloat = sizeof(float);  // NOLINT
  uint32 size_needed = 0;
  if (!SafeMultiplyUint32(elements_needed, kSizeOfFloat, &size_needed) ||
      size_needed > 0x7FFFFFFFU) {
    LOCAL_SET_GL_ERROR(
        GL_OUT_OF_MEMORY, function_name, "simulating GL_FIXED attribs");
    return false;
  }

  LOCAL_COPY_REAL_GL_ERRORS_TO_WRAPPER(function_name);

  glBindBuffer(GL_ARRAY_BUFFER, fixed_attrib_buffer_id_);
  if (static_cast<GLsizei>(size_needed) > fixed_attrib_buffer_size_) {
    glBufferData(GL_ARRAY_BUFFER, size_needed, NULL, GL_DYNAMIC_DRAW);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
      LOCAL_SET_GL_ERROR(
          GL_OUT_OF_MEMORY, function_name, "simulating GL_FIXED attribs");
      return false;
    }
  }

  GLintptr offset = 0;
  for (VertexAttribManager::VertexAttribList::const_iterator it =
       enabled_attribs.begin(); it != enabled_attribs.end(); ++it) {
    const VertexAttrib* attrib = *it;
    const Program::VertexAttrib* attrib_info =
        state_.current_program->GetAttribInfoByLocation(attrib->index());
    GLuint max_accessed = attrib->MaxVertexAccessed(primcount,
                                                  max_vertex_accessed);
    GLuint num_vertices = max_accessed + 1;
    if (num_vertices == 0) {
      LOCAL_SET_GL_ERROR(
          GL_OUT_OF_MEMORY, function_name, "Simulating attrib 0");
      return false;
    }
    if (attrib_info &&
        attrib->CanAccess(max_accessed) &&
        attrib->type() == GL_FIXED) {
      int num_elements = attrib->size() * num_vertices;
      const int src_size = num_elements * sizeof(int32);
      const int dst_size = num_elements * sizeof(float);
      scoped_ptr<float[]> data(new float[num_elements]);
      const int32* src = reinterpret_cast<const int32 *>(
          attrib->buffer()->GetRange(attrib->offset(), src_size));
      const int32* end = src + num_elements;
      float* dst = data.get();
      while (src != end) {
        *dst++ = static_cast<float>(*src++) / 65536.0f;
      }
      glBufferSubData(GL_ARRAY_BUFFER, offset, dst_size, data.get());
      glVertexAttribPointer(
          attrib->index(), attrib->size(), GL_FLOAT, false, 0,
          reinterpret_cast<GLvoid*>(offset));
      offset += dst_size;
    }
  }
  *simulated = true;
  return true;
}
