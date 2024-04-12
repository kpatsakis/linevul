XmpFilePtr xmp_files_open_new(const char *path, XmpOpenFileOptions options)
{
    CHECK_PTR(path, NULL);
    RESET_ERROR;

    try {
        auto txf = std::unique_ptr<SXMPFiles>(new SXMPFiles);

        txf->OpenFile(path, XMP_FT_UNKNOWN, options);

        return reinterpret_cast<XmpFilePtr>(txf.release());
    }
    catch (const XMP_Error &e) {
        set_error(e);
    }

    return NULL;
}
