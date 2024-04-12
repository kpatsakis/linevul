void GLES2Implementation::BindFragDataLocationEXT(GLuint program,
                                                  GLuint colorName,
                                                  const char* name) {
  GPU_CLIENT_SINGLE_THREAD_CHECK();
  GPU_CLIENT_LOG("[" << GetLogPrefix() << "] glBindFragDataLocationEXT("
                     << program << ", " << colorName << ", " << name << ")");
  SetBucketAsString(kResultBucketId, name);
  helper_->BindFragDataLocationEXTBucket(program, colorName, kResultBucketId);
  helper_->SetBucketSize(kResultBucketId, 0);
  CheckGLError();
}
