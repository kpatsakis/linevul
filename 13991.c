int set_iface_flags(const char *ifname, int dev_up) {
 struct ifreq ifr;
 int ret;
 int sock = socket(PF_INET, SOCK_DGRAM, 0);
 if (sock < 0) {
        ALOGD("Bad socket: %d\n", sock);
 return -errno;
 }


    memset(&ifr, 0, sizeof(ifr));
    strlcpy(ifr.ifr_name, ifname, IFNAMSIZ);


 if (ioctl(sock, SIOCGIFFLAGS, &ifr) != 0) {
      ret = errno ? -errno : -999;
      ALOGE("Could not read interface %s flags: %d\n", ifname, errno);
      close(sock);
 return ret;
 } else {
 }

 if (dev_up) {
 if (ifr.ifr_flags & IFF_UP) {
        close(sock);
 return 0;
 }
      ifr.ifr_flags |= IFF_UP;
 } else {
 if (!(ifr.ifr_flags & IFF_UP)) {
        close(sock);
 return 0;
 }
      ifr.ifr_flags &= ~IFF_UP;
 }

 if (ioctl(sock, SIOCSIFFLAGS, &ifr) != 0) {
      ALOGE("Could not set interface %s flags: %d\n", ifname, errno);
      ret = errno ? -errno : -999;
      close(sock);
 return ret;
 } else {
      ALOGD("set interface %s flags (%s)\n", ifname, dev_up ? "UP" : "DOWN");
 }
    close(sock);
 return 0;
}
