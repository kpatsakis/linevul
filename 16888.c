bool GLES2DecoderImpl::Initialize(
    const scoped_refptr<gfx::GLSurface>& surface,
    const scoped_refptr<gfx::GLContext>& context,
    bool offscreen,
    const gfx::Size& size,
    const DisallowedFeatures& disallowed_features,
    const char* allowed_extensions,
    const std::vector<int32>& attribs) {
  TRACE_EVENT0("gpu", "GLES2DecoderImpl::Initialize");
  DCHECK(context->IsCurrent(surface.get()));
  DCHECK(!context_.get());

  if (CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kEnableGPUDebugging)) {
    set_debug(true);
  }

  if (CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kEnableGPUCommandLogging)) {
    set_log_commands(true);
  }

  compile_shader_always_succeeds_ = CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kCompileShaderAlwaysSucceeds);


  context_ = context;
  surface_ = surface;

  if (!group_->Initialize(disallowed_features, allowed_extensions)) {
    LOG(ERROR) << "GpuScheduler::InitializeCommon failed because group "
               << "failed to initialize.";
    group_ = NULL;  // Must not destroy ContextGroup if it is not initialized.
    Destroy(true);
    return false;
  }
  CHECK_GL_ERROR();

  disallowed_features_ = disallowed_features;

  vertex_attrib_manager_.reset(new VertexAttribManager());
  vertex_attrib_manager_->Initialize(group_->max_vertex_attribs());

  query_manager_.reset(new QueryManager(this, feature_info_));

  util_.set_num_compressed_texture_formats(
      validators_->compressed_texture_format.GetValues().size());

  if (gfx::GetGLImplementation() != gfx::kGLImplementationEGLGLES2) {
    glEnableVertexAttribArray(0);
  }
  glGenBuffersARB(1, &attrib_0_buffer_id_);
  glBindBuffer(GL_ARRAY_BUFFER, attrib_0_buffer_id_);
  glVertexAttribPointer(0, 1, GL_FLOAT, GL_FALSE, 0, NULL);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glGenBuffersARB(1, &fixed_attrib_buffer_id_);

  texture_units_.reset(
      new TextureUnit[group_->max_texture_units()]);
  for (uint32 tt = 0; tt < group_->max_texture_units(); ++tt) {
    glActiveTexture(GL_TEXTURE0 + tt);
    TextureManager::TextureInfo* info;
    if (feature_info_->feature_flags().oes_egl_image_external) {
      info = texture_manager()->GetDefaultTextureInfo(GL_TEXTURE_EXTERNAL_OES);
      texture_units_[tt].bound_texture_external_oes = info;
      glBindTexture(GL_TEXTURE_EXTERNAL_OES, info->service_id());
    }
    if (feature_info_->feature_flags().arb_texture_rectangle) {
      info = texture_manager()->GetDefaultTextureInfo(GL_TEXTURE_RECTANGLE_ARB);
      texture_units_[tt].bound_texture_rectangle_arb = info;
      glBindTexture(GL_TEXTURE_RECTANGLE_ARB, info->service_id());
    }
    info = texture_manager()->GetDefaultTextureInfo(GL_TEXTURE_CUBE_MAP);
    texture_units_[tt].bound_texture_cube_map = info;
    glBindTexture(GL_TEXTURE_CUBE_MAP, info->service_id());
    info = texture_manager()->GetDefaultTextureInfo(GL_TEXTURE_2D);
    texture_units_[tt].bound_texture_2d = info;
    glBindTexture(GL_TEXTURE_2D, info->service_id());
  }
  glActiveTexture(GL_TEXTURE0);
  CHECK_GL_ERROR();

  ContextCreationAttribParser attrib_parser;
  if (!attrib_parser.Parse(attribs))
    return false;


  GLint v = 0;
  glGetIntegerv(GL_ALPHA_BITS, &v);
  back_buffer_color_format_ =
      (attrib_parser.alpha_size_ != 0 && v > 0) ? GL_RGBA : GL_RGB;
  glGetIntegerv(GL_DEPTH_BITS, &v);
  back_buffer_has_depth_ = attrib_parser.depth_size_ != 0 && v > 0;
  glGetIntegerv(GL_STENCIL_BITS, &v);
  back_buffer_has_stencil_ = attrib_parser.stencil_size_ != 0 && v > 0;

  if (offscreen) {
    if (attrib_parser.samples_ > 0 && attrib_parser.sample_buffers_ > 0 &&
        (context_->HasExtension("GL_EXT_framebuffer_multisample") ||
         context_->HasExtension("GL_ANGLE_framebuffer_multisample"))) {
      GLint max_sample_count = 1;
      glGetIntegerv(GL_MAX_SAMPLES_EXT, &max_sample_count);
      offscreen_target_samples_ = std::min(attrib_parser.samples_,
                                           max_sample_count);
    } else {
      offscreen_target_samples_ = 1;
    }
    offscreen_target_buffer_preserved_ = attrib_parser.buffer_preserved_;

    if (gfx::GetGLImplementation() == gfx::kGLImplementationEGLGLES2) {
      const bool rgb8_supported =
          context_->HasExtension("GL_OES_rgb8_rgba8");
      if (rgb8_supported && offscreen_target_samples_ > 1) {
        offscreen_target_color_format_ = attrib_parser.alpha_size_ > 0 ?
            GL_RGBA8 : GL_RGB8;
      } else {
        offscreen_target_samples_ = 1;
        offscreen_target_color_format_ = attrib_parser.alpha_size_ > 0 ?
            GL_RGBA : GL_RGB;
      }

      const bool depth24_stencil8_supported =
          context_->HasExtension("GL_OES_packed_depth_stencil");
      VLOG(1) << "GL_OES_packed_depth_stencil "
              << (depth24_stencil8_supported ? "" : "not ") << "supported.";
      if ((attrib_parser.depth_size_ > 0 || attrib_parser.stencil_size_ > 0) &&
          depth24_stencil8_supported) {
        offscreen_target_depth_format_ = GL_DEPTH24_STENCIL8;
        offscreen_target_stencil_format_ = 0;
      } else {
        offscreen_target_depth_format_ = attrib_parser.depth_size_ > 0 ?
            GL_DEPTH_COMPONENT16 : 0;
        offscreen_target_stencil_format_ = attrib_parser.stencil_size_ > 0 ?
            GL_STENCIL_INDEX8 : 0;
      }
    } else {
      offscreen_target_color_format_ = attrib_parser.alpha_size_ > 0 ?
          GL_RGBA : GL_RGB;

      const bool depth24_stencil8_supported =
          context_->HasExtension("GL_EXT_packed_depth_stencil");
      VLOG(1) << "GL_EXT_packed_depth_stencil "
              << (depth24_stencil8_supported ? "" : "not ") << "supported.";

      if ((attrib_parser.depth_size_ > 0 || attrib_parser.stencil_size_ > 0) &&
          depth24_stencil8_supported) {
        offscreen_target_depth_format_ = GL_DEPTH24_STENCIL8;
        offscreen_target_stencil_format_ = 0;
      } else {
        offscreen_target_depth_format_ = attrib_parser.depth_size_ > 0 ?
            GL_DEPTH_COMPONENT : 0;
        offscreen_target_stencil_format_ = attrib_parser.stencil_size_ > 0 ?
            GL_STENCIL_INDEX : 0;
      }
    }

    offscreen_saved_color_format_ = attrib_parser.alpha_size_ > 0 ?
        GL_RGBA : GL_RGB;

    offscreen_target_frame_buffer_.reset(new FrameBuffer(this));
    offscreen_target_frame_buffer_->Create();
    if (IsOffscreenBufferMultisampled()) {
      offscreen_target_color_render_buffer_.reset(new RenderBuffer(this));
      offscreen_target_color_render_buffer_->Create();
    } else {
      offscreen_target_color_texture_.reset(new Texture(this));
      offscreen_target_color_texture_->Create();
    }
    offscreen_target_depth_render_buffer_.reset(new RenderBuffer(this));
    offscreen_target_depth_render_buffer_->Create();
    offscreen_target_stencil_render_buffer_.reset(new RenderBuffer(this));
    offscreen_target_stencil_render_buffer_->Create();

    offscreen_saved_frame_buffer_.reset(new FrameBuffer(this));
    offscreen_saved_frame_buffer_->Create();
    offscreen_saved_color_texture_.reset(new Texture(this));
    offscreen_saved_color_texture_->Create();

    if (!ResizeOffscreenFrameBuffer(size)) {
      LOG(ERROR) << "Could not allocate offscreen buffer storage.";
      Destroy(true);
      return false;
    }

    DoBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  if (gfx::GetGLImplementation() != gfx::kGLImplementationEGLGLES2) {
    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);
    glEnable(GL_POINT_SPRITE);
  }

  has_robustness_extension_ =
      context->HasExtension("GL_ARB_robustness") ||
      context->HasExtension("GL_EXT_robustness");

  if (!feature_info_->feature_flags().disable_workarounds) {
#if defined(OS_MACOSX)
    needs_mac_nvidia_driver_workaround_ =
        feature_info_->feature_flags().is_nvidia;
    needs_glsl_built_in_function_emulation_ =
        feature_info_->feature_flags().is_amd;
#endif
  }

  if (!InitializeShaderTranslator()) {
    return false;
  }

  viewport_width_ = size.width();
  viewport_height_ = size.height();
  glViewport(viewport_x_, viewport_y_, viewport_width_, viewport_height_);

  GLint viewport_params[4] = { 0 };
  glGetIntegerv(GL_MAX_VIEWPORT_DIMS, viewport_params);
  viewport_max_width_ = viewport_params[0];
  viewport_max_height_ = viewport_params[1];

  glActiveTexture(GL_TEXTURE0 + active_texture_unit_);
  glLineWidth(1.0);
  EnableDisable(GL_BLEND, enable_blend_);
  glBlendColor(0.0f, 0.0, 0.0f, 0.0f);
  glBlendFunc(GL_ONE, GL_ZERO);
  glBlendEquation(GL_FUNC_ADD);
  glBlendFuncSeparate(GL_ONE, GL_ZERO, GL_ONE, GL_ZERO);
  glClearColor(clear_red_, clear_green_, clear_blue_, clear_alpha_);
  glColorMask(mask_red_, mask_green_, mask_blue_, mask_alpha_);
  EnableDisable(GL_CULL_FACE, enable_cull_face_);
  glCullFace(GL_BACK);
  glClearDepth(clear_depth_);
  glDepthFunc(GL_LESS);
  glDepthRange(0.0f, 1.0f);
  EnableDisable(GL_DEPTH_TEST, enable_depth_test_);
  glEnable(GL_DITHER);
  glFrontFace(GL_CCW);
  glHint(GL_GENERATE_MIPMAP_HINT, GL_DONT_CARE);
  glLineWidth(1.0f);
  glPixelStorei(GL_PACK_ALIGNMENT, pack_alignment_);
  glPolygonOffset(0.0f, 0.0f);
  glDisable(GL_POLYGON_OFFSET_FILL);
  glSampleCoverage(1.0, false);
  glScissor(viewport_x_, viewport_y_, viewport_width_, viewport_height_);
  EnableDisable(GL_SCISSOR_TEST, enable_scissor_test_);
  EnableDisable(GL_STENCIL_TEST, enable_stencil_test_);
  glClearStencil(clear_stencil_);
  glStencilFunc(GL_ALWAYS, 0, 0xFFFFFFFFU);
  glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
  glStencilMaskSeparate(GL_FRONT, mask_stencil_front_);
  glStencilMaskSeparate(GL_BACK, mask_stencil_back_);
  glPixelStorei(GL_UNPACK_ALIGNMENT, unpack_alignment_);

  DoBindBuffer(GL_ARRAY_BUFFER, 0);
  DoBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  DoBindFramebuffer(GL_FRAMEBUFFER, 0);
  DoBindRenderbuffer(GL_RENDERBUFFER, 0);

#if defined(OS_MACOSX)
  if (!feature_info_->feature_flags().disable_workarounds &&
      (feature_info_->feature_flags().is_amd ||
       feature_info_->feature_flags().is_intel) &&
      gfx::GetGLImplementation() == gfx::kGLImplementationDesktopGL) {
    glPointParameteri(GL_POINT_SPRITE_COORD_ORIGIN, GL_LOWER_LEFT);
  }
#endif

  return true;
}
