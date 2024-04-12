pgp_free_blob(pgp_blob_t *blob)
{
	if (blob) {
		if (blob->parent) {
			pgp_blob_t **p;

			/* remove blob from list of parent's children */
			for (p = &blob->parent->files; *p != NULL && *p != blob; p = &(*p)->next)
				;
			if (*p == blob)
				*p = blob->next;
		}

		sc_file_free(blob->file);
		if (blob->data)
			free(blob->data);
		free(blob);
	}
}
