nautilus_mime_types_group_get_name (gint group_index)
{
    g_return_val_if_fail (group_index < G_N_ELEMENTS (mimetype_groups), NULL);

    return gettext (mimetype_groups[group_index].name);
}
