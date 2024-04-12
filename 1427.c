void ParamTraits<base::Time>::Write(Message* m, const param_type& p) {
  ParamTraits<int64>::Write(m, p.ToInternalValue());
}
