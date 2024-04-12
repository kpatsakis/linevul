bool ParamTraits<gfx::Size>::Read(const Message* m,
                                  PickleIterator* iter,
                                  gfx::Size* r) {
  int w, h;
  if (!m->ReadInt(iter, &w) ||
      !m->ReadInt(iter, &h))
    return false;
  r->set_width(w);
  r->set_height(h);
  return true;
}
