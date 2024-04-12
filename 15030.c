ProcRenderCreateGlyphSet (ClientPtr client)
{
    GlyphSetPtr	    glyphSet;
    PictFormatPtr   format;
    int		    rc, f;
    REQUEST(xRenderCreateGlyphSetReq);

    REQUEST_SIZE_MATCH(xRenderCreateGlyphSetReq);

    LEGAL_NEW_RESOURCE(stuff->gsid, client);
    rc = dixLookupResourceByType((pointer *)&format, stuff->format,
				 PictFormatType, client, DixReadAccess);
    if (rc != Success)
	return rc;

    switch (format->depth) {
    case 1:
	f = GlyphFormat1;
	break;
    case 4:
	f = GlyphFormat4;
	break;
    case 8:
	f = GlyphFormat8;
	break;
    case 16:
	f = GlyphFormat16;
	break;
    case 32:
	f = GlyphFormat32;
	break;
    default:
	return BadMatch;
    }
    if (format->type != PictTypeDirect)
	return BadMatch;
    glyphSet = AllocateGlyphSet (f, format);
    if (!glyphSet)
	return BadAlloc;
    /* security creation/labeling check */
    rc = XaceHook(XACE_RESOURCE_ACCESS, client, stuff->gsid, GlyphSetType,
		  glyphSet, RT_NONE, NULL, DixCreateAccess);
    if (rc != Success)
	return rc;
    if (!AddResource (stuff->gsid, GlyphSetType, (pointer)glyphSet))
	return BadAlloc;
    return Success;
}
