void InputDispatcher::KeyEntry::appendDescription(String8& msg) const {
    msg.appendFormat("KeyEvent(deviceId=%d, source=0x%08x, action=%d, "
 "flags=0x%08x, keyCode=%d, scanCode=%d, metaState=0x%08x, "
 "repeatCount=%d), policyFlags=0x%08x",
            deviceId, source, action, flags, keyCode, scanCode, metaState,
            repeatCount, policyFlags);
}
