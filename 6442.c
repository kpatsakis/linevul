void acquire_object(const sp<ProcessState>& proc,
 const flat_binder_object& obj, const void* who, size_t* outAshmemSize)
{
 switch (obj.type) {
 case BINDER_TYPE_BINDER:
 if (obj.binder) {
                LOG_REFS("Parcel %p acquiring reference on local %p", who, obj.cookie);
 reinterpret_cast<IBinder*>(obj.cookie)->incStrong(who);
 }
 return;
 case BINDER_TYPE_WEAK_BINDER:
 if (obj.binder)
 reinterpret_cast<RefBase::weakref_type*>(obj.binder)->incWeak(who);
 return;
 case BINDER_TYPE_HANDLE: {
 const sp<IBinder> b = proc->getStrongProxyForHandle(obj.handle);
 if (b != NULL) {
                LOG_REFS("Parcel %p acquiring reference on remote %p", who, b.get());
                b->incStrong(who);
 }
 return;
 }
 case BINDER_TYPE_WEAK_HANDLE: {
 const wp<IBinder> b = proc->getWeakProxyForHandle(obj.handle);
 if (b != NULL) b.get_refs()->incWeak(who);
 return;
 }
 case BINDER_TYPE_FD: {
 if ((obj.cookie != 0) && (outAshmemSize != NULL)) {
 struct stat st;
 int ret = fstat(obj.handle, &st);
 if (!ret && S_ISCHR(st.st_mode) && (st.st_rdev == ashmem_rdev())) {
 int size = ashmem_get_size_region(obj.handle);
 if (size > 0) {
 *outAshmemSize += size;
 }
 }
 }
 return;
 }
 }

    ALOGD("Invalid object type 0x%08x", obj.type);
}
