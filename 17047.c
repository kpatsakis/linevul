  void SetContentsScaleOnBothLayers(float contents_scale,
                                    float device_scale_factor,
                                    float page_scale_factor,
                                    float maximum_animation_contents_scale,
                                    bool animating_transform) {
    SetupDrawPropertiesAndUpdateTiles(pending_layer_,
                                      contents_scale,
                                      device_scale_factor,
                                      page_scale_factor,
                                      maximum_animation_contents_scale,
                                      animating_transform);

    SetupDrawPropertiesAndUpdateTiles(active_layer_,
                                      contents_scale,
                                      device_scale_factor,
                                      page_scale_factor,
                                      maximum_animation_contents_scale,
                                      animating_transform);
  }
