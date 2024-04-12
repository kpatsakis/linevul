status_t SoftAVC::resetPlugin() {
    mIsInFlush = false;
    mReceivedEOS = false;
    memset(mTimeStamps, 0, sizeof(mTimeStamps));
    memset(mTimeStampsValid, 0, sizeof(mTimeStampsValid));

 /* Initialize both start and end times */
    gettimeofday(&mTimeStart, NULL);
    gettimeofday(&mTimeEnd, NULL);

 return OK;
}
