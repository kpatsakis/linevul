  cc::Layer* SynthesizedClipLayerAt(unsigned index) {
    return paint_artifact_compositor_->GetExtraDataForTesting()
        ->synthesized_clip_layers[index]
        .get();
  }
