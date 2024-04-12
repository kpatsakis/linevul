_XcursorFindBestSize (XcursorFileHeader *fileHeader,
		      XcursorDim	size,
		      int		*nsizesp)
{
    unsigned int n;
    int		nsizes = 0;
    XcursorDim	bestSize = 0;
    XcursorDim	thisSize;

    if (!fileHeader || !nsizesp)
        return 0;

    for (n = 0; n < fileHeader->ntoc; n++)
    {
	if (fileHeader->tocs[n].type != XCURSOR_IMAGE_TYPE)
	    continue;
	thisSize = fileHeader->tocs[n].subtype;
	if (!bestSize || dist (thisSize, size) < dist (bestSize, size))
	{
	    bestSize = thisSize;
	    nsizes = 1;
	}
	else if (thisSize == bestSize)
	    nsizes++;
    }
    *nsizesp = nsizes;
    return bestSize;
}
