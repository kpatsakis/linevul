void DefragInitConfig(char quiet)
{
    SCLogDebug("initializing defrag engine...");

    memset(&defrag_config,  0, sizeof(defrag_config));
    SC_ATOMIC_INIT(defragtracker_counter);
    SC_ATOMIC_INIT(defrag_memuse);
    SC_ATOMIC_INIT(defragtracker_prune_idx);
    DefragTrackerQueueInit(&defragtracker_spare_q);

#ifndef AFLFUZZ_NO_RANDOM
    unsigned int seed = RandomTimePreseed();
    /* set defaults */
    defrag_config.hash_rand   = (int)(DEFRAG_DEFAULT_HASHSIZE * (rand_r(&seed) / RAND_MAX + 1.0));
#endif
    defrag_config.hash_size   = DEFRAG_DEFAULT_HASHSIZE;
    defrag_config.memcap      = DEFRAG_DEFAULT_MEMCAP;
    defrag_config.prealloc    = DEFRAG_DEFAULT_PREALLOC;

    /* Check if we have memcap and hash_size defined at config */
    char *conf_val;
    uint32_t configval = 0;

    /** set config values for memcap, prealloc and hash_size */
    if ((ConfGet("defrag.memcap", &conf_val)) == 1)
    {
        if (ParseSizeStringU64(conf_val, &defrag_config.memcap) < 0) {
            SCLogError(SC_ERR_SIZE_PARSE, "Error parsing defrag.memcap "
                       "from conf file - %s.  Killing engine",
                       conf_val);
            exit(EXIT_FAILURE);
        }
    }
    if ((ConfGet("defrag.hash-size", &conf_val)) == 1)
    {
        if (ByteExtractStringUint32(&configval, 10, strlen(conf_val),
                                    conf_val) > 0) {
            defrag_config.hash_size = configval;
        } else {
            WarnInvalidConfEntry("defrag.hash-size", "%"PRIu32, defrag_config.hash_size);
        }
    }


    if ((ConfGet("defrag.trackers", &conf_val)) == 1)
    {
        if (ByteExtractStringUint32(&configval, 10, strlen(conf_val),
                                    conf_val) > 0) {
            defrag_config.prealloc = configval;
        } else {
            WarnInvalidConfEntry("defrag.trackers", "%"PRIu32, defrag_config.prealloc);
        }
    }
    SCLogDebug("DefragTracker config from suricata.yaml: memcap: %"PRIu64", hash-size: "
               "%"PRIu32", prealloc: %"PRIu32, defrag_config.memcap,
               defrag_config.hash_size, defrag_config.prealloc);

    /* alloc hash memory */
    uint64_t hash_size = defrag_config.hash_size * sizeof(DefragTrackerHashRow);
    if (!(DEFRAG_CHECK_MEMCAP(hash_size))) {
        SCLogError(SC_ERR_DEFRAG_INIT, "allocating defrag hash failed: "
                "max defrag memcap is smaller than projected hash size. "
                "Memcap: %"PRIu64", Hash table size %"PRIu64". Calculate "
                "total hash size by multiplying \"defrag.hash-size\" with %"PRIuMAX", "
                "which is the hash bucket size.", defrag_config.memcap, hash_size,
                (uintmax_t)sizeof(DefragTrackerHashRow));
        exit(EXIT_FAILURE);
    }
    defragtracker_hash = SCCalloc(defrag_config.hash_size, sizeof(DefragTrackerHashRow));
    if (unlikely(defragtracker_hash == NULL)) {
        SCLogError(SC_ERR_FATAL, "Fatal error encountered in DefragTrackerInitConfig. Exiting...");
        exit(EXIT_FAILURE);
    }
    memset(defragtracker_hash, 0, defrag_config.hash_size * sizeof(DefragTrackerHashRow));

    uint32_t i = 0;
    for (i = 0; i < defrag_config.hash_size; i++) {
        DRLOCK_INIT(&defragtracker_hash[i]);
    }
    (void) SC_ATOMIC_ADD(defrag_memuse, (defrag_config.hash_size * sizeof(DefragTrackerHashRow)));

    if (quiet == FALSE) {
        SCLogConfig("allocated %llu bytes of memory for the defrag hash... "
                  "%" PRIu32 " buckets of size %" PRIuMAX "",
                  SC_ATOMIC_GET(defrag_memuse), defrag_config.hash_size,
                  (uintmax_t)sizeof(DefragTrackerHashRow));
    }

    if ((ConfGet("defrag.prealloc", &conf_val)) == 1)
    {
        if (ConfValIsTrue(conf_val)) {
            /* pre allocate defrag trackers */
            for (i = 0; i < defrag_config.prealloc; i++) {
                if (!(DEFRAG_CHECK_MEMCAP(sizeof(DefragTracker)))) {
                    SCLogError(SC_ERR_DEFRAG_INIT, "preallocating defrag trackers failed: "
                            "max defrag memcap reached. Memcap %"PRIu64", "
                            "Memuse %"PRIu64".", defrag_config.memcap,
                            ((uint64_t)SC_ATOMIC_GET(defrag_memuse) + (uint64_t)sizeof(DefragTracker)));
                    exit(EXIT_FAILURE);
                }

                DefragTracker *h = DefragTrackerAlloc();
                if (h == NULL) {
                    SCLogError(SC_ERR_DEFRAG_INIT, "preallocating defrag failed: %s", strerror(errno));
                    exit(EXIT_FAILURE);
                }
                DefragTrackerEnqueue(&defragtracker_spare_q,h);
            }
            if (quiet == FALSE) {
                SCLogConfig("preallocated %" PRIu32 " defrag trackers of size %" PRIuMAX "",
                        defragtracker_spare_q.len, (uintmax_t)sizeof(DefragTracker));
            }
        }
    }

    if (quiet == FALSE) {
        SCLogConfig("defrag memory usage: %llu bytes, maximum: %"PRIu64,
                SC_ATOMIC_GET(defrag_memuse), defrag_config.memcap);
    }

    return;
}
