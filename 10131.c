static const char *baseFilename(const char *filename) {
    const char *cur;
    if (filename == NULL)
        return(NULL);
    cur = &filename[strlen(filename)];
    while ((cur > filename) && (*cur != '/'))
        cur--;
    if (*cur == '/')
        return(cur + 1);
    return(cur);
}
