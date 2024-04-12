void OMXCodec::setImageOutputFormat(
        OMX_COLOR_FORMATTYPE format, OMX_U32 width, OMX_U32 height) {
    CODEC_LOGV("setImageOutputFormat(%u, %u)", width, height);

#if 0
    OMX_INDEXTYPE index;
 status_t err = mOMX->get_extension_index(
            mNode, "OMX.TI.JPEG.decode.Config.OutputColorFormat", &index);
    CHECK_EQ(err, (status_t)OK);

    err = mOMX->set_config(mNode, index, &format, sizeof(format));
    CHECK_EQ(err, (status_t)OK);
#endif

    OMX_PARAM_PORTDEFINITIONTYPE def;
 InitOMXParams(&def);
    def.nPortIndex = kPortIndexOutput;

 status_t err = mOMX->getParameter(
            mNode, OMX_IndexParamPortDefinition, &def, sizeof(def));
    CHECK_EQ(err, (status_t)OK);

    CHECK_EQ((int)def.eDomain, (int)OMX_PortDomainImage);

    OMX_IMAGE_PORTDEFINITIONTYPE *imageDef = &def.format.image;

    CHECK_EQ((int)imageDef->eCompressionFormat, (int)OMX_IMAGE_CodingUnused);
    imageDef->eColorFormat = format;
    imageDef->nFrameWidth = width;
    imageDef->nFrameHeight = height;

 switch (format) {
 case OMX_COLOR_FormatYUV420PackedPlanar:
 case OMX_COLOR_FormatYUV411Planar:
 {
            def.nBufferSize = (width * height * 3) / 2;
 break;
 }

 case OMX_COLOR_FormatCbYCrY:
 {
            def.nBufferSize = width * height * 2;
 break;
 }

 case OMX_COLOR_Format32bitARGB8888:
 {
            def.nBufferSize = width * height * 4;
 break;
 }

 case OMX_COLOR_Format16bitARGB4444:
 case OMX_COLOR_Format16bitARGB1555:
 case OMX_COLOR_Format16bitRGB565:
 case OMX_COLOR_Format16bitBGR565:
 {
            def.nBufferSize = width * height * 2;
 break;
 }

 default:
            CHECK(!"Should not be here. Unknown color format.");
 break;
 }

    def.nBufferCountActual = def.nBufferCountMin;

    err = mOMX->setParameter(
            mNode, OMX_IndexParamPortDefinition, &def, sizeof(def));
    CHECK_EQ(err, (status_t)OK);
}
