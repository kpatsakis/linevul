SkIcoCodec::SkIcoCodec(int width, int height, const SkEncodedInfo& info,
 SkTArray<std::unique_ptr<SkCodec>, true>* codecs,
                       sk_sp<SkColorSpace> colorSpace)
 : INHERITED(width, height, info, SkColorSpaceXform::ColorFormat(), nullptr,
                std::move(colorSpace))
 , fEmbeddedCodecs(codecs)
 , fCurrScanlineCodec(nullptr)
 , fCurrIncrementalCodec(nullptr)
{}
