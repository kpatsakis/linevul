static int _sx_sasl_process(sx_t s, sx_plugin_t p, nad_t nad) {
    Gsasl_session *sd = (Gsasl_session *) s->plugin_data[p->index];
    int attr;
    char mech[128];
    sx_error_t sxe;
    int flags;
    char *ns = NULL, *to = NULL, *from = NULL, *version = NULL;

    /* only want sasl packets */
    if(NAD_ENS(nad, 0) < 0 || NAD_NURI_L(nad, NAD_ENS(nad, 0)) != strlen(uri_SASL) || strncmp(NAD_NURI(nad, NAD_ENS(nad, 0)), uri_SASL, strlen(uri_SASL)) != 0)
        return 1;

    /* quietly drop it if sasl is disabled, or if not ready */
    if(s->state != state_STREAM) {
        _sx_debug(ZONE, "not correct state for sasl, ignoring");
        nad_free(nad);
        return 0;
    }

    /* packets from the client */
    if(s->type == type_SERVER) {
        if(!(s->flags & SX_SASL_OFFER)) {
            _sx_debug(ZONE, "they tried to do sasl, but we never offered it, ignoring");
            nad_free(nad);
            return 0;
        }

#ifdef HAVE_SSL
        if((s->flags & SX_SSL_STARTTLS_REQUIRE) && s->ssf == 0) {
            _sx_debug(ZONE, "they tried to do sasl, but they have to do starttls first, ignoring");
            nad_free(nad);
            return 0;
        }
#endif

        /* auth */
        if(NAD_ENAME_L(nad, 0) == 4 && strncmp("auth", NAD_ENAME(nad, 0), NAD_ENAME_L(nad, 0)) == 0) {
            /* require mechanism */
            if((attr = nad_find_attr(nad, 0, -1, "mechanism", NULL)) < 0) {
                _sx_nad_write(s, _sx_sasl_failure(s, _sasl_err_INVALID_MECHANISM, NULL), 0);
                nad_free(nad);
                return 0;
            }

            /* extract */
            snprintf(mech, 127, "%.*s", NAD_AVAL_L(nad, attr), NAD_AVAL(nad, attr));

            /* go */
            _sx_sasl_client_process(s, p, sd, mech, NAD_CDATA(nad, 0), NAD_CDATA_L(nad, 0));

            nad_free(nad);
            return 0;
        }

        /* response */
        else if(NAD_ENAME_L(nad, 0) == 8 && strncmp("response", NAD_ENAME(nad, 0), NAD_ENAME_L(nad, 0)) == 0) {
            /* process it */
            _sx_sasl_client_process(s, p, sd, NULL, NAD_CDATA(nad, 0), NAD_CDATA_L(nad, 0));

            nad_free(nad);
            return 0;
        }

        /* abort */
        else if(NAD_ENAME_L(nad, 0) == 5 && strncmp("abort", NAD_ENAME(nad, 0), NAD_ENAME_L(nad, 0)) == 0) {
            _sx_debug(ZONE, "sasl handshake aborted");

            _sx_nad_write(s, _sx_sasl_failure(s, _sasl_err_ABORTED, NULL), 0);

            nad_free(nad);
            return 0;
        }
    }

    /* packets from the server */
    else if(s->type == type_CLIENT) {
        if(sd == NULL) {
            _sx_debug(ZONE, "got sasl client packets, but they never started sasl, ignoring");
            nad_free(nad);
            return 0;
        }

        /* challenge */
        if(NAD_ENAME_L(nad, 0) == 9 && strncmp("challenge", NAD_ENAME(nad, 0), NAD_ENAME_L(nad, 0)) == 0) {
            /* process it */
            _sx_sasl_server_process(s, p, sd, NAD_CDATA(nad, 0), NAD_CDATA_L(nad, 0));

            nad_free(nad);
            return 0;
        }

        /* success */
        else if(NAD_ENAME_L(nad, 0) == 7 && strncmp("success", NAD_ENAME(nad, 0), NAD_ENAME_L(nad, 0)) == 0) {
            _sx_debug(ZONE, "sasl handshake completed, resetting");
            nad_free(nad);

            /* save interesting bits */
            flags = s->flags;

            if(s->ns != NULL) ns = strdup(s->ns);

            if(s->req_to != NULL) to = strdup(s->req_to);
            if(s->req_from != NULL) from = strdup(s->req_from);
            if(s->req_version != NULL) version = strdup(s->req_version);

            /* reset state */
            _sx_reset(s);

            _sx_debug(ZONE, "restarting stream with sasl layer established");

            /* second time round */
            sx_client_init(s, flags, ns, to, from, version);

            /* free bits */
            if(ns != NULL) free(ns);
            if(to != NULL) free(to);
            if(from != NULL) free(from);
            if(version != NULL) free(version);

            return 0;
        }

        /* failure */
        else if(NAD_ENAME_L(nad, 0) == 7 && strncmp("failure", NAD_ENAME(nad, 0), NAD_ENAME_L(nad, 0)) == 0) {
            /* fire the error */
            _sx_gen_error(sxe, SX_ERR_AUTH, "Authentication failed", NULL);
            _sx_event(s, event_ERROR, (void *) &sxe);

            /* cleanup */
            gsasl_finish(sd);

            s->plugin_data[p->index] = NULL;

            nad_free(nad);
            return 0;
        }
    }

    /* invalid sasl command, quietly drop it */
    _sx_debug(ZONE, "unknown sasl command '%.*s', ignoring", NAD_ENAME_L(nad, 0), NAD_ENAME(nad, 0));

    nad_free(nad);
    return 0;
}
