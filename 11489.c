static inline int create_server_socket(const char* name)
{
 int s = socket(AF_LOCAL, SOCK_STREAM, 0);
 if(s < 0)
 return -1;
    APPL_TRACE_DEBUG("covert name to android abstract name:%s", name);
 if(socket_local_server_bind(s, name, ANDROID_SOCKET_NAMESPACE_ABSTRACT) >= 0)
 {
 if(listen(s, 5) == 0)
 {
            APPL_TRACE_DEBUG("listen to local socket:%s, fd:%d", name, s);
 return s;
 }
 else APPL_TRACE_ERROR("listen to local socket:%s, fd:%d failed, errno:%d", name, s, errno);
 }
 else APPL_TRACE_ERROR("create local socket:%s fd:%d, failed, errno:%d", name, s, errno);
    close(s);
 return -1;
}
