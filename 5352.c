void WorkerGlobalScopeFileSystem::webkitRequestFileSystem(WorkerGlobalScope& worker, int type, long long size, PassOwnPtr<FileSystemCallback> successCallback, PassOwnPtr<ErrorCallback> errorCallback)
{
    ExecutionContext* secureContext = worker.executionContext();
    if (!secureContext->securityOrigin()->canAccessFileSystem()) {
        DOMFileSystem::scheduleCallback(&worker, errorCallback, FileError::create(FileError::SECURITY_ERR));
        return;
    }

    FileSystemType fileSystemType = static_cast<FileSystemType>(type);
    if (!DOMFileSystemBase::isValidType(fileSystemType)) {
        DOMFileSystem::scheduleCallback(&worker, errorCallback, FileError::create(FileError::INVALID_MODIFICATION_ERR));
        return;
    }

    LocalFileSystem::from(worker)->requestFileSystem(&worker, fileSystemType, size, FileSystemCallbacks::create(successCallback, errorCallback, &worker, fileSystemType));
}
