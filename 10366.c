status_t ACodec::configureCodec(
 const char *mime, const sp<AMessage> &msg) {
 int32_t encoder;
 if (!msg->findInt32("encoder", &encoder)) {
        encoder = false;
 }

    sp<AMessage> inputFormat = new AMessage();
    sp<AMessage> outputFormat = mNotify->dup(); // will use this for kWhatOutputFormatChanged

    mIsEncoder = encoder;

    mInputMetadataType = kMetadataBufferTypeInvalid;
    mOutputMetadataType = kMetadataBufferTypeInvalid;

 status_t err = setComponentRole(encoder /* isEncoder */, mime);

 if (err != OK) {
 return err;
 }

 int32_t bitRate = 0;
 if (encoder && strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_FLAC)
 && !msg->findInt32("bitrate", &bitRate)) {
 return INVALID_OPERATION;
 }

 int32_t storeMeta;
 if (encoder
 && msg->findInt32("store-metadata-in-buffers", &storeMeta)
 && storeMeta != 0) {
        err = mOMX->storeMetaDataInBuffers(mNode, kPortIndexInput, OMX_TRUE, &mInputMetadataType);
 if (err != OK) {
            ALOGE("[%s] storeMetaDataInBuffers (input) failed w/ err %d",
                    mComponentName.c_str(), err);

 return err;
 }
 if (mInputMetadataType == kMetadataBufferTypeGrallocSource) {
            mInputMetadataType = kMetadataBufferTypeCameraSource;
 }

 uint32_t usageBits;
 if (mOMX->getParameter(
                mNode, (OMX_INDEXTYPE)OMX_IndexParamConsumerUsageBits,
 &usageBits, sizeof(usageBits)) == OK) {
            inputFormat->setInt32(
 "using-sw-read-often", !!(usageBits & GRALLOC_USAGE_SW_READ_OFTEN));
 }
 }

 int32_t prependSPSPPS = 0;
 if (encoder
 && msg->findInt32("prepend-sps-pps-to-idr-frames", &prependSPSPPS)
 && prependSPSPPS != 0) {
        OMX_INDEXTYPE index;
        err = mOMX->getExtensionIndex(
                mNode,
 "OMX.google.android.index.prependSPSPPSToIDRFrames",
 &index);

 if (err == OK) {
 PrependSPSPPSToIDRFramesParams params;
 InitOMXParams(&params);
            params.bEnable = OMX_TRUE;

            err = mOMX->setParameter(
                    mNode, index, &params, sizeof(params));
 }

 if (err != OK) {
            ALOGE("Encoder could not be configured to emit SPS/PPS before "
 "IDR frames. (err %d)", err);

 return err;
 }
 }

 int32_t video = !strncasecmp(mime, "video/", 6);
    mIsVideo = video;
 if (encoder && video) {
        OMX_BOOL enable = (OMX_BOOL) (prependSPSPPS
 && msg->findInt32("store-metadata-in-buffers-output", &storeMeta)
 && storeMeta != 0);

        err = mOMX->storeMetaDataInBuffers(mNode, kPortIndexOutput, enable, &mOutputMetadataType);
 if (err != OK) {
            ALOGE("[%s] storeMetaDataInBuffers (output) failed w/ err %d",
                mComponentName.c_str(), err);
 }

 if (!msg->findInt64(
 "repeat-previous-frame-after",
 &mRepeatFrameDelayUs)) {
            mRepeatFrameDelayUs = -1ll;
 }

 if (!msg->findInt64("max-pts-gap-to-encoder", &mMaxPtsGapUs)) {
            mMaxPtsGapUs = -1ll;
 }

 if (!msg->findFloat("max-fps-to-encoder", &mMaxFps)) {
            mMaxFps = -1;
 }

 if (!msg->findInt64("time-lapse", &mTimePerCaptureUs)) {
            mTimePerCaptureUs = -1ll;
 }

 if (!msg->findInt32(
 "create-input-buffers-suspended",
 (int32_t*)&mCreateInputBuffersSuspended)) {
            mCreateInputBuffersSuspended = false;
 }
 }

    sp<RefBase> obj;
 bool haveNativeWindow = msg->findObject("native-window", &obj)
 && obj != NULL && video && !encoder;
    mLegacyAdaptiveExperiment = false;
 if (video && !encoder) {
        inputFormat->setInt32("adaptive-playback", false);

 int32_t usageProtected;
 if (msg->findInt32("protected", &usageProtected) && usageProtected) {
 if (!haveNativeWindow) {
                ALOGE("protected output buffers must be sent to an ANativeWindow");
 return PERMISSION_DENIED;
 }
            mFlags |= kFlagIsGrallocUsageProtected;
            mFlags |= kFlagPushBlankBuffersToNativeWindowOnShutdown;
 }
 }
 if (haveNativeWindow) {
        sp<ANativeWindow> nativeWindow =
 static_cast<ANativeWindow *>(static_cast<Surface *>(obj.get()));

 int32_t autoFrc;
 if (msg->findInt32("auto-frc", &autoFrc)) {
 bool enabled = autoFrc;
            OMX_CONFIG_BOOLEANTYPE config;
 InitOMXParams(&config);
            config.bEnabled = (OMX_BOOL)enabled;
 status_t temp = mOMX->setConfig(
                    mNode, (OMX_INDEXTYPE)OMX_IndexConfigAutoFramerateConversion,
 &config, sizeof(config));
 if (temp == OK) {
                outputFormat->setInt32("auto-frc", enabled);
 } else if (enabled) {
                ALOGI("codec does not support requested auto-frc (err %d)", temp);
 }
 }

 int32_t tunneled;
 if (msg->findInt32("feature-tunneled-playback", &tunneled) &&
            tunneled != 0) {
            ALOGI("Configuring TUNNELED video playback.");
            mTunneled = true;

 int32_t audioHwSync = 0;
 if (!msg->findInt32("audio-hw-sync", &audioHwSync)) {
                ALOGW("No Audio HW Sync provided for video tunnel");
 }
            err = configureTunneledVideoPlayback(audioHwSync, nativeWindow);
 if (err != OK) {
                ALOGE("configureTunneledVideoPlayback(%d,%p) failed!",
                        audioHwSync, nativeWindow.get());
 return err;
 }

 int32_t maxWidth = 0, maxHeight = 0;
 if (msg->findInt32("max-width", &maxWidth) &&
                    msg->findInt32("max-height", &maxHeight)) {

                err = mOMX->prepareForAdaptivePlayback(
                        mNode, kPortIndexOutput, OMX_TRUE, maxWidth, maxHeight);
 if (err != OK) {
                    ALOGW("[%s] prepareForAdaptivePlayback failed w/ err %d",
                            mComponentName.c_str(), err);
                    err = OK;
 } else {
                    inputFormat->setInt32("max-width", maxWidth);
                    inputFormat->setInt32("max-height", maxHeight);
                    inputFormat->setInt32("adaptive-playback", true);
 }
 }
 } else {
            ALOGV("Configuring CPU controlled video playback.");
            mTunneled = false;

            err = native_window_set_sideband_stream(nativeWindow.get(), NULL);
 if (err != OK) {
                ALOGE("set_sideband_stream(NULL) failed! (err %d).", err);
 return err;
 }

            err = mOMX->storeMetaDataInBuffers(
                    mNode, kPortIndexOutput, OMX_TRUE, &mOutputMetadataType);
 if (err != OK) {
                ALOGE("[%s] storeMetaDataInBuffers failed w/ err %d",
                        mComponentName.c_str(), err);


 int usageBits = 0;
 bool canDoAdaptivePlayback;

 if (nativeWindow->query(
                        nativeWindow.get(),
                        NATIVE_WINDOW_CONSUMER_USAGE_BITS,
 &usageBits) != OK) {
                    canDoAdaptivePlayback = false;
 } else {
                    canDoAdaptivePlayback =
 (usageBits &
 (GRALLOC_USAGE_SW_READ_MASK |
                                 GRALLOC_USAGE_SW_WRITE_MASK)) == 0;
 }

 int32_t maxWidth = 0, maxHeight = 0;
 if (canDoAdaptivePlayback &&
                        msg->findInt32("max-width", &maxWidth) &&
                        msg->findInt32("max-height", &maxHeight)) {
                    ALOGV("[%s] prepareForAdaptivePlayback(%dx%d)",
                            mComponentName.c_str(), maxWidth, maxHeight);

                    err = mOMX->prepareForAdaptivePlayback(
                            mNode, kPortIndexOutput, OMX_TRUE, maxWidth,
                            maxHeight);
                    ALOGW_IF(err != OK,
 "[%s] prepareForAdaptivePlayback failed w/ err %d",
                            mComponentName.c_str(), err);

 if (err == OK) {
                        inputFormat->setInt32("max-width", maxWidth);
                        inputFormat->setInt32("max-height", maxHeight);
                        inputFormat->setInt32("adaptive-playback", true);
 }
 }
                err = OK;
 } else {
                ALOGV("[%s] storeMetaDataInBuffers succeeded",
                        mComponentName.c_str());
                CHECK(storingMetadataInDecodedBuffers());
                mLegacyAdaptiveExperiment = ADebug::isExperimentEnabled(
 "legacy-adaptive", !msg->contains("no-experiments"));

                inputFormat->setInt32("adaptive-playback", true);
 }

 int32_t push;
 if (msg->findInt32("push-blank-buffers-on-shutdown", &push)
 && push != 0) {
                mFlags |= kFlagPushBlankBuffersToNativeWindowOnShutdown;
 }
 }

 int32_t rotationDegrees;
 if (msg->findInt32("rotation-degrees", &rotationDegrees)) {
            mRotationDegrees = rotationDegrees;
 } else {
            mRotationDegrees = 0;
 }
 }

 if (video) {
 bool usingSwRenderer = false;
 if (haveNativeWindow && mComponentName.startsWith("OMX.google.")) {
            usingSwRenderer = true;
            haveNativeWindow = false;
 }

 if (encoder) {
            err = setupVideoEncoder(mime, msg);
 } else {
            err = setupVideoDecoder(mime, msg, haveNativeWindow);
 }

 if (err != OK) {
 return err;
 }

 if (haveNativeWindow) {
            mNativeWindow = static_cast<Surface *>(obj.get());
 }

        err = initNativeWindow();
 if (err != OK) {
 return err;
 }

 if (haveNativeWindow) {
 int32_t requestedColorFormat = OMX_COLOR_FormatUnused;
 if (msg->findInt32("color-format", &requestedColorFormat) &&
                    requestedColorFormat == OMX_COLOR_FormatYUV420Flexible) {
 status_t err = getPortFormat(kPortIndexOutput, outputFormat);
 if (err != OK) {
 return err;
 }
 int32_t colorFormat = OMX_COLOR_FormatUnused;
                OMX_U32 flexibleEquivalent = OMX_COLOR_FormatUnused;
 if (!outputFormat->findInt32("color-format", &colorFormat)) {
                    ALOGE("ouptut port did not have a color format (wrong domain?)");
 return BAD_VALUE;
 }
                ALOGD("[%s] Requested output format %#x and got %#x.",
                        mComponentName.c_str(), requestedColorFormat, colorFormat);
 if (!isFlexibleColorFormat(
                                mOMX, mNode, colorFormat, haveNativeWindow, &flexibleEquivalent)
 || flexibleEquivalent != (OMX_U32)requestedColorFormat) {
                    ALOGI("[%s] Falling back to software renderer", mComponentName.c_str());
                    mNativeWindow.clear();
                    mNativeWindowUsageBits = 0;
                    haveNativeWindow = false;
                    usingSwRenderer = true;
 if (storingMetadataInDecodedBuffers()) {
                        err = mOMX->storeMetaDataInBuffers(
                                mNode, kPortIndexOutput, OMX_FALSE, &mOutputMetadataType);
                        mOutputMetadataType = kMetadataBufferTypeInvalid; // just in case
                        inputFormat->setInt32("adaptive-playback", false);
 }
 if (err == OK) {
                        err = mOMX->enableGraphicBuffers(mNode, kPortIndexOutput, OMX_FALSE);
 }
 if (mFlags & kFlagIsGrallocUsageProtected) {
                        err = PERMISSION_DENIED;
 } else if (err == OK) {
                        err = setupVideoDecoder(mime, msg, false);
 }
 }
 }
 }

 if (usingSwRenderer) {
            outputFormat->setInt32("using-sw-renderer", 1);
 }
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_MPEG)) {
 int32_t numChannels, sampleRate;
 if (!msg->findInt32("channel-count", &numChannels)
 || !msg->findInt32("sample-rate", &sampleRate)) {
            err = OK;
 } else {
            err = setupRawAudioFormat(
                    encoder ? kPortIndexInput : kPortIndexOutput,
                    sampleRate,
                    numChannels);
 }
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_AAC)) {
 int32_t numChannels, sampleRate;
 if (!msg->findInt32("channel-count", &numChannels)
 || !msg->findInt32("sample-rate", &sampleRate)) {
            err = INVALID_OPERATION;
 } else {
 int32_t isADTS, aacProfile;
 int32_t sbrMode;
 int32_t maxOutputChannelCount;
 int32_t pcmLimiterEnable;
 drcParams_t drc;
 if (!msg->findInt32("is-adts", &isADTS)) {
                isADTS = 0;
 }
 if (!msg->findInt32("aac-profile", &aacProfile)) {
                aacProfile = OMX_AUDIO_AACObjectNull;
 }
 if (!msg->findInt32("aac-sbr-mode", &sbrMode)) {
                sbrMode = -1;
 }

 if (!msg->findInt32("aac-max-output-channel_count", &maxOutputChannelCount)) {
                maxOutputChannelCount = -1;
 }
 if (!msg->findInt32("aac-pcm-limiter-enable", &pcmLimiterEnable)) {
                pcmLimiterEnable = -1;
 }
 if (!msg->findInt32("aac-encoded-target-level", &drc.encodedTargetLevel)) {
                drc.encodedTargetLevel = -1;
 }
 if (!msg->findInt32("aac-drc-cut-level", &drc.drcCut)) {
                drc.drcCut = -1;
 }
 if (!msg->findInt32("aac-drc-boost-level", &drc.drcBoost)) {
                drc.drcBoost = -1;
 }
 if (!msg->findInt32("aac-drc-heavy-compression", &drc.heavyCompression)) {
                drc.heavyCompression = -1;
 }
 if (!msg->findInt32("aac-target-ref-level", &drc.targetRefLevel)) {
                drc.targetRefLevel = -1;
 }

            err = setupAACCodec(
                    encoder, numChannels, sampleRate, bitRate, aacProfile,
                    isADTS != 0, sbrMode, maxOutputChannelCount, drc,
                    pcmLimiterEnable);
 }
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_AMR_NB)) {
        err = setupAMRCodec(encoder, false /* isWAMR */, bitRate);
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_AMR_WB)) {
        err = setupAMRCodec(encoder, true /* isWAMR */, bitRate);
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_G711_ALAW)
 || !strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_G711_MLAW)) {

 int32_t numChannels;
 if (!msg->findInt32("channel-count", &numChannels)) {
            err = INVALID_OPERATION;
 } else {
 int32_t sampleRate;
 if (!msg->findInt32("sample-rate", &sampleRate)) {
                sampleRate = 8000;
 }
            err = setupG711Codec(encoder, sampleRate, numChannels);
 }
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_FLAC)) {
 int32_t numChannels = 0, sampleRate = 0, compressionLevel = -1;
 if (encoder &&
 (!msg->findInt32("channel-count", &numChannels)
 || !msg->findInt32("sample-rate", &sampleRate))) {
            ALOGE("missing channel count or sample rate for FLAC encoder");
            err = INVALID_OPERATION;
 } else {
 if (encoder) {
 if (!msg->findInt32(
 "complexity", &compressionLevel) &&
 !msg->findInt32(
 "flac-compression-level", &compressionLevel)) {
                    compressionLevel = 5; // default FLAC compression level
 } else if (compressionLevel < 0) {
                    ALOGW("compression level %d outside [0..8] range, "
 "using 0",
                          compressionLevel);
                    compressionLevel = 0;
 } else if (compressionLevel > 8) {
                    ALOGW("compression level %d outside [0..8] range, "
 "using 8",
                          compressionLevel);
                    compressionLevel = 8;
 }
 }
            err = setupFlacCodec(
                    encoder, numChannels, sampleRate, compressionLevel);
 }
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_RAW)) {
 int32_t numChannels, sampleRate;
 if (encoder
 || !msg->findInt32("channel-count", &numChannels)
 || !msg->findInt32("sample-rate", &sampleRate)) {
            err = INVALID_OPERATION;
 } else {
            err = setupRawAudioFormat(kPortIndexInput, sampleRate, numChannels);
 }
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_AC3)) {
 int32_t numChannels;
 int32_t sampleRate;
 if (!msg->findInt32("channel-count", &numChannels)
 || !msg->findInt32("sample-rate", &sampleRate)) {
            err = INVALID_OPERATION;
 } else {
            err = setupAC3Codec(encoder, numChannels, sampleRate);
 }
 } else if (!strcasecmp(mime, MEDIA_MIMETYPE_AUDIO_EAC3)) {
 int32_t numChannels;
 int32_t sampleRate;
 if (!msg->findInt32("channel-count", &numChannels)
 || !msg->findInt32("sample-rate", &sampleRate)) {
            err = INVALID_OPERATION;
 } else {
            err = setupEAC3Codec(encoder, numChannels, sampleRate);
 }
 }

 if (err != OK) {
 return err;
 }

 if (!msg->findInt32("encoder-delay", &mEncoderDelay)) {
        mEncoderDelay = 0;
 }

 if (!msg->findInt32("encoder-padding", &mEncoderPadding)) {
        mEncoderPadding = 0;
 }

 if (msg->findInt32("channel-mask", &mChannelMask)) {
        mChannelMaskPresent = true;
 } else {
        mChannelMaskPresent = false;
 }

 int32_t maxInputSize;
 if (msg->findInt32("max-input-size", &maxInputSize)) {
        err = setMinBufferSize(kPortIndexInput, (size_t)maxInputSize);
 } else if (!strcmp("OMX.Nvidia.aac.decoder", mComponentName.c_str())) {
        err = setMinBufferSize(kPortIndexInput, 8192); // XXX
 }

 int32_t priority;
 if (msg->findInt32("priority", &priority)) {
        err = setPriority(priority);
 }

 int32_t rateInt = -1;
 float rateFloat = -1;
 if (!msg->findFloat("operating-rate", &rateFloat)) {
        msg->findInt32("operating-rate", &rateInt);
        rateFloat = (float)rateInt; // 16MHz (FLINTMAX) is OK for upper bound.
 }
 if (rateFloat > 0) {
        err = setOperatingRate(rateFloat, video);
 }

    mBaseOutputFormat = outputFormat;

    err = getPortFormat(kPortIndexInput, inputFormat);
 if (err == OK) {
        err = getPortFormat(kPortIndexOutput, outputFormat);
 if (err == OK) {
            mInputFormat = inputFormat;
            mOutputFormat = outputFormat;
 }
 }
 return err;
}
