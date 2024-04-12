void DetachSharedMemory(Display* display, XSharedMemoryId shmseg) {
  DCHECK(QuerySharedMemorySupport(display));

  XShmSegmentInfo shminfo;
  memset(&shminfo, 0, sizeof(shminfo));
  shminfo.shmseg = shmseg;

  if (!XShmDetach(display, &shminfo))
    NOTREACHED();
}
