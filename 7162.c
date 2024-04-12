ScriptValue WebGLRenderingContextBase::getUniform(
    ScriptState* script_state,
    WebGLProgram* program,
    const WebGLUniformLocation* uniform_location) {
  if (isContextLost() || !ValidateWebGLObject("getUniform", program))
    return ScriptValue::CreateNull(script_state);
  DCHECK(uniform_location);
  if (uniform_location->Program() != program) {
    SynthesizeGLError(GL_INVALID_OPERATION, "getUniform",
                      "no uniformlocation or not valid for this program");
    return ScriptValue::CreateNull(script_state);
  }
  GLint location = uniform_location->Location();

  GLuint program_id = ObjectNonZero(program);
  GLint max_name_length = -1;
  ContextGL()->GetProgramiv(program_id, GL_ACTIVE_UNIFORM_MAX_LENGTH,
                            &max_name_length);
  if (max_name_length < 0)
    return ScriptValue::CreateNull(script_state);
  if (max_name_length == 0) {
    SynthesizeGLError(GL_INVALID_VALUE, "getUniform",
                      "no active uniforms exist");
    return ScriptValue::CreateNull(script_state);
  }

  GLint active_uniforms = 0;
  ContextGL()->GetProgramiv(program_id, GL_ACTIVE_UNIFORMS, &active_uniforms);
  for (GLint i = 0; i < active_uniforms; i++) {
    LChar* name_ptr;
    scoped_refptr<StringImpl> name_impl =
        StringImpl::CreateUninitialized(max_name_length, name_ptr);
    GLsizei length = 0;
    GLint size = -1;
    GLenum type = 0;
    ContextGL()->GetActiveUniform(program_id, i, max_name_length, &length,
                                  &size, &type,
                                  reinterpret_cast<GLchar*>(name_ptr));
    if (size < 0)
      return ScriptValue::CreateNull(script_state);
    String name(name_impl->Substring(0, length));
    StringBuilder name_builder;
    if (size > 1 && name.EndsWith("[0]"))
      name = name.Left(name.length() - 3);
    for (GLint index = 0; index < size; ++index) {
      name_builder.Clear();
      name_builder.Append(name);
      if (size > 1 && index >= 1) {
        name_builder.Append('[');
        name_builder.AppendNumber(index);
        name_builder.Append(']');
      }
      GLint loc = ContextGL()->GetUniformLocation(
          ObjectOrZero(program), name_builder.ToString().Utf8().data());
      if (loc == location) {
        GLenum base_type;
        unsigned length;
        switch (type) {
          case GL_BOOL:
            base_type = GL_BOOL;
            length = 1;
            break;
          case GL_BOOL_VEC2:
            base_type = GL_BOOL;
            length = 2;
            break;
          case GL_BOOL_VEC3:
            base_type = GL_BOOL;
            length = 3;
            break;
          case GL_BOOL_VEC4:
            base_type = GL_BOOL;
            length = 4;
            break;
          case GL_INT:
            base_type = GL_INT;
            length = 1;
            break;
          case GL_INT_VEC2:
            base_type = GL_INT;
            length = 2;
            break;
          case GL_INT_VEC3:
            base_type = GL_INT;
            length = 3;
            break;
          case GL_INT_VEC4:
            base_type = GL_INT;
            length = 4;
            break;
          case GL_FLOAT:
            base_type = GL_FLOAT;
            length = 1;
            break;
          case GL_FLOAT_VEC2:
            base_type = GL_FLOAT;
            length = 2;
            break;
          case GL_FLOAT_VEC3:
            base_type = GL_FLOAT;
            length = 3;
            break;
          case GL_FLOAT_VEC4:
            base_type = GL_FLOAT;
            length = 4;
            break;
          case GL_FLOAT_MAT2:
            base_type = GL_FLOAT;
            length = 4;
            break;
          case GL_FLOAT_MAT3:
            base_type = GL_FLOAT;
            length = 9;
            break;
          case GL_FLOAT_MAT4:
            base_type = GL_FLOAT;
            length = 16;
            break;
          case GL_SAMPLER_2D:
          case GL_SAMPLER_CUBE:
            base_type = GL_INT;
            length = 1;
            break;
          default:
            if (!IsWebGL2OrHigher()) {
              SynthesizeGLError(GL_INVALID_VALUE, "getUniform",
                                "unhandled type");
              return ScriptValue::CreateNull(script_state);
            }
            switch (type) {
              case GL_UNSIGNED_INT:
                base_type = GL_UNSIGNED_INT;
                length = 1;
                break;
              case GL_UNSIGNED_INT_VEC2:
                base_type = GL_UNSIGNED_INT;
                length = 2;
                break;
              case GL_UNSIGNED_INT_VEC3:
                base_type = GL_UNSIGNED_INT;
                length = 3;
                break;
              case GL_UNSIGNED_INT_VEC4:
                base_type = GL_UNSIGNED_INT;
                length = 4;
                break;
              case GL_FLOAT_MAT2x3:
                base_type = GL_FLOAT;
                length = 6;
                break;
              case GL_FLOAT_MAT2x4:
                base_type = GL_FLOAT;
                length = 8;
                break;
              case GL_FLOAT_MAT3x2:
                base_type = GL_FLOAT;
                length = 6;
                break;
              case GL_FLOAT_MAT3x4:
                base_type = GL_FLOAT;
                length = 12;
                break;
              case GL_FLOAT_MAT4x2:
                base_type = GL_FLOAT;
                length = 8;
                break;
              case GL_FLOAT_MAT4x3:
                base_type = GL_FLOAT;
                length = 12;
                break;
              case GL_SAMPLER_3D:
              case GL_SAMPLER_2D_ARRAY:
              case GL_SAMPLER_2D_SHADOW:
              case GL_SAMPLER_CUBE_SHADOW:
              case GL_SAMPLER_2D_ARRAY_SHADOW:
              case GL_INT_SAMPLER_2D:
              case GL_INT_SAMPLER_CUBE:
              case GL_INT_SAMPLER_3D:
              case GL_INT_SAMPLER_2D_ARRAY:
              case GL_UNSIGNED_INT_SAMPLER_2D:
              case GL_UNSIGNED_INT_SAMPLER_CUBE:
              case GL_UNSIGNED_INT_SAMPLER_3D:
              case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
                base_type = GL_INT;
                length = 1;
                break;
              default:
                SynthesizeGLError(GL_INVALID_VALUE, "getUniform",
                                  "unhandled type");
                return ScriptValue::CreateNull(script_state);
            }
        }
        switch (base_type) {
          case GL_FLOAT: {
            GLfloat value[16] = {0};
            ContextGL()->GetUniformfv(ObjectOrZero(program), location, value);
            if (length == 1)
              return WebGLAny(script_state, value[0]);
            return WebGLAny(script_state,
                            DOMFloat32Array::Create(value, length));
          }
          case GL_INT: {
            GLint value[4] = {0};
            ContextGL()->GetUniformiv(ObjectOrZero(program), location, value);
            if (length == 1)
              return WebGLAny(script_state, value[0]);
            return WebGLAny(script_state, DOMInt32Array::Create(value, length));
          }
          case GL_UNSIGNED_INT: {
            GLuint value[4] = {0};
            ContextGL()->GetUniformuiv(ObjectOrZero(program), location, value);
            if (length == 1)
              return WebGLAny(script_state, value[0]);
            return WebGLAny(script_state,
                            DOMUint32Array::Create(value, length));
          }
          case GL_BOOL: {
            GLint value[4] = {0};
            ContextGL()->GetUniformiv(ObjectOrZero(program), location, value);
            if (length > 1) {
              bool bool_value[16] = {0};
              for (unsigned j = 0; j < length; j++)
                bool_value[j] = static_cast<bool>(value[j]);
              return WebGLAny(script_state, bool_value, length);
            }
            return WebGLAny(script_state, static_cast<bool>(value[0]));
          }
          default:
            NOTIMPLEMENTED();
        }
      }
    }
  }
  SynthesizeGLError(GL_INVALID_VALUE, "getUniform", "unknown error");
  return ScriptValue::CreateNull(script_state);
}
