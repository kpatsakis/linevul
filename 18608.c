PlatformFontSkia::PlatformFontSkia(const std::string& font_name,
                                   int font_size_pixels) {
  FontRenderParamsQuery query;
  query.families.push_back(font_name);
  query.pixel_size = font_size_pixels;
  query.weight = Font::Weight::NORMAL;
  InitFromDetails(nullptr, font_name, font_size_pixels, Font::NORMAL,
                  query.weight, gfx::GetFontRenderParams(query, nullptr));
}
