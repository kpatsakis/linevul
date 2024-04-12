void DefragTrackerMoveToSpare(DefragTracker *h)
{
    DefragTrackerEnqueue(&defragtracker_spare_q, h);
    (void) SC_ATOMIC_SUB(defragtracker_counter, 1);
}
