InputMethodLibrary* InputMethodLibrary::GetImpl(bool stub) {
  if (stub) {
    return new InputMethodLibraryStubImpl();
  } else {
    InputMethodLibraryImpl* impl = new InputMethodLibraryImpl();
    if (!impl->Init()) {
      LOG(ERROR) << "Failed to initialize InputMethodLibraryImpl";
    }
    return impl;
  }
}
