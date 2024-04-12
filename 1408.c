e1000e_can_receive(E1000ECore *core)
{
    int i;

    if (!e1000x_rx_ready(core->owner, core->mac)) {
        return false;
    }

    for (i = 0; i < E1000E_NUM_QUEUES; i++) {
        E1000E_RxRing rxr;

        e1000e_rx_ring_init(core, &rxr, i);
        if (e1000e_ring_enabled(core, rxr.i) &&
            e1000e_has_rxbufs(core, rxr.i, 1)) {
            trace_e1000e_rx_can_recv();
            return true;
        }
    }

    trace_e1000e_rx_can_recv_rings_full();
    return false;
}
