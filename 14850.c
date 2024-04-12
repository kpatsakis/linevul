bool InputDispatcher::checkInjectionPermission(const sp<InputWindowHandle>& windowHandle,
 const InjectionState* injectionState) {
 if (injectionState
 && (windowHandle == NULL
 || windowHandle->getInfo()->ownerUid != injectionState->injectorUid)
 && !hasInjectionPermission(injectionState->injectorPid, injectionState->injectorUid)) {
 if (windowHandle != NULL) {
            ALOGW("Permission denied: injecting event from pid %d uid %d to window %s "
 "owned by uid %d",
                    injectionState->injectorPid, injectionState->injectorUid,
                    windowHandle->getName().string(),
                    windowHandle->getInfo()->ownerUid);
 } else {
            ALOGW("Permission denied: injecting event from pid %d uid %d",
                    injectionState->injectorPid, injectionState->injectorUid);
 }
 return false;
 }
 return true;
}
