bool ParamTraits<base::FileDescriptor>::Read(const Message* m,
                                             PickleIterator* iter,
                                             param_type* r) {
  bool valid;
  if (!ReadParam(m, iter, &valid))
    return false;

  if (!valid) {
    r->fd = -1;
    r->auto_close = false;
    return true;
  }

  return m->ReadFileDescriptor(iter, r);
}
