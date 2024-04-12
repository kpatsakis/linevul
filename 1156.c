  ConversionContext(const PropertyTreeState& layer_state,
                    const gfx::Vector2dF& layer_offset,
                    const FloatSize& visual_rect_subpixel_offset,
                    cc::DisplayItemList& cc_list)
      : layer_state_(layer_state),
        layer_offset_(layer_offset),
        current_transform_(layer_state.Transform()),
        current_clip_(layer_state.Clip()),
        current_effect_(layer_state.Effect()),
        chunk_to_layer_mapper_(layer_state_,
                               layer_offset_,
                               visual_rect_subpixel_offset),
        cc_list_(cc_list) {}
