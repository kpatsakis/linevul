bool ParamTraits<gfx::Transform>::Read(const base::Pickle* m,
                                       base::PickleIterator* iter,
                                       param_type* r) {
  const char* column_major_data;
  if (!iter->ReadBytes(&column_major_data, sizeof(SkMScalar) * 16))
    return false;
  r->matrix().setColMajor(
      reinterpret_cast<const SkMScalar*>(column_major_data));
  return true;
}
