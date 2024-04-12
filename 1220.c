static inline int connect_server_socket(const char* name)
{
 int s = socket(AF_LOCAL, SOCK_STREAM, 0);
 if(s < 0)
 return -1;
    set_socket_blocking(s, TRUE);
 if(socket_local_client_connect(s, name, ANDROID_SOCKET_NAMESPACE_ABSTRACT, SOCK_STREAM) >= 0)
 {
        APPL_TRACE_DEBUG("connected to local socket:%s, fd:%d", name, s);
 return s;
 }
 else APPL_TRACE_ERROR("connect to local socket:%s, fd:%d failed, errno:%d", name, s, errno);
    close(s);
 return -1;
}
