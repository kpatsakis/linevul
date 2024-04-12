void DOMFileSystemSync::reportError(PassOwnPtr<ErrorCallback> errorCallback, PassRefPtrWillBeRawPtr<FileError> fileError)
{
    errorCallback->handleEvent(fileError.get());
}
