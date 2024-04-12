void InputDispatcher::addMonitoringTargetsLocked(Vector<InputTarget>& inputTargets) {
 for (size_t i = 0; i < mMonitoringChannels.size(); i++) {
        inputTargets.push();

 InputTarget& target = inputTargets.editTop();
        target.inputChannel = mMonitoringChannels[i];
        target.flags = InputTarget::FLAG_DISPATCH_AS_IS;
        target.xOffset = 0;
        target.yOffset = 0;
        target.pointerIds.clear();
        target.scaleFactor = 1.0f;
 }
}
