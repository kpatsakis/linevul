int VisualizerLib_Release(effect_handle_t handle) {
 VisualizerContext * pContext = (VisualizerContext *)handle;

    ALOGV("VisualizerLib_Release %p", handle);
 if (pContext == NULL) {
 return -EINVAL;
 }
    pContext->mState = VISUALIZER_STATE_UNINITIALIZED;
 delete pContext;

 return 0;
}
