SoftAMRWBEncoder::~SoftAMRWBEncoder() {
 if (mEncoderHandle != NULL) {
        CHECK_EQ(VO_ERR_NONE, mApiHandle->Uninit(mEncoderHandle));
        mEncoderHandle = NULL;
 }

 delete mApiHandle;
    mApiHandle = NULL;

 delete mMemOperator;
    mMemOperator = NULL;
}
