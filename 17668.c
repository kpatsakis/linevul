static void IRQ_check(OpenPICState *opp, IRQQueue *q)
{
    int irq = -1;
    int next = -1;
    int priority = -1;

    for (;;) {
        irq = find_next_bit(q->queue, opp->max_irq, irq + 1);
        if (irq == opp->max_irq) {
            break;
        }

        DPRINTF("IRQ_check: irq %d set ivpr_pr=%d pr=%d\n",
                irq, IVPR_PRIORITY(opp->src[irq].ivpr), priority);

        if (IVPR_PRIORITY(opp->src[irq].ivpr) > priority) {
            next = irq;
            priority = IVPR_PRIORITY(opp->src[irq].ivpr);
        }
    }

    q->next = next;
    q->priority = priority;
}
