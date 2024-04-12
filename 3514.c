EnumTraits<media::mojom::VideoCaptureApi, media::VideoCaptureApi>::ToMojom(
    media::VideoCaptureApi input) {
  switch (input) {
    case media::VideoCaptureApi::LINUX_V4L2_SINGLE_PLANE:
      return media::mojom::VideoCaptureApi::LINUX_V4L2_SINGLE_PLANE;
    case media::VideoCaptureApi::WIN_MEDIA_FOUNDATION:
      return media::mojom::VideoCaptureApi::WIN_MEDIA_FOUNDATION;
    case media::VideoCaptureApi::WIN_MEDIA_FOUNDATION_SENSOR:
      return media::mojom::VideoCaptureApi::WIN_MEDIA_FOUNDATION_SENSOR;
    case media::VideoCaptureApi::WIN_DIRECT_SHOW:
      return media::mojom::VideoCaptureApi::WIN_DIRECT_SHOW;
    case media::VideoCaptureApi::MACOSX_AVFOUNDATION:
      return media::mojom::VideoCaptureApi::MACOSX_AVFOUNDATION;
    case media::VideoCaptureApi::MACOSX_DECKLINK:
      return media::mojom::VideoCaptureApi::MACOSX_DECKLINK;
    case media::VideoCaptureApi::ANDROID_API1:
      return media::mojom::VideoCaptureApi::ANDROID_API1;
    case media::VideoCaptureApi::ANDROID_API2_LEGACY:
      return media::mojom::VideoCaptureApi::ANDROID_API2_LEGACY;
    case media::VideoCaptureApi::ANDROID_API2_FULL:
      return media::mojom::VideoCaptureApi::ANDROID_API2_FULL;
    case media::VideoCaptureApi::ANDROID_API2_LIMITED:
      return media::mojom::VideoCaptureApi::ANDROID_API2_LIMITED;
    case media::VideoCaptureApi::VIRTUAL_DEVICE:
      return media::mojom::VideoCaptureApi::VIRTUAL_DEVICE;
    case media::VideoCaptureApi::UNKNOWN:
      return media::mojom::VideoCaptureApi::UNKNOWN;
  }
  NOTREACHED();
  return media::mojom::VideoCaptureApi::UNKNOWN;
}
