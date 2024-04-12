PlatformFontSkia::PlatformFontSkia(sk_sp<SkTypeface> typeface,
                                   const std::string& family,
                                   int size_pixels,
                                   int style,
                                   Font::Weight weight,
                                   const FontRenderParams& render_params) {
  InitFromDetails(std::move(typeface), family, size_pixels, style, weight,
                  render_params);
}
