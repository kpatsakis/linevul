void DesktopWindowTreeHostX11::SerializeImageRepresentation(
    const gfx::ImageSkiaRep& rep,
    std::vector<unsigned long>* data) {
  int width = rep.GetWidth();
  data->push_back(width);

  int height = rep.GetHeight();
  data->push_back(height);

  const SkBitmap& bitmap = rep.GetBitmap();

  for (int y = 0; y < height; ++y)
    for (int x = 0; x < width; ++x)
      data->push_back(bitmap.getColor(x, y));
}
