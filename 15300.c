static GIOStatus irssi_ssl_write(GIOChannel *handle, const gchar *buf, gsize len, gsize *ret, GError **gerr)
{
	GIOSSLChannel *chan = (GIOSSLChannel *)handle;
	gint ret1, err;
	const char *errstr;

	ret1 = SSL_write(chan->ssl, (const char *)buf, len);
	if(ret1 <= 0)
	{
		*ret = 0;
		err = SSL_get_error(chan->ssl, ret1);
		if(err == SSL_ERROR_WANT_READ || err == SSL_ERROR_WANT_WRITE)
			return G_IO_STATUS_AGAIN;
		else if(err == SSL_ERROR_ZERO_RETURN)
			errstr = "server closed connection";
		else if (err == SSL_ERROR_SYSCALL)
		{
			errstr = ERR_reason_error_string(ERR_get_error());
			if (errstr == NULL && ret1 == -1)
				errstr = strerror(errno);
			if (errstr == NULL)
				errstr = "server closed connection unexpectedly";
		}
		else
		{
			errstr = ERR_reason_error_string(ERR_get_error());
			if (errstr == NULL)
				errstr = "unknown SSL error";
		}
		g_warning("SSL write error: %s", errstr);
		*gerr = g_error_new_literal(G_IO_CHANNEL_ERROR, G_IO_CHANNEL_ERROR_FAILED,
					    errstr);
		return G_IO_STATUS_ERROR;
	}
	else
	{
		*ret = ret1;
		return G_IO_STATUS_NORMAL;
	}
	/*UNREACH*/
	return G_IO_STATUS_ERROR;
}
