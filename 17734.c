 bool UsbDeviceImpl::Close(scoped_refptr<UsbDeviceHandle> handle) {
   DCHECK(thread_checker_.CalledOnValidThread());
 
  for (HandlesVector::iterator it = handles_.begin(); it != handles_.end();
       ++it) {
    if (it->get() == handle.get()) {
      (*it)->InternalClose();
      handles_.erase(it);
      return true;
    }
  }
  return false;
}
