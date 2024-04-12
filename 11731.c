 explicit FastSloppyArgumentsElementsAccessor(const char* name)
 : SloppyArgumentsElementsAccessor<
 FastSloppyArgumentsElementsAccessor,
 FastHoleyObjectElementsAccessor,
 ElementsKindTraits<FAST_SLOPPY_ARGUMENTS_ELEMENTS> >(name) {}
