static void save_text_from_text_view(GtkTextView *tv, const char *name)
{
    gchar *new_str = get_malloced_string_from_text_view(tv);
    save_text_if_changed(name, new_str);
    free(new_str);
}
