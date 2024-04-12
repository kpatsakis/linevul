static bool underMetaDataPath(const Vector<uint32_t> &path) {
 return path.size() >= 5
 && path[0] == FOURCC('m', 'o', 'o', 'v')
 && path[1] == FOURCC('u', 'd', 't', 'a')
 && path[2] == FOURCC('m', 'e', 't', 'a')
 && path[3] == FOURCC('i', 'l', 's', 't');
}
