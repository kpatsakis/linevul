ScriptValue WebGL2RenderingContextBase::getParameter(ScriptState* script_state,
                                                     GLenum pname) {
  if (isContextLost())
    return ScriptValue::CreateNull(script_state);
  switch (pname) {
    case GL_SHADING_LANGUAGE_VERSION: {
      return WebGLAny(
          script_state,
          "WebGL GLSL ES 3.00 (" +
              String(ContextGL()->GetString(GL_SHADING_LANGUAGE_VERSION)) +
              ")");
    }
    case GL_VERSION:
      return WebGLAny(
          script_state,
          "WebGL 2.0 (" + String(ContextGL()->GetString(GL_VERSION)) + ")");

    case GL_COPY_READ_BUFFER_BINDING:
      return WebGLAny(script_state, bound_copy_read_buffer_.Get());
    case GL_COPY_WRITE_BUFFER_BINDING:
      return WebGLAny(script_state, bound_copy_write_buffer_.Get());
    case GL_DRAW_FRAMEBUFFER_BINDING:
      return WebGLAny(script_state, framebuffer_binding_.Get());
    case GL_FRAGMENT_SHADER_DERIVATIVE_HINT:
      return GetUnsignedIntParameter(script_state, pname);
    case GL_MAX_3D_TEXTURE_SIZE:
      return GetIntParameter(script_state, pname);
    case GL_MAX_ARRAY_TEXTURE_LAYERS:
      return GetIntParameter(script_state, pname);
    case GC3D_MAX_CLIENT_WAIT_TIMEOUT_WEBGL:
      return WebGLAny(script_state, kMaxClientWaitTimeout);
    case GL_MAX_COLOR_ATTACHMENTS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_COMBINED_FRAGMENT_UNIFORM_COMPONENTS:
      return GetInt64Parameter(script_state, pname);
    case GL_MAX_COMBINED_UNIFORM_BLOCKS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_COMBINED_VERTEX_UNIFORM_COMPONENTS:
      return GetInt64Parameter(script_state, pname);
    case GL_MAX_DRAW_BUFFERS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_ELEMENT_INDEX:
      return GetInt64Parameter(script_state, pname);
    case GL_MAX_ELEMENTS_INDICES:
      return GetIntParameter(script_state, pname);
    case GL_MAX_ELEMENTS_VERTICES:
      return GetIntParameter(script_state, pname);
    case GL_MAX_FRAGMENT_INPUT_COMPONENTS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_FRAGMENT_UNIFORM_BLOCKS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_FRAGMENT_UNIFORM_COMPONENTS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_PROGRAM_TEXEL_OFFSET:
      return GetIntParameter(script_state, pname);
    case GL_MAX_SAMPLES:
      return GetIntParameter(script_state, pname);
    case GL_MAX_SERVER_WAIT_TIMEOUT:
      return GetInt64Parameter(script_state, pname);
    case GL_MAX_TEXTURE_LOD_BIAS:
      return GetFloatParameter(script_state, pname);
    case GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_UNIFORM_BLOCK_SIZE:
      return GetInt64Parameter(script_state, pname);
    case GL_MAX_UNIFORM_BUFFER_BINDINGS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_VARYING_COMPONENTS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_VERTEX_OUTPUT_COMPONENTS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_VERTEX_UNIFORM_BLOCKS:
      return GetIntParameter(script_state, pname);
    case GL_MAX_VERTEX_UNIFORM_COMPONENTS:
      return GetIntParameter(script_state, pname);
    case GL_MIN_PROGRAM_TEXEL_OFFSET:
      return GetIntParameter(script_state, pname);
    case GL_PACK_ROW_LENGTH:
      return GetIntParameter(script_state, pname);
    case GL_PACK_SKIP_PIXELS:
      return GetIntParameter(script_state, pname);
    case GL_PACK_SKIP_ROWS:
      return GetIntParameter(script_state, pname);
    case GL_PIXEL_PACK_BUFFER_BINDING:
      return WebGLAny(script_state, bound_pixel_pack_buffer_.Get());
    case GL_PIXEL_UNPACK_BUFFER_BINDING:
      return WebGLAny(script_state, bound_pixel_unpack_buffer_.Get());
    case GL_RASTERIZER_DISCARD:
      return GetBooleanParameter(script_state, pname);
    case GL_READ_BUFFER: {
      GLenum value = 0;
      if (!isContextLost()) {
        WebGLFramebuffer* read_framebuffer_binding =
            GetFramebufferBinding(GL_READ_FRAMEBUFFER);
        if (!read_framebuffer_binding)
          value = read_buffer_of_default_framebuffer_;
        else
          value = read_framebuffer_binding->GetReadBuffer();
      }
      return WebGLAny(script_state, value);
    }
    case GL_READ_FRAMEBUFFER_BINDING:
      return WebGLAny(script_state, read_framebuffer_binding_.Get());
    case GL_SAMPLER_BINDING:
      return WebGLAny(script_state, sampler_units_[active_texture_unit_].Get());
    case GL_TEXTURE_BINDING_2D_ARRAY:
      return WebGLAny(
          script_state,
          texture_units_[active_texture_unit_].texture2d_array_binding_.Get());
    case GL_TEXTURE_BINDING_3D:
      return WebGLAny(
          script_state,
          texture_units_[active_texture_unit_].texture3d_binding_.Get());
    case GL_TRANSFORM_FEEDBACK_ACTIVE:
      return GetBooleanParameter(script_state, pname);
    case GL_TRANSFORM_FEEDBACK_BUFFER_BINDING:
      return WebGLAny(
          script_state,
          transform_feedback_binding_->GetBoundTransformFeedbackBuffer());
    case GL_TRANSFORM_FEEDBACK_BINDING:
      if (!transform_feedback_binding_->IsDefaultObject()) {
        return WebGLAny(script_state, transform_feedback_binding_.Get());
      }
      return ScriptValue::CreateNull(script_state);
    case GL_TRANSFORM_FEEDBACK_PAUSED:
      return GetBooleanParameter(script_state, pname);
    case GL_UNIFORM_BUFFER_BINDING:
      return WebGLAny(script_state, bound_uniform_buffer_.Get());
    case GL_UNIFORM_BUFFER_OFFSET_ALIGNMENT:
      return GetIntParameter(script_state, pname);
    case GL_UNPACK_IMAGE_HEIGHT:
      return GetIntParameter(script_state, pname);
    case GL_UNPACK_ROW_LENGTH:
      return GetIntParameter(script_state, pname);
    case GL_UNPACK_SKIP_IMAGES:
      return GetIntParameter(script_state, pname);
    case GL_UNPACK_SKIP_PIXELS:
      return GetIntParameter(script_state, pname);
    case GL_UNPACK_SKIP_ROWS:
      return GetIntParameter(script_state, pname);
    case GL_TIMESTAMP_EXT:
      if (ExtensionEnabled(kEXTDisjointTimerQueryWebGL2Name)) {
        return WebGLAny(script_state, 0);
      }
      SynthesizeGLError(GL_INVALID_ENUM, "getParameter",
                        "invalid parameter name, "
                        "EXT_disjoint_timer_query_webgl2 not enabled");
      return ScriptValue::CreateNull(script_state);
    case GL_GPU_DISJOINT_EXT:
      if (ExtensionEnabled(kEXTDisjointTimerQueryWebGL2Name)) {
        return GetBooleanParameter(script_state, GL_GPU_DISJOINT_EXT);
      }
      SynthesizeGLError(GL_INVALID_ENUM, "getParameter",
                        "invalid parameter name, "
                        "EXT_disjoint_timer_query_webgl2 not enabled");
      return ScriptValue::CreateNull(script_state);

    default:
      return WebGLRenderingContextBase::getParameter(script_state, pname);
  }
}
