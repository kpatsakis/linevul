void initServerConfig(void) {
    int j;

    getRandomHexChars(server.runid,CONFIG_RUN_ID_SIZE);
    server.configfile = NULL;
    server.executable = NULL;
    server.hz = CONFIG_DEFAULT_HZ;
    server.runid[CONFIG_RUN_ID_SIZE] = '\0';
    server.arch_bits = (sizeof(long) == 8) ? 64 : 32;
    server.port = CONFIG_DEFAULT_SERVER_PORT;
    server.tcp_backlog = CONFIG_DEFAULT_TCP_BACKLOG;
    server.bindaddr_count = 0;
    server.unixsocket = NULL;
    server.unixsocketperm = CONFIG_DEFAULT_UNIX_SOCKET_PERM;
    server.ipfd_count = 0;
    server.sofd = -1;
    server.protected_mode = CONFIG_DEFAULT_PROTECTED_MODE;
    server.dbnum = CONFIG_DEFAULT_DBNUM;
    server.verbosity = CONFIG_DEFAULT_VERBOSITY;
    server.maxidletime = CONFIG_DEFAULT_CLIENT_TIMEOUT;
    server.tcpkeepalive = CONFIG_DEFAULT_TCP_KEEPALIVE;
    server.active_expire_enabled = 1;
    server.client_max_querybuf_len = PROTO_MAX_QUERYBUF_LEN;
    server.saveparams = NULL;
    server.loading = 0;
    server.logfile = zstrdup(CONFIG_DEFAULT_LOGFILE);
    server.syslog_enabled = CONFIG_DEFAULT_SYSLOG_ENABLED;
    server.syslog_ident = zstrdup(CONFIG_DEFAULT_SYSLOG_IDENT);
    server.syslog_facility = LOG_LOCAL0;
    server.daemonize = CONFIG_DEFAULT_DAEMONIZE;
    server.supervised = 0;
    server.supervised_mode = SUPERVISED_NONE;
    server.aof_state = AOF_OFF;
    server.aof_fsync = CONFIG_DEFAULT_AOF_FSYNC;
    server.aof_no_fsync_on_rewrite = CONFIG_DEFAULT_AOF_NO_FSYNC_ON_REWRITE;
    server.aof_rewrite_perc = AOF_REWRITE_PERC;
    server.aof_rewrite_min_size = AOF_REWRITE_MIN_SIZE;
    server.aof_rewrite_base_size = 0;
    server.aof_rewrite_scheduled = 0;
    server.aof_last_fsync = time(NULL);
    server.aof_rewrite_time_last = -1;
    server.aof_rewrite_time_start = -1;
    server.aof_lastbgrewrite_status = C_OK;
    server.aof_delayed_fsync = 0;
    server.aof_fd = -1;
    server.aof_selected_db = -1; /* Make sure the first time will not match */
    server.aof_flush_postponed_start = 0;
    server.aof_rewrite_incremental_fsync = CONFIG_DEFAULT_AOF_REWRITE_INCREMENTAL_FSYNC;
    server.aof_load_truncated = CONFIG_DEFAULT_AOF_LOAD_TRUNCATED;
    server.pidfile = NULL;
    server.rdb_filename = zstrdup(CONFIG_DEFAULT_RDB_FILENAME);
    server.aof_filename = zstrdup(CONFIG_DEFAULT_AOF_FILENAME);
    server.requirepass = NULL;
    server.rdb_compression = CONFIG_DEFAULT_RDB_COMPRESSION;
    server.rdb_checksum = CONFIG_DEFAULT_RDB_CHECKSUM;
    server.stop_writes_on_bgsave_err = CONFIG_DEFAULT_STOP_WRITES_ON_BGSAVE_ERROR;
    server.activerehashing = CONFIG_DEFAULT_ACTIVE_REHASHING;
    server.notify_keyspace_events = 0;
    server.maxclients = CONFIG_DEFAULT_MAX_CLIENTS;
    server.bpop_blocked_clients = 0;
    server.maxmemory = CONFIG_DEFAULT_MAXMEMORY;
    server.maxmemory_policy = CONFIG_DEFAULT_MAXMEMORY_POLICY;
    server.maxmemory_samples = CONFIG_DEFAULT_MAXMEMORY_SAMPLES;
    server.hash_max_ziplist_entries = OBJ_HASH_MAX_ZIPLIST_ENTRIES;
    server.hash_max_ziplist_value = OBJ_HASH_MAX_ZIPLIST_VALUE;
    server.list_max_ziplist_size = OBJ_LIST_MAX_ZIPLIST_SIZE;
    server.list_compress_depth = OBJ_LIST_COMPRESS_DEPTH;
    server.set_max_intset_entries = OBJ_SET_MAX_INTSET_ENTRIES;
    server.zset_max_ziplist_entries = OBJ_ZSET_MAX_ZIPLIST_ENTRIES;
    server.zset_max_ziplist_value = OBJ_ZSET_MAX_ZIPLIST_VALUE;
    server.hll_sparse_max_bytes = CONFIG_DEFAULT_HLL_SPARSE_MAX_BYTES;
    server.shutdown_asap = 0;
    server.repl_ping_slave_period = CONFIG_DEFAULT_REPL_PING_SLAVE_PERIOD;
    server.repl_timeout = CONFIG_DEFAULT_REPL_TIMEOUT;
    server.repl_min_slaves_to_write = CONFIG_DEFAULT_MIN_SLAVES_TO_WRITE;
    server.repl_min_slaves_max_lag = CONFIG_DEFAULT_MIN_SLAVES_MAX_LAG;
    server.cluster_enabled = 0;
    server.cluster_node_timeout = CLUSTER_DEFAULT_NODE_TIMEOUT;
    server.cluster_migration_barrier = CLUSTER_DEFAULT_MIGRATION_BARRIER;
    server.cluster_slave_validity_factor = CLUSTER_DEFAULT_SLAVE_VALIDITY;
    server.cluster_require_full_coverage = CLUSTER_DEFAULT_REQUIRE_FULL_COVERAGE;
    server.cluster_configfile = zstrdup(CONFIG_DEFAULT_CLUSTER_CONFIG_FILE);
    server.migrate_cached_sockets = dictCreate(&migrateCacheDictType,NULL);
    server.next_client_id = 1; /* Client IDs, start from 1 .*/
    server.loading_process_events_interval_bytes = (1024*1024*2);

    server.lruclock = getLRUClock();
    resetServerSaveParams();

    appendServerSaveParams(60*60,1);  /* save after 1 hour and 1 change */
    appendServerSaveParams(300,100);  /* save after 5 minutes and 100 changes */
    appendServerSaveParams(60,10000); /* save after 1 minute and 10000 changes */
    /* Replication related */
    server.masterauth = NULL;
    server.masterhost = NULL;
    server.masterport = 6379;
    server.master = NULL;
    server.cached_master = NULL;
    server.repl_master_initial_offset = -1;
    server.repl_state = REPL_STATE_NONE;
    server.repl_syncio_timeout = CONFIG_REPL_SYNCIO_TIMEOUT;
    server.repl_serve_stale_data = CONFIG_DEFAULT_SLAVE_SERVE_STALE_DATA;
    server.repl_slave_ro = CONFIG_DEFAULT_SLAVE_READ_ONLY;
    server.repl_down_since = 0; /* Never connected, repl is down since EVER. */
    server.repl_disable_tcp_nodelay = CONFIG_DEFAULT_REPL_DISABLE_TCP_NODELAY;
    server.repl_diskless_sync = CONFIG_DEFAULT_REPL_DISKLESS_SYNC;
    server.repl_diskless_sync_delay = CONFIG_DEFAULT_REPL_DISKLESS_SYNC_DELAY;
    server.slave_priority = CONFIG_DEFAULT_SLAVE_PRIORITY;
    server.slave_announce_ip = CONFIG_DEFAULT_SLAVE_ANNOUNCE_IP;
    server.slave_announce_port = CONFIG_DEFAULT_SLAVE_ANNOUNCE_PORT;
    server.master_repl_offset = 0;

    /* Replication partial resync backlog */
    server.repl_backlog = NULL;
    server.repl_backlog_size = CONFIG_DEFAULT_REPL_BACKLOG_SIZE;
    server.repl_backlog_histlen = 0;
    server.repl_backlog_idx = 0;
    server.repl_backlog_off = 0;
    server.repl_backlog_time_limit = CONFIG_DEFAULT_REPL_BACKLOG_TIME_LIMIT;
    server.repl_no_slaves_since = time(NULL);

    /* Client output buffer limits */
    for (j = 0; j < CLIENT_TYPE_OBUF_COUNT; j++)
        server.client_obuf_limits[j] = clientBufferLimitsDefaults[j];

    /* Double constants initialization */
    R_Zero = 0.0;
    R_PosInf = 1.0/R_Zero;
    R_NegInf = -1.0/R_Zero;
    R_Nan = R_Zero/R_Zero;

    /* Command table -- we initiialize it here as it is part of the
     * initial configuration, since command names may be changed via
     * redis.conf using the rename-command directive. */
    server.commands = dictCreate(&commandTableDictType,NULL);
    server.orig_commands = dictCreate(&commandTableDictType,NULL);
    populateCommandTable();
    server.delCommand = lookupCommandByCString("del");
    server.multiCommand = lookupCommandByCString("multi");
    server.lpushCommand = lookupCommandByCString("lpush");
    server.lpopCommand = lookupCommandByCString("lpop");
    server.rpopCommand = lookupCommandByCString("rpop");
    server.sremCommand = lookupCommandByCString("srem");
    server.execCommand = lookupCommandByCString("exec");

    /* Slow log */
    server.slowlog_log_slower_than = CONFIG_DEFAULT_SLOWLOG_LOG_SLOWER_THAN;
    server.slowlog_max_len = CONFIG_DEFAULT_SLOWLOG_MAX_LEN;

    /* Latency monitor */
    server.latency_monitor_threshold = CONFIG_DEFAULT_LATENCY_MONITOR_THRESHOLD;

    /* Debugging */
    server.assert_failed = "<no assertion failed>";
    server.assert_file = "<no file>";
    server.assert_line = 0;
    server.bug_report_start = 0;
    server.watchdog_period = 0;
}
