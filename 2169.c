void DefragTrackerFree(DefragTracker *dt)
{
    if (dt != NULL) {
        DefragTrackerClearMemory(dt);

        SCMutexDestroy(&dt->lock);
        SCFree(dt);
        (void) SC_ATOMIC_SUB(defrag_memuse, sizeof(DefragTracker));
    }
}
