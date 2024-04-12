static ImageOrientation readImageOrientation(jpeg_decompress_struct* info)
{
    const unsigned orientationTag = 0x112;
    const unsigned shortType = 3;
    for (jpeg_saved_marker_ptr marker = info->marker_list; marker; marker = marker->next) {
        bool isBigEndian;
        unsigned ifdOffset;
        if (!checkExifHeader(marker, isBigEndian, ifdOffset))
            continue;
        const unsigned offsetToTiffData = 6; // Account for 'Exif\0<fill byte>' header.
        if (marker->data_length < offsetToTiffData || ifdOffset >= marker->data_length - offsetToTiffData)
            continue;
        ifdOffset += offsetToTiffData;

        JOCTET* ifd = marker->data + ifdOffset;
        JOCTET* end = marker->data + marker->data_length;
        if (end - ifd < 2)
            continue;
        unsigned tagCount = readUint16(ifd, isBigEndian);
        ifd += 2; // Skip over the uint16 that was just read.

        const int ifdEntrySize = 12;
        for (unsigned i = 0; i < tagCount && end - ifd >= ifdEntrySize; ++i, ifd += ifdEntrySize) {
            unsigned tag = readUint16(ifd, isBigEndian);
            unsigned type = readUint16(ifd + 2, isBigEndian);
            unsigned count = readUint32(ifd + 4, isBigEndian);
            if (tag == orientationTag && type == shortType && count == 1)
                return ImageOrientation::fromEXIFValue(readUint16(ifd + 8, isBigEndian));
        }
    }

    return ImageOrientation();
}
