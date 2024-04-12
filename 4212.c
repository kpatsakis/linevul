DefragContextNew(void)
{
    DefragContext *dc;

    dc = SCCalloc(1, sizeof(*dc));
    if (unlikely(dc == NULL))
        return NULL;

    /* Initialize the pool of trackers. */
    intmax_t tracker_pool_size;
    if (!ConfGetInt("defrag.trackers", &tracker_pool_size) || tracker_pool_size == 0) {
        tracker_pool_size = DEFAULT_DEFRAG_HASH_SIZE;
    }

    /* Initialize the pool of frags. */
    intmax_t frag_pool_size;
    if (!ConfGetInt("defrag.max-frags", &frag_pool_size) || frag_pool_size == 0) {
        frag_pool_size = DEFAULT_DEFRAG_POOL_SIZE;
    }
    intmax_t frag_pool_prealloc = frag_pool_size / 2;
    dc->frag_pool = PoolInit(frag_pool_size, frag_pool_prealloc,
        sizeof(Frag),
        NULL, DefragFragInit, dc, NULL, NULL);
    if (dc->frag_pool == NULL) {
        SCLogError(SC_ERR_MEM_ALLOC,
            "Defrag: Failed to initialize fragment pool.");
        exit(EXIT_FAILURE);
    }
    if (SCMutexInit(&dc->frag_pool_lock, NULL) != 0) {
        SCLogError(SC_ERR_MUTEX,
            "Defrag: Failed to initialize frag pool mutex.");
        exit(EXIT_FAILURE);
    }

    /* Set the default timeout. */
    intmax_t timeout;
    if (!ConfGetInt("defrag.timeout", &timeout)) {
        dc->timeout = TIMEOUT_DEFAULT;
    }
    else {
        if (timeout < TIMEOUT_MIN) {
            SCLogError(SC_ERR_INVALID_ARGUMENT,
                "defrag: Timeout less than minimum allowed value.");
            exit(EXIT_FAILURE);
        }
        else if (timeout > TIMEOUT_MAX) {
            SCLogError(SC_ERR_INVALID_ARGUMENT,
                "defrag: Tiemout greater than maximum allowed value.");
            exit(EXIT_FAILURE);
        }
        dc->timeout = timeout;
    }

    SCLogDebug("Defrag Initialized:");
    SCLogDebug("\tTimeout: %"PRIuMAX, (uintmax_t)dc->timeout);
    SCLogDebug("\tMaximum defrag trackers: %"PRIuMAX, tracker_pool_size);
    SCLogDebug("\tPreallocated defrag trackers: %"PRIuMAX, tracker_pool_size);
    SCLogDebug("\tMaximum fragments: %"PRIuMAX, (uintmax_t)frag_pool_size);
    SCLogDebug("\tPreallocated fragments: %"PRIuMAX, (uintmax_t)frag_pool_prealloc);

    return dc;
}
