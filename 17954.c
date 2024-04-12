static struct addrinfo *lookuphost(const char *hostname, in_port_t port)
{
    struct addrinfo *ai = 0;
    struct addrinfo hints = { .ai_family = AF_UNSPEC,
                              .ai_protocol = IPPROTO_TCP,
                              .ai_socktype = SOCK_STREAM };
    char service[NI_MAXSERV];
    int error;

    (void)snprintf(service, NI_MAXSERV, "%d", port);
    if ((error = getaddrinfo(hostname, service, &hints, &ai)) != 0) {
       if (error != EAI_SYSTEM) {
          fprintf(stderr, "getaddrinfo(): %s\n", gai_strerror(error));
       } else {
          perror("getaddrinfo()");
       }
    }

    return ai;
}
