MediaPlayer::MediaPlayer()
{
    ALOGV("constructor");
    mListener = NULL;
    mCookie = NULL;
    mStreamType = AUDIO_STREAM_MUSIC;
    mAudioAttributesParcel = NULL;
    mCurrentPosition = -1;
    mSeekPosition = -1;
    mCurrentState = MEDIA_PLAYER_IDLE;
    mPrepareSync = false;
    mPrepareStatus = NO_ERROR;
    mLoop = false;
    mLeftVolume = mRightVolume = 1.0;
    mVideoWidth = mVideoHeight = 0;
    mLockThreadId = 0;
    mAudioSessionId = AudioSystem::newAudioUniqueId();
 AudioSystem::acquireAudioSessionId(mAudioSessionId, -1);
    mSendLevel = 0;
    mRetransmitEndpointValid = false;
}
