    void createColorTransform(const ColorProfile& colorProfile, bool hasAlpha)
    {
        if (m_transform)
            qcms_transform_release(m_transform);
        m_transform = 0;

        if (colorProfile.isEmpty())
            return;
        qcms_profile* deviceProfile = ImageDecoder::qcmsOutputDeviceProfile();
        if (!deviceProfile)
            return;
        qcms_profile* inputProfile = qcms_profile_from_memory(colorProfile.data(), colorProfile.size());
        if (!inputProfile)
            return;
        ASSERT(icSigRgbData == qcms_profile_get_color_space(inputProfile));
        qcms_data_type dataFormat = hasAlpha ? QCMS_DATA_RGBA_8 : QCMS_DATA_RGB_8;
        m_transform = qcms_transform_create(inputProfile, dataFormat, deviceProfile, dataFormat, QCMS_INTENT_PERCEPTUAL);
        qcms_profile_release(inputProfile);
    }
