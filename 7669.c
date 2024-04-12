get_pixbuf_for_content (goffset  file_len,
                        char    *file_contents)
{
    gboolean res;
    GdkPixbuf *pixbuf, *pixbuf2;
    GdkPixbufLoader *loader;
    gsize chunk_len;
    pixbuf = NULL;

    loader = gdk_pixbuf_loader_new ();
    g_signal_connect (loader, "size-prepared",
                      G_CALLBACK (thumbnail_loader_size_prepared),
                      NULL);

    /* For some reason we have to write in chunks, or gdk-pixbuf fails */
    res = TRUE;
    while (res && file_len > 0)
    {
        chunk_len = file_len;
        res = gdk_pixbuf_loader_write (loader, (guchar *) file_contents, chunk_len, NULL);
        file_contents += chunk_len;
        file_len -= chunk_len;
    }
    if (res)
    {
        res = gdk_pixbuf_loader_close (loader, NULL);
    }
    if (res)
    {
        pixbuf = g_object_ref (gdk_pixbuf_loader_get_pixbuf (loader));
    }
    g_object_unref (G_OBJECT (loader));

    if (pixbuf)
    {
        pixbuf2 = gdk_pixbuf_apply_embedded_orientation (pixbuf);
        g_object_unref (pixbuf);
        pixbuf = pixbuf2;
    }
    return pixbuf;
}
