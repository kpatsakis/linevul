local char *justname(char *path)
{
    char *p;

    p = strrchr(path, '/');
    return p == NULL ? path : p + 1;
}
