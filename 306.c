void ParamTraits<ListValue>::Log(const param_type& p, std::string* l) {
  std::string json;
  base::JSONWriter::Write(&p, &json);
  l->append(json);
}
