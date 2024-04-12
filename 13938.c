void InputDispatcher::addWindowTargetLocked(const sp<InputWindowHandle>& windowHandle,
 int32_t targetFlags, BitSet32 pointerIds, Vector<InputTarget>& inputTargets) {
    inputTargets.push();

 const InputWindowInfo* windowInfo = windowHandle->getInfo();
 InputTarget& target = inputTargets.editTop();
    target.inputChannel = windowInfo->inputChannel;
    target.flags = targetFlags;
    target.xOffset = - windowInfo->frameLeft;
    target.yOffset = - windowInfo->frameTop;
    target.scaleFactor = windowInfo->scaleFactor;
    target.pointerIds = pointerIds;
}
