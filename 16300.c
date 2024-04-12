DocumentElementSetMap& documentToElementSetMap() {
  DEFINE_STATIC_LOCAL(DocumentElementSetMap, map, (new DocumentElementSetMap));
  return map;
}
