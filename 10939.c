int index_directory(char *dir, char *title)
{
    struct dirent *dirbuf;
    int numdir;
    struct dirent **array;
    struct stat statbuf;
    char http_filename[MAX_FILE_LENGTH * 3];
    char html_filename[MAX_FILE_LENGTH * 6];
    char escaped_filename[MAX_FILE_LENGTH * 18]; /* *both* http and html escape */
    int i;

    if (chdir(dir) == -1) {
        send_error(3);
        return -1;
    }
    numdir = scandir(".", &array, select_files, alphasort);
    if (numdir == -1) {
        send_error(2);
        return -1;
    } else if (numdir == -2) {
        send_error(6);
        return -1;
    }

    if (html_escape_string(title, html_filename, strlen(title)) == NULL) {
        send_error(4);
        return -1;
    }

    printf("<html>\n"
           "<head>\n<title>Index of %s</title>\n</head>\n\n"
           "<body bgcolor=\"#ffffff\">\n"
           "<H2>Index of %s</H2>\n"
           "<table>\n%s",
           html_filename, html_filename,
           (strcmp(title, "/") == 0 ? "" :
            "<tr><td colspan=3><h3>Directories</h3></td></tr>"
            "<tr><td colspan=3><a href=\"../\">Parent Directory</a></td></tr>\n"));

    for (i = 0; i < numdir; ++i) {
        dirbuf = array[i];

        if (stat(dirbuf->d_name, &statbuf) == -1)
            continue;

        if (!S_ISDIR(statbuf.st_mode))
            continue;

        if (html_escape_string(dirbuf->d_name, html_filename,
                               NAMLEN(dirbuf)) == NULL) {
            send_error(4);
            return -1;
        }
        if (http_escape_string(dirbuf->d_name, http_filename,
                               NAMLEN(dirbuf)) == NULL) {
            send_error(4);
            return -1;
        }
        if (html_escape_string(http_filename, escaped_filename,
                               strlen(http_filename)) == NULL) {
            send_error(4);
            return -1;
        }
        printf("<tr>"
               "<td width=\"40%%\"><a href=\"%s/\">%s/</a></td>"
               "<td align=right>%s</td>"
               "<td align=right>"
               PRINTF_OFF_T_ARG
               " bytes</td>"
               "</tr>\n",
               escaped_filename, html_filename,
               ctime(&statbuf.st_mtime), (off_t) statbuf.st_size);
    }

    printf
        ("<tr><td colspan=3>&nbsp;</td></tr>\n<tr><td colspan=3><h3>Files</h3></td></tr>\n");

    for (i = 0; i < numdir; ++i) {
        int len;
        dirbuf = array[i];

        if (stat(dirbuf->d_name, &statbuf) == -1)
            continue;


        if (S_ISDIR(statbuf.st_mode))
            continue;

        if (html_escape_string(dirbuf->d_name, html_filename,
                               NAMLEN(dirbuf)) == NULL) {
            send_error(4);
            return -1;
        }
        if (http_escape_string(dirbuf->d_name, http_filename,
                               NAMLEN(dirbuf)) == NULL) {
            send_error(4);
            return -1;
        }

        len = strlen(http_filename);
#ifdef GUNZIP
        if (len > 3 && !memcmp(http_filename + len - 3, ".gz", 3)) {
            http_filename[len - 3] = '\0';
            html_filename[strlen(html_filename) - 3] = '\0';
            if (html_escape_string(http_filename, escaped_filename,
                                   strlen(http_filename)) == NULL) {
                send_error(4);
                return -1;
            }

            printf("<tr>"
                   "<td width=\"40%%\"><a href=\"%s\">%s</a> "
                   "<a href=\"%s.gz\">(.gz)</a></td>"
                   "<td align=right>%s</td>"
                   "<td align=right>"
                   PRINTF_OFF_T_ARG
                   "bytes</td>"
                   "</tr>\n",
                   escaped_filename, html_filename, http_filename,
                   ctime(&statbuf.st_mtime), (off_t) statbuf.st_size);
        } else {
#endif
            if (html_escape_string(http_filename, escaped_filename,
                                   strlen(http_filename)) == NULL) {
                send_error(4);
                return -1;
            }
            printf("<tr>"
                   "<td width=\"40%%\"><a href=\"%s\">%s</a></td>"
                   "<td align=right>%s</td>"
                   "<td align=right>"
                   PRINTF_OFF_T_ARG
                   "bytes</td>"
                   "</tr>\n",
                   escaped_filename, html_filename,
                   ctime(&statbuf.st_mtime), (off_t) statbuf.st_size);
#ifdef GUNZIP
        }
#endif
    }
    /* hey -- even though this is a one-shot deal, we should
     * still free memory we ought to free
     * You never know -- this code might get used elsewhere!
     */
    for (i = 0; i < numdir; ++i) {
        free(array[i]);
        array[i] = NULL;
    }
    free(array);
    array = NULL;

    return 0;                   /* success */
}
