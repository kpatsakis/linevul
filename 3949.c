VideoTrackRecorder::CodecId VideoStringToCodecId(
    const blink::WebString& codecs) {
  const std::string& codecs_str = ToLowerASCII(codecs.Utf8());

  if (codecs_str.find("vp8") != std::string::npos)
    return VideoTrackRecorder::CodecId::VP8;
  if (codecs_str.find("vp9") != std::string::npos)
    return VideoTrackRecorder::CodecId::VP9;
#if BUILDFLAG(RTC_USE_H264)
  if (codecs_str.find("h264") != std::string::npos ||
      codecs_str.find("avc1") != std::string::npos)
    return VideoTrackRecorder::CodecId::H264;
#endif
  return VideoTrackRecorder::CodecId::LAST;
}
