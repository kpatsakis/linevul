EnumTraits<media::mojom::VideoFacingMode, media::VideoFacingMode>::ToMojom(
    media::VideoFacingMode input) {
  switch (input) {
    case media::VideoFacingMode::MEDIA_VIDEO_FACING_NONE:
      return media::mojom::VideoFacingMode::NONE;
    case media::VideoFacingMode::MEDIA_VIDEO_FACING_USER:
      return media::mojom::VideoFacingMode::USER;
    case media::VideoFacingMode::MEDIA_VIDEO_FACING_ENVIRONMENT:
      return media::mojom::VideoFacingMode::ENVIRONMENT;
    case media::VideoFacingMode::NUM_MEDIA_VIDEO_FACING_MODES:
      NOTREACHED();
      return media::mojom::VideoFacingMode::NONE;
  }
  NOTREACHED();
  return media::mojom::VideoFacingMode::NONE;
}
