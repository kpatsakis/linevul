alloc_value_block(void (*alloc_func) (vector_t *), const char *block_type)
{
	char *buf;
	char *str = NULL;
	vector_t *vec = NULL;
	bool first_line = true;

	buf = (char *) MALLOC(MAXBUF);
	while (read_line(buf, MAXBUF)) {
		if (!(vec = alloc_strvec(buf)))
			continue;

		if (first_line) {
			first_line = false;

			if (!strcmp(vector_slot(vec, 0), BOB)) {
				free_strvec(vec);
				continue;
			}

			log_message(LOG_INFO, "'%s' missing from beginning of block %s", BOB, block_type);
		}

		str = vector_slot(vec, 0);
		if (!strcmp(str, EOB)) {
			free_strvec(vec);
			break;
		}

		if (vector_size(vec))
			(*alloc_func) (vec);

		free_strvec(vec);
	}
	FREE(buf);
}
