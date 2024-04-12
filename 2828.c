inline HTMLCanvasElement::HTMLCanvasElement(Document& document)
    : HTMLElement(kCanvasTag, document),
      ContextLifecycleObserver(&document),
      PageVisibilityObserver(document.GetPage()),
      size_(kDefaultCanvasWidth, kDefaultCanvasHeight),
      context_creation_was_blocked_(false),
      ignore_reset_(false),
      origin_clean_(true),
      surface_layer_bridge_(nullptr),
      gpu_memory_usage_(0),
      externally_allocated_memory_(0),
      gpu_readback_invoked_in_current_frame_(false),
      gpu_readback_successive_frames_(0) {
  UseCounter::Count(document, WebFeature::kHTMLCanvasElement);

  GetDocument().IncrementNumberOfCanvases();
}
