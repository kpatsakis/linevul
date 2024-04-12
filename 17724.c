error::Error GLES2DecoderImpl::HandleGetString(uint32_t immediate_data_size,
                                               const volatile void* cmd_data) {
  const volatile gles2::cmds::GetString& c =
      *static_cast<const volatile gles2::cmds::GetString*>(cmd_data);
  GLenum name = static_cast<GLenum>(c.name);
  if (!validators_->string_type.IsValid(name)) {
    LOCAL_SET_GL_ERROR_INVALID_ENUM("glGetString", name, "name");
    return error::kNoError;
  }

  const char* str = nullptr;
  std::string extensions;
  switch (name) {
    case GL_VERSION:
      str = GetServiceVersionString(feature_info_.get());
      break;
    case GL_SHADING_LANGUAGE_VERSION:
      str = GetServiceShadingLanguageVersionString(feature_info_.get());
      break;
    case GL_EXTENSIONS: {
      gfx::ExtensionSet extension_set = feature_info_->extensions();
      if (feature_info_->IsWebGLContext()) {
        if (!derivatives_explicitly_enabled_)
          extension_set.erase(kOESDerivativeExtension);
        if (!frag_depth_explicitly_enabled_)
          extension_set.erase(kEXTFragDepthExtension);
        if (!draw_buffers_explicitly_enabled_)
          extension_set.erase(kEXTDrawBuffersExtension);
        if (!shader_texture_lod_explicitly_enabled_)
          extension_set.erase(kEXTShaderTextureLodExtension);
        if (!multi_draw_explicitly_enabled_)
          extension_set.erase(kWEBGLMultiDrawExtension);
        if (!multi_draw_instanced_explicitly_enabled_)
          extension_set.erase(kWEBGLMultiDrawInstancedExtension);
      }
      if (supports_post_sub_buffer_)
        extension_set.insert("GL_CHROMIUM_post_sub_buffer");
      extensions = gfx::MakeExtensionString(extension_set);
      str = extensions.c_str();
      break;
    }
    default:
      str = reinterpret_cast<const char*>(api()->glGetStringFn(name));
      break;
  }
  Bucket* bucket = CreateBucket(c.bucket_id);
  bucket->SetFromString(str);
  return error::kNoError;
}
