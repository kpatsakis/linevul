String8 InputDispatcher::getApplicationWindowLabelLocked(
 const sp<InputApplicationHandle>& applicationHandle,
 const sp<InputWindowHandle>& windowHandle) {
 if (applicationHandle != NULL) {
 if (windowHandle != NULL) {
 String8 label(applicationHandle->getName());
            label.append(" - ");
            label.append(windowHandle->getName());
 return label;
 } else {
 return applicationHandle->getName();
 }
 } else if (windowHandle != NULL) {
 return windowHandle->getName();
 } else {
 return String8("<unknown application or window>");
 }
}
