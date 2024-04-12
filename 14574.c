PassRefPtr<Uint8Array> ImageBitmap::copyBitmapData(AlphaDisposition alphaOp,
                                                   DataColorFormat format) {
  SkImageInfo info = SkImageInfo::Make(
      width(), height(),
      (format == RGBAColorType) ? kRGBA_8888_SkColorType : kN32_SkColorType,
      (alphaOp == PremultiplyAlpha) ? kPremul_SkAlphaType
                                    : kUnpremul_SkAlphaType);
  RefPtr<Uint8Array> dstPixels =
      copySkImageData(m_image->imageForCurrentFrame().get(), info);
  return dstPixels.release();
}
