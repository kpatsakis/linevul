bool IsValidPVRTCSize(GLint level, GLsizei size) {
  return GLES2Util::IsPOT(size);
}
