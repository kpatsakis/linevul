void InputDispatcher::MotionEntry::appendDescription(String8& msg) const {
    msg.appendFormat("MotionEvent(deviceId=%d, source=0x%08x, action=%d, actionButton=0x%08x, "
 "flags=0x%08x, metaState=0x%08x, buttonState=0x%08x, "
 "edgeFlags=0x%08x, xPrecision=%.1f, yPrecision=%.1f, displayId=%d, pointers=[",
            deviceId, source, action, actionButton, flags, metaState, buttonState, edgeFlags,
            xPrecision, yPrecision, displayId);
 for (uint32_t i = 0; i < pointerCount; i++) {
 if (i) {
            msg.append(", ");
 }
        msg.appendFormat("%d: (%.1f, %.1f)", pointerProperties[i].id,
                pointerCoords[i].getX(), pointerCoords[i].getY());
 }
    msg.appendFormat("]), policyFlags=0x%08x", policyFlags);
}
