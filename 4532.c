void IPCThreadState::restoreCallingIdentity(int64_t token)
{
    mCallingUid = (int)(token>>32);
    mCallingPid = (int)token;
}
