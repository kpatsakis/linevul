void AsyncFileSystemChromium::createDirectory(const KURL& path, bool exclusive, PassOwnPtr<AsyncFileSystemCallbacks> callbacks)
{
    m_webFileSystem->createDirectory(path, exclusive, new WebKit::WebFileSystemCallbacksImpl(callbacks));
}
