static bool underQTMetaPath(const Vector<uint32_t> &path, int32_t depth) {
 return path.size() >= 2
 && path[0] == FOURCC('m', 'o', 'o', 'v')
 && path[1] == FOURCC('m', 'e', 't', 'a')
 && (depth == 2
 || (depth == 3
 && (path[2] == FOURCC('h', 'd', 'l', 'r')
 ||  path[2] == FOURCC('i', 'l', 's', 't')
 ||  path[2] == FOURCC('k', 'e', 'y', 's'))));
}
