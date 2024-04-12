void SimpleSoftOMXComponent::checkTransitions() {
 if (mState != mTargetState) {
 bool transitionComplete = true;

 if (mState == OMX_StateLoaded) {
            CHECK_EQ((int)mTargetState, (int)OMX_StateIdle);

 for (size_t i = 0; i < mPorts.size(); ++i) {
 const PortInfo &port = mPorts.itemAt(i);
 if (port.mDef.bEnabled == OMX_FALSE) {
 continue;
 }

 if (port.mDef.bPopulated == OMX_FALSE) {
                    transitionComplete = false;
 break;
 }
 }
 } else if (mTargetState == OMX_StateLoaded) {
            CHECK_EQ((int)mState, (int)OMX_StateIdle);

 for (size_t i = 0; i < mPorts.size(); ++i) {
 const PortInfo &port = mPorts.itemAt(i);
 if (port.mDef.bEnabled == OMX_FALSE) {
 continue;
 }

 size_t n = port.mBuffers.size();

 if (n > 0) {
                    CHECK_LE(n, port.mDef.nBufferCountActual);

 if (n == port.mDef.nBufferCountActual) {
                        CHECK_EQ((int)port.mDef.bPopulated, (int)OMX_TRUE);
 } else {
                        CHECK_EQ((int)port.mDef.bPopulated, (int)OMX_FALSE);
 }

                    transitionComplete = false;
 break;
 }
 }
 }

 if (transitionComplete) {
            ALOGV("state transition from %d to %d complete", mState, mTargetState);
            mState = mTargetState;

 if (mState == OMX_StateLoaded) {
                onReset();
 }

            notify(OMX_EventCmdComplete, OMX_CommandStateSet, mState, NULL);
 } else {
            ALOGV("state transition from %d to %d not yet complete", mState, mTargetState);
 }
 }

 for (size_t i = 0; i < mPorts.size(); ++i) {
 PortInfo *port = &mPorts.editItemAt(i);

 if (port->mTransition == PortInfo::DISABLING) {
 if (port->mBuffers.empty()) {
                ALOGV("Port %zu now disabled.", i);

                port->mTransition = PortInfo::NONE;
                notify(OMX_EventCmdComplete, OMX_CommandPortDisable, i, NULL);

                onPortEnableCompleted(i, false /* enabled */);
 }
 } else if (port->mTransition == PortInfo::ENABLING) {
 if (port->mDef.bPopulated == OMX_TRUE) {
                ALOGV("Port %zu now enabled.", i);

                port->mTransition = PortInfo::NONE;
                port->mDef.bEnabled = OMX_TRUE;
                notify(OMX_EventCmdComplete, OMX_CommandPortEnable, i, NULL);

                onPortEnableCompleted(i, true /* enabled */);
 }
 }
 }
}
