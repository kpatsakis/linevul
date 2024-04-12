create_socket_name (const char *template)
{
  char *name, *p;
  size_t len;

  /* Prepend the tmp directory to the template.  */
  p = getenv ("TMPDIR");
  if (!p || !*p)
    p = "/tmp";

  len = strlen (p) + strlen (template) + 2;
  name = xcharalloc (len);
  memset (name, 0, len);
  memcpy (name, p, strlen (p));
  if (p[strlen (p) - 1] != '/')
    name = strcat (name, "/");
  name = strcat (name, template);

  p = strrchr (name, '/');
  *p = '\0';
  if (!mkdtemp (name))
    {
      free (name);
      return NULL;
    }
  *p = '/';
  return name;
}
