delete_file(struct mg_connection *conn, const char *path)
{
	struct de de;
	memset(&de.file, 0, sizeof(de.file));
	if (!mg_stat(conn, path, &de.file)) {
		/* mg_stat returns 0 if the file does not exist */
		mg_send_http_error(conn,
		                   404,
		                   "Error: Cannot delete file\nFile %s not found",
		                   path);
		return;
	}

#if 0 /* Ignore if a file in memory is inside a folder */
        if (de.access.membuf != NULL) {
                /* the file is cached in memory */
                mg_send_http_error(
                    conn,
                    405,
                    "Error: Delete not possible\nDeleting %s is not supported",
                    path);
                return;
        }
#endif

	if (de.file.is_directory) {
		if (remove_directory(conn, path)) {
			/* Delete is successful: Return 204 without content. */
			mg_send_http_error(conn, 204, "%s", "");
		} else {
			/* Delete is not successful: Return 500 (Server error). */
			mg_send_http_error(conn, 500, "Error: Could not delete %s", path);
		}
		return;
	}

	/* This is an existing file (not a directory).
	 * Check if write permission is granted. */
	if (access(path, W_OK) != 0) {
		/* File is read only */
		mg_send_http_error(
		    conn,
		    403,
		    "Error: Delete not possible\nDeleting %s is not allowed",
		    path);
		return;
	}

	/* Try to delete it. */
	if (mg_remove(conn, path) == 0) {
		/* Delete was successful: Return 204 without content. */
		mg_send_http_error(conn, 204, "%s", "");
	} else {
		/* Delete not successful (file locked). */
		mg_send_http_error(conn,
		                   423,
		                   "Error: Cannot delete file\nremove(%s): %s",
		                   path,
		                   strerror(ERRNO));
	}
}
