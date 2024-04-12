set_default_lang ()
{
  char *v;

  v = get_string_value ("LC_ALL");
  set_locale_var ("LC_ALL", v);

  v = get_string_value ("LANG");
  set_lang ("LANG", v);
}
