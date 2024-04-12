void Parcel::closeFileDescriptors()
{
 size_t i = mObjectsSize;
 if (i > 0) {
 }
 while (i > 0) {
        i--;
 const flat_binder_object* flat
 = reinterpret_cast<flat_binder_object*>(mData+mObjects[i]);
 if (flat->type == BINDER_TYPE_FD) {
            close(flat->handle);
 }
 }
}
