server_http_authenticate(struct server_config *srv_conf, struct client *clt)
{
	char			 decoded[1024];
	FILE			*fp = NULL;
	struct http_descriptor	*desc = clt->clt_descreq;
	const struct auth	*auth = srv_conf->auth;
	struct kv		*ba, key;
	size_t			 linesize = 0;
	ssize_t			 linelen;
	int			 ret = -1;
	char			*line = NULL, *user = NULL, *pass = NULL;
	char			*clt_user = NULL, *clt_pass = NULL;

	memset(decoded, 0, sizeof(decoded));
	key.kv_key = "Authorization";

	if ((ba = kv_find(&desc->http_headers, &key)) == NULL ||
	    ba->kv_value == NULL)
		goto done;

	if (strncmp(ba->kv_value, "Basic ", strlen("Basic ")) != 0)
		goto done;

	if (b64_pton(strchr(ba->kv_value, ' ') + 1, (uint8_t *)decoded,
	    sizeof(decoded)) <= 0)
		goto done;

	if ((clt_pass = strchr(decoded, ':')) == NULL)
		goto done;

	clt_user = decoded;
	*clt_pass++ = '\0';
	if ((clt->clt_remote_user = strdup(clt_user)) == NULL)
		goto done;

	if (clt_pass == NULL)
		goto done;

	if ((fp = fopen(auth->auth_htpasswd, "r")) == NULL)
		goto done;

	while ((linelen = getline(&line, &linesize, fp)) != -1) {
		if (line[linelen - 1] == '\n')
			line[linelen - 1] = '\0';
		user = line;
		pass = strchr(line, ':');

		if (pass == NULL) {
			explicit_bzero(line, linelen);
			continue;
		}

		*pass++ = '\0';

		if (strcmp(clt_user, user) != 0) {
			explicit_bzero(line, linelen);
			continue;
		}

		if (crypt_checkpass(clt_pass, pass) == 0) {
			explicit_bzero(line, linelen);
			ret = 0;
			break;
		}
	}
done:
	free(line);
	if (fp != NULL)
		fclose(fp);

	if (ba != NULL && ba->kv_value != NULL) {
		explicit_bzero(ba->kv_value, strlen(ba->kv_value));
		explicit_bzero(decoded, sizeof(decoded));
	}

	return (ret);
}
