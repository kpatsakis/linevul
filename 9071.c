static void save_edited_one_liner(GtkCellRendererText *renderer,
                gchar *tree_path,
                gchar *new_text,
                gpointer user_data)
{

    GtkTreeIter iter;
    if (!gtk_tree_model_get_iter_from_string(GTK_TREE_MODEL(g_ls_details), &iter, tree_path))
        return;
    gchar *item_name = NULL;
    gtk_tree_model_get(GTK_TREE_MODEL(g_ls_details), &iter,
                DETAIL_COLUMN_NAME, &item_name,
                -1);
    if (!item_name) /* paranoia, should never happen */
        return;
    struct problem_item *item = problem_data_get_item_or_NULL(g_cd, item_name);
    if (item && (item->flags & CD_FLAG_ISEDITABLE))
    {
        struct dump_dir *dd = wizard_open_directory_for_writing(g_dump_dir_name);
        if (dd)
        {
            dd_save_text(dd, item_name, new_text);
            free(item->content);
            item->content = xstrdup(new_text);
            gtk_list_store_set(g_ls_details, &iter,
                    DETAIL_COLUMN_VALUE, new_text,
                    -1);
        }
        dd_close(dd);
    }
}
