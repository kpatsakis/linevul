BrowserGpuChannelHostFactory::AllocateSharedMemory(uint32 size) {
  scoped_ptr<base::SharedMemory> shm(new base::SharedMemory());
  if (!shm->CreateAnonymous(size))
    return scoped_ptr<base::SharedMemory>();
  return shm.Pass();
}
