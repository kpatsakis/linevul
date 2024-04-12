void EnumFonts(struct _FPDF_SYSFONTINFO* sysfontinfo, void* mapper) {
  FPDF_AddInstalledFont(mapper, "Arial", FXFONT_DEFAULT_CHARSET);

  const FPDF_CharsetFontMap* font_map = FPDF_GetDefaultTTFMap();
  for (; font_map->charset != -1; ++font_map) {
    FPDF_AddInstalledFont(mapper, font_map->fontname, font_map->charset);
  }
}
