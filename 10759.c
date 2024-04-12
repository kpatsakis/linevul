void dns_resolve_domain(s2s_t s2s, dnscache_t dns) {
    dnsquery_t query = (dnsquery_t) calloc(1, sizeof(struct dnsquery_st));

    query->s2s = s2s;
    query->results = xhash_new(71);
    if (idna_to_ascii_8z(dns->name, &query->name, 0) != IDNA_SUCCESS) {
        log_write(s2s->log, LOG_ERR, "idna dns encode for %s failed", dns->name);
        /* shortcut resolution failure */
        query->expiry = time(NULL) + 99999999;
        out_resolve(query->s2s, dns->name, query->results, query->expiry);
        return;
    }
    query->hosts = xhash_new(71);
    query->srv_i = -1;
    query->expiry = 0;
    query->cur_host = NULL;
    query->cur_port = 0;
    query->cur_expiry = 0;
    query->query = NULL;
    dns->query = query;

    log_debug(ZONE, "dns resolve for %s@%p started", query->name, query);

    /* - resolve all SRV records to host/port
     * - if no results, include domain/5269
     * - resolve all host/port combinations
     * - return result
     */
    _dns_result_srv(NULL, NULL, query);
}
