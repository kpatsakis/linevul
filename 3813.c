void ParamTraits<gfx::Vector2d>::Log(const gfx::Vector2d& v, std::string* l) {
  l->append(base::StringPrintf("(%d, %d)", v.x(), v.y()));
}
