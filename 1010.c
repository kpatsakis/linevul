static int GetLayersUpdateTimeHistogramBucket(size_t numLayers) {
  if (numLayers < 10)
    return 0;
  if (numLayers < 30)
    return 1;
  if (numLayers < 70)
    return 2;
  if (numLayers < 150)
    return 3;
  return 4;
}
