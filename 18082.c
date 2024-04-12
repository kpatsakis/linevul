xmlCleanURI(xmlURIPtr uri) {
 if (uri == NULL) return;

 if (uri->scheme != NULL) xmlFree(uri->scheme);
    uri->scheme = NULL;
 if (uri->server != NULL) xmlFree(uri->server);
    uri->server = NULL;
 if (uri->user != NULL) xmlFree(uri->user);
    uri->user = NULL;
 if (uri->path != NULL) xmlFree(uri->path);
    uri->path = NULL;
 if (uri->fragment != NULL) xmlFree(uri->fragment);
    uri->fragment = NULL;
 if (uri->opaque != NULL) xmlFree(uri->opaque);
    uri->opaque = NULL;
 if (uri->authority != NULL) xmlFree(uri->authority);
    uri->authority = NULL;
 if (uri->query != NULL) xmlFree(uri->query);
    uri->query = NULL;
 if (uri->query_raw != NULL) xmlFree(uri->query_raw);
    uri->query_raw = NULL;
}
