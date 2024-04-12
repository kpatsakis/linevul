DEFUN(ldBmark, BOOKMARK VIEW_BOOKMARK, "View bookmarks")
{
    cmd_loadURL(BookmarkFile, NULL, NO_REFERER, NULL);
}
