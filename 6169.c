status_t MediaPlayer::reset_l()
{
    mLoop = false;
 if (mCurrentState == MEDIA_PLAYER_IDLE) return NO_ERROR;
    mPrepareSync = false;
 if (mPlayer != 0) {
 status_t ret = mPlayer->reset();
 if (ret != NO_ERROR) {
            ALOGE("reset() failed with return code (%d)", ret);
            mCurrentState = MEDIA_PLAYER_STATE_ERROR;
 } else {
            mPlayer->disconnect();
            mCurrentState = MEDIA_PLAYER_IDLE;
 }
        mPlayer = 0;
 return ret;
 }
    clear_l();
 return NO_ERROR;
}
