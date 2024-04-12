XcursorScanTheme (const char *theme, const char *name)
{
    FILE	*f = NULL;
    char	*full;
    char	*dir;
    const char  *path;
    char	*inherits = NULL;
    const char	*i;

    if (!theme || !name)
        return NULL;

    /*
     * Scan this theme
     */
    for (path = XcursorLibraryPath ();
	 path && f == NULL;
	 path = _XcursorNextPath (path))
    {
	dir = _XcursorBuildThemeDir (path, theme);
	if (dir)
	{
	    full = _XcursorBuildFullname (dir, "cursors", name);
	    if (full)
	    {
		f = fopen (full, "r");
		free (full);
	    }
	    if (!f && !inherits)
	    {
		full = _XcursorBuildFullname (dir, "", "index.theme");
		if (full)
		{
		    inherits = _XcursorThemeInherits (full);
		    free (full);
		}
	    }
	    free (dir);
	}
    }
    /*
     * Recurse to scan inherited themes
     */
    for (i = inherits; i && f == NULL; i = _XcursorNextPath (i))
	f = XcursorScanTheme (i, name);
    if (inherits != NULL)
	free (inherits);
    return f;
}
