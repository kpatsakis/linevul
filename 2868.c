bool Instance::Init(uint32_t argc, const char* argn[], const char* argv[]) {
  if (pp::PDF::IsFeatureEnabled(this, PP_PDFFEATURE_HIDPI))
    hidpi_enabled_ = true;

  printing_enabled_ = pp::PDF::IsFeatureEnabled(this, PP_PDFFEATURE_PRINTING);
  if (printing_enabled_) {
    CreateToolbar(kPDFToolbarButtons, arraysize(kPDFToolbarButtons));
  } else {
    CreateToolbar(kPDFNoPrintToolbarButtons,
                  arraysize(kPDFNoPrintToolbarButtons));
  }

  CreateProgressBar();

  autoscroll_anchor_ =
      CreateResourceImage(PP_RESOURCEIMAGE_PDF_PAN_SCROLL_ICON);

#ifdef ENABLE_THUMBNAILS
  CreateThumbnails();
#endif
  const char* url = NULL;
  for (uint32_t i = 0; i < argc; ++i) {
    if (strcmp(argn[i], "src") == 0) {
      url = argv[i];
      break;
    }
  }

  if (!url)
    return false;

  CreatePageIndicator(IsPrintPreviewUrl(url));

  if (!full_) {
    LoadUrl(url);
  } else {
    DCHECK(!did_call_start_loading_);
    pp::PDF::DidStartLoading(this);
    did_call_start_loading_ = true;
  }

  ZoomLimitsChanged(kMinZoom, kMaxZoom);

  text_input_.reset(new pp::TextInput_Dev(this));

  url_ = url;
  return engine_->New(url);
}
