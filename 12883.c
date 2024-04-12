XRRScreenSize *XRRSizes(Display *dpy, int screen, int *nsizes)
{
  XRRScreenConfiguration *config;
  XExtDisplayInfo *info = XRRFindDisplay(dpy);
  XRRScreenSize *sizes;

  LockDisplay(dpy);
  if ((config = _XRRValidateCache(dpy, info, screen))) {
    *nsizes = config->nsizes;
    sizes = config->sizes;
    UnlockDisplay(dpy);
    return sizes;
    }
  else {
    UnlockDisplay(dpy);
    *nsizes = 0;
    return NULL;
  }
}
