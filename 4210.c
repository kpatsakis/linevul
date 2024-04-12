status_t Camera3Device::RequestThread::prepareHalRequests() {
    ATRACE_CALL();

 for (auto& nextRequest : mNextRequests) {
        sp<CaptureRequest> captureRequest = nextRequest.captureRequest;
 camera3_capture_request_t* halRequest = &nextRequest.halRequest;
 Vector<camera3_stream_buffer_t>* outputBuffers = &nextRequest.outputBuffers;

        halRequest->frame_number = captureRequest->mResultExtras.frameNumber;

 status_t res = insertTriggers(captureRequest);

 if (res < 0) {
            SET_ERR("RequestThread: Unable to insert triggers "
 "(capture request %d, HAL device: %s (%d)",
                    halRequest->frame_number, strerror(-res), res);
 return INVALID_OPERATION;
 }
 int triggerCount = res;
 bool triggersMixedIn = (triggerCount > 0 || mPrevTriggers > 0);
        mPrevTriggers = triggerCount;

 if (mPrevRequest != captureRequest || triggersMixedIn) {
 /**
             * HAL workaround:
             * Insert a dummy trigger ID if a trigger is set but no trigger ID is
             */
            res = addDummyTriggerIds(captureRequest);
 if (res != OK) {
                SET_ERR("RequestThread: Unable to insert dummy trigger IDs "
 "(capture request %d, HAL device: %s (%d)",
                        halRequest->frame_number, strerror(-res), res);
 return INVALID_OPERATION;
 }

 /**
             * The request should be presorted so accesses in HAL
             *   are O(logn). Sidenote, sorting a sorted metadata is nop.
             */
            captureRequest->mSettings.sort();
            halRequest->settings = captureRequest->mSettings.getAndLock();
            mPrevRequest = captureRequest;
            ALOGVV("%s: Request settings are NEW", __FUNCTION__);

            IF_ALOGV() {
 camera_metadata_ro_entry_t e = camera_metadata_ro_entry_t();
                find_camera_metadata_ro_entry(
                        halRequest->settings,
                        ANDROID_CONTROL_AF_TRIGGER,
 &e
 );
 if (e.count > 0) {
                    ALOGV("%s: Request (frame num %d) had AF trigger 0x%x",
                          __FUNCTION__,
                          halRequest->frame_number,
                          e.data.u8[0]);
 }
 }
 } else {
            ALOGVV("%s: Request settings are REUSED",
                   __FUNCTION__);
 }

 uint32_t totalNumBuffers = 0;

 if (captureRequest->mInputStream != NULL) {
            halRequest->input_buffer = &captureRequest->mInputBuffer;
            totalNumBuffers += 1;
 } else {
            halRequest->input_buffer = NULL;
 }

        outputBuffers->insertAt(camera3_stream_buffer_t(), 0,
                captureRequest->mOutputStreams.size());
        halRequest->output_buffers = outputBuffers->array();
 for (size_t i = 0; i < captureRequest->mOutputStreams.size(); i++) {
            res = captureRequest->mOutputStreams.editItemAt(i)->
                    getBuffer(&outputBuffers->editItemAt(i));
 if (res != OK) {
                ALOGE("RequestThread: Can't get output buffer, skipping request:"
 " %s (%d)", strerror(-res), res);

 return TIMED_OUT;
 }
            halRequest->num_output_buffers++;
 }
        totalNumBuffers += halRequest->num_output_buffers;

        sp<Camera3Device> parent = mParent.promote();
 if (parent == NULL) {
            CLOGE("RequestThread: Parent is gone");
 return INVALID_OPERATION;
 }
        res = parent->registerInFlight(halRequest->frame_number,
                totalNumBuffers, captureRequest->mResultExtras,
 /*hasInput*/halRequest->input_buffer != NULL,
                captureRequest->mAeTriggerCancelOverride);
        ALOGVV("%s: registered in flight requestId = %" PRId32 ", frameNumber = %" PRId64
 ", burstId = %" PRId32 ".",
                __FUNCTION__,
                captureRequest->mResultExtras.requestId, captureRequest->mResultExtras.frameNumber,
                captureRequest->mResultExtras.burstId);
 if (res != OK) {
            SET_ERR("RequestThread: Unable to register new in-flight request:"
 " %s (%d)", strerror(-res), res);
 return INVALID_OPERATION;
 }
 }

 return OK;
}
