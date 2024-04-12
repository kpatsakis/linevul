GLuint GLES2Implementation::GetProgramResourceIndexHelper(
    GLuint program,
    GLenum program_interface,
    const char* name) {
  typedef cmds::GetProgramResourceIndex::Result Result;
  SetBucketAsCString(kResultBucketId, name);
  auto result = GetResultAs<Result>();
  if (!result) {
    return GL_INVALID_INDEX;
  }
  *result = GL_INVALID_INDEX;
  helper_->GetProgramResourceIndex(program, program_interface, kResultBucketId,
                                   GetResultShmId(), result.offset());
  WaitForCmd();
  helper_->SetBucketSize(kResultBucketId, 0);
  return *result;
}
