rad_auth_open(void)
{
	struct rad_handle *h;

	h = (struct rad_handle *)malloc(sizeof(struct rad_handle));
	if (h != NULL) {
		TSRMLS_FETCH();
		php_srand(time(NULL) * getpid() * (unsigned long) (php_combined_lcg(TSRMLS_C) * 10000.0) TSRMLS_CC);
		h->fd = -1;
		h->num_servers = 0;
		h->ident = php_rand(TSRMLS_C);
		h->errmsg[0] = '\0';
		memset(h->pass, 0, sizeof h->pass);
		h->pass_len = 0;
		h->pass_pos = 0;
		h->chap_pass = 0;
		h->type = RADIUS_AUTH;
        h->request_created = 0;        
	}
	return h;
}
