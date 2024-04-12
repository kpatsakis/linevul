void GLES2Implementation::DestroyGpuFenceCHROMIUMHelper(GLuint client_id) {
  if (GetIdAllocator(IdNamespaces::kGpuFences)->InUse(client_id)) {
    GetIdAllocator(IdNamespaces::kGpuFences)->FreeID(client_id);
    helper_->DestroyGpuFenceCHROMIUM(client_id);
  } else {
    SetGLError(GL_INVALID_VALUE, "glDestroyGpuFenceCHROMIUM",
               "id not created by this context.");
  }
}
