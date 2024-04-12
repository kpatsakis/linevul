WebGLRenderingContextBase::WebGLRenderingContextBase(
    CanvasRenderingContextHost* host,
    scoped_refptr<WebTaskRunner> task_runner,
    std::unique_ptr<WebGraphicsContext3DProvider> context_provider,
    bool using_gpu_compositing,
    const CanvasContextCreationAttributes& requested_attributes,
    unsigned version)
    : CanvasRenderingContext(host, requested_attributes),
      context_group_(new WebGLContextGroup()),
      is_hidden_(false),
      context_lost_mode_(kNotLostContext),
      auto_recovery_method_(kManual),
      dispatch_context_lost_event_timer_(
          task_runner,
          this,
          &WebGLRenderingContextBase::DispatchContextLostEvent),
      restore_allowed_(false),
      restore_timer_(task_runner,
                     this,
                     &WebGLRenderingContextBase::MaybeRestoreContext),
      generated_image_cache_(4),
      synthesized_errors_to_console_(true),
      num_gl_errors_to_console_allowed_(kMaxGLErrorsAllowedToConsole),
      one_plus_max_non_default_texture_unit_(0),
      is_web_gl2_formats_types_added_(false),
      is_web_gl2_tex_image_source_formats_types_added_(false),
      is_web_gl2_internal_formats_copy_tex_image_added_(false),
      is_oes_texture_float_formats_types_added_(false),
      is_oes_texture_half_float_formats_types_added_(false),
      is_web_gl_depth_texture_formats_types_added_(false),
      is_ext_srgb_formats_types_added_(false),
      is_ext_color_buffer_float_formats_added_(false),
      version_(version) {
  DCHECK(context_provider);

  context_group_->AddContext(this);

  max_viewport_dims_[0] = max_viewport_dims_[1] = 0;
  context_provider->ContextGL()->GetIntegerv(GL_MAX_VIEWPORT_DIMS,
                                             max_viewport_dims_);

  scoped_refptr<DrawingBuffer> buffer;
  buffer =
      CreateDrawingBuffer(std::move(context_provider), using_gpu_compositing);
  if (!buffer) {
    context_lost_mode_ = kSyntheticLostContext;
    return;
  }

  drawing_buffer_ = std::move(buffer);
  GetDrawingBuffer()->Bind(GL_FRAMEBUFFER);
  SetupFlags();

#define ADD_VALUES_TO_SET(set, values)                    \
  for (size_t i = 0; i < WTF_ARRAY_LENGTH(values); ++i) { \
    set.insert(values[i]);                                \
  }

  ADD_VALUES_TO_SET(supported_internal_formats_, kSupportedFormatsES2);
  ADD_VALUES_TO_SET(supported_tex_image_source_internal_formats_,
                    kSupportedFormatsES2);
  ADD_VALUES_TO_SET(supported_internal_formats_copy_tex_image_,
                    kSupportedFormatsES2);
  ADD_VALUES_TO_SET(supported_formats_, kSupportedFormatsES2);
  ADD_VALUES_TO_SET(supported_tex_image_source_formats_, kSupportedFormatsES2);
  ADD_VALUES_TO_SET(supported_types_, kSupportedTypesES2);
  ADD_VALUES_TO_SET(supported_tex_image_source_types_, kSupportedTypesES2);
}
