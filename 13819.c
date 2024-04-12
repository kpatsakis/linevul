void DefragTrackerClearMemory(DefragTracker *dt)
{
    DefragTrackerFreeFrags(dt);
    SC_ATOMIC_DESTROY(dt->use_cnt);
}
