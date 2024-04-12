void ParamTraits<unsigned short>::Write(Message* m, const param_type& p) {
  m->WriteBytes(&p, sizeof(param_type));
}
