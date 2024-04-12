    MockFrontend()
        : last_host_id_(-222), last_cache_id_(-222),
          last_status_(APPCACHE_STATUS_OBSOLETE),
          last_status_changed_(APPCACHE_STATUS_OBSOLETE),
          last_event_id_(APPCACHE_OBSOLETE_EVENT),
          content_blocked_(false) {
    }
