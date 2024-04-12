nautilus_file_operations_copy_move (const GList          *item_uris,
                                    GArray               *relative_item_points,
                                    const char           *target_dir,
                                    GdkDragAction         copy_action,
                                    GtkWidget            *parent_view,
                                    NautilusCopyCallback  done_callback,
                                    gpointer              done_callback_data)
{
    GList *locations;
    GList *p;
    GFile *dest, *src_dir;
    GtkWindow *parent_window;
    gboolean target_is_mapping;
    gboolean have_nonmapping_source;

    dest = NULL;
    target_is_mapping = FALSE;
    have_nonmapping_source = FALSE;

    if (target_dir)
    {
        dest = g_file_new_for_uri (target_dir);
        if (g_file_has_uri_scheme (dest, "burn"))
        {
            target_is_mapping = TRUE;
        }
    }

    locations = location_list_from_uri_list (item_uris);

    for (p = locations; p != NULL; p = p->next)
    {
        if (!g_file_has_uri_scheme ((GFile * ) p->data, "burn"))
        {
            have_nonmapping_source = TRUE;
        }
    }

    if (target_is_mapping && have_nonmapping_source && copy_action == GDK_ACTION_MOVE)
    {
        /* never move to "burn:///", but fall back to copy.
         * This is a workaround, because otherwise the source files would be removed.
         */
        copy_action = GDK_ACTION_COPY;
    }

    parent_window = NULL;
    if (parent_view)
    {
        parent_window = (GtkWindow *) gtk_widget_get_ancestor (parent_view, GTK_TYPE_WINDOW);
    }

    if (copy_action == GDK_ACTION_COPY)
    {
        src_dir = g_file_get_parent (locations->data);
        if (target_dir == NULL ||
            (src_dir != NULL &&
             g_file_equal (src_dir, dest)))
        {
            nautilus_file_operations_duplicate (locations,
                                                relative_item_points,
                                                parent_window,
                                                done_callback, done_callback_data);
        }
        else
        {
            nautilus_file_operations_copy (locations,
                                           relative_item_points,
                                           dest,
                                           parent_window,
                                           done_callback, done_callback_data);
        }
        if (src_dir)
        {
            g_object_unref (src_dir);
        }
    }
    else if (copy_action == GDK_ACTION_MOVE)
    {
        if (g_file_has_uri_scheme (dest, "trash"))
        {
            MoveTrashCBData *cb_data;

            cb_data = g_slice_new0 (MoveTrashCBData);
            cb_data->real_callback = done_callback;
            cb_data->real_data = done_callback_data;

            nautilus_file_operations_trash_or_delete (locations,
                                                      parent_window,
                                                      (NautilusDeleteCallback) callback_for_move_to_trash,
                                                      cb_data);
        }
        else
        {
            nautilus_file_operations_move (locations,
                                           relative_item_points,
                                           dest,
                                           parent_window,
                                           done_callback, done_callback_data);
        }
    }
    else
    {
        nautilus_file_operations_link (locations,
                                       relative_item_points,
                                       dest,
                                       parent_window,
                                       done_callback, done_callback_data);
    }

    g_list_free_full (locations, g_object_unref);
    if (dest)
    {
        g_object_unref (dest);
    }
}
