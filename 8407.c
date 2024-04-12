RendererCapabilities::RendererCapabilities(ResourceFormat best_texture_format,
                                           bool allow_partial_texture_updates,
                                           bool using_offscreen_context3d,
                                           int max_texture_size,
                                           bool using_shared_memory_resources)
    : best_texture_format(best_texture_format),
      allow_partial_texture_updates(allow_partial_texture_updates),
      using_offscreen_context3d(using_offscreen_context3d),
      max_texture_size(max_texture_size),
      using_shared_memory_resources(using_shared_memory_resources) {}
