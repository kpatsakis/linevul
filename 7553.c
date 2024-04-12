  void ExtractFileFeatures(const base::FilePath& file_path) {
    base::TimeTicks start_time = base::TimeTicks::Now();
    binary_feature_extractor_->CheckSignature(file_path, &signature_info_);
    bool is_signed = (signature_info_.certificate_chain_size() > 0);
    if (is_signed) {
      DVLOG(2) << "Downloaded a signed binary: " << file_path.value();
    } else {
      DVLOG(2) << "Downloaded an unsigned binary: "
               << file_path.value();
    }
    UMA_HISTOGRAM_BOOLEAN("SBClientDownload.SignedBinaryDownload", is_signed);
    UMA_HISTOGRAM_TIMES("SBClientDownload.ExtractSignatureFeaturesTime",
                        base::TimeTicks::Now() - start_time);

    start_time = base::TimeTicks::Now();
    image_headers_.reset(new ClientDownloadRequest_ImageHeaders());
    if (!binary_feature_extractor_->ExtractImageFeatures(
            file_path,
            BinaryFeatureExtractor::kDefaultOptions,
            image_headers_.get(),
            nullptr /* signed_data */)) {
      image_headers_.reset();
    }
    UMA_HISTOGRAM_TIMES("SBClientDownload.ExtractImageHeadersTime",
                        base::TimeTicks::Now() - start_time);

    OnFileFeatureExtractionDone();
  }
