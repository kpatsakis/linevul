aptcTimerHandler(unsigned long arg)
{
    u32 numbytes;
    u32 throughput;
    struct ar6_softc *ar;
    int status;

    ar = (struct ar6_softc *)arg;
    A_ASSERT(ar != NULL);
    A_ASSERT(!timer_pending(&aptcTimer));

    AR6000_SPIN_LOCK(&ar->arLock, 0);

    /* Get the number of bytes transferred */
    numbytes = aptcTR.bytesTransmitted + aptcTR.bytesReceived;
    aptcTR.bytesTransmitted = aptcTR.bytesReceived = 0;

    /* Calculate and decide based on throughput thresholds */
    throughput = ((numbytes * 8)/APTC_TRAFFIC_SAMPLING_INTERVAL); /* Kbps */
    if (throughput < APTC_LOWER_THROUGHPUT_THRESHOLD) {
        /* Enable Sleep and delete the timer */
        A_ASSERT(ar->arWmiReady == true);
        AR6000_SPIN_UNLOCK(&ar->arLock, 0);
        status = wmi_powermode_cmd(ar->arWmi, REC_POWER);
        AR6000_SPIN_LOCK(&ar->arLock, 0);
        A_ASSERT(status == 0);
        aptcTR.timerScheduled = false;
    } else {
        A_TIMEOUT_MS(&aptcTimer, APTC_TRAFFIC_SAMPLING_INTERVAL, 0);
    }

    AR6000_SPIN_UNLOCK(&ar->arLock, 0);
}
