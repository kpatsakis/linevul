XcursorFileLoadImages (FILE *file, int size)
{
    XcursorFile	f;

    if (!file)
        return NULL;

    _XcursorStdioFileInitialize (file, &f);
    return XcursorXcFileLoadImages (&f, size);
}
