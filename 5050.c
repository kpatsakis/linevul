chkURLBuffer(Buffer *buf)
{
    static char *url_like_pat[] = {
	"https?://[a-zA-Z0-9][a-zA-Z0-9:%\\-\\./?=~_\\&+@#,\\$;]*[a-zA-Z0-9_/=\\-]",
	"file:/[a-zA-Z0-9:%\\-\\./=_\\+@#,\\$;]*",
#ifdef USE_GOPHER
	"gopher://[a-zA-Z0-9][a-zA-Z0-9:%\\-\\./_]*",
#endif				/* USE_GOPHER */
	"ftp://[a-zA-Z0-9][a-zA-Z0-9:%\\-\\./=_+@#,\\$]*[a-zA-Z0-9_/]",
#ifdef USE_NNTP
	"news:[^<> 	][^<> 	]*",
	"nntp://[a-zA-Z0-9][a-zA-Z0-9:%\\-\\./_]*",
#endif				/* USE_NNTP */
#ifndef USE_W3MMAILER		/* see also chkExternalURIBuffer() */
	"mailto:[^<> 	][^<> 	]*@[a-zA-Z0-9][a-zA-Z0-9\\-\\._]*[a-zA-Z0-9]",
#endif
#ifdef INET6
	"https?://[a-zA-Z0-9:%\\-\\./_@]*\\[[a-fA-F0-9:][a-fA-F0-9:\\.]*\\][a-zA-Z0-9:%\\-\\./?=~_\\&+@#,\\$;]*",
	"ftp://[a-zA-Z0-9:%\\-\\./_@]*\\[[a-fA-F0-9:][a-fA-F0-9:\\.]*\\][a-zA-Z0-9:%\\-\\./=_+@#,\\$]*",
#endif				/* INET6 */
	NULL
    };
    int i;
    for (i = 0; url_like_pat[i]; i++) {
	reAnchor(buf, url_like_pat[i]);
    }
#ifdef USE_EXTERNAL_URI_LOADER
    chkExternalURIBuffer(buf);
#endif
    buf->check_url |= CHK_URL;
}
