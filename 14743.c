  void SetToLarge(const gfx::PointF& new_center) {
    PaintedShapeTransforms transforms;
    SetPaintedLayersVisible(true);
    shadow_layer_->SetVisible(false);
    large_shadow_layer_->SetVisible(true);
    MoveLargeShadow(new_center);

    center_point_ = new_center;
    CalculateRectTransforms(large_size_, kBackgroundCornerRadiusDip,
                            &transforms);
    SetTransforms(transforms);
  }
