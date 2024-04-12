bool GLES2Implementation::GetActiveUniformBlockNameHelper(GLuint program,
                                                          GLuint index,
                                                          GLsizei bufsize,
                                                          GLsizei* length,
                                                          char* name) {
  DCHECK_LE(0, bufsize);
  helper_->SetBucketSize(kResultBucketId, 0);
  typedef cmds::GetActiveUniformBlockName::Result Result;
  auto result = GetResultAs<Result>();
  if (!result) {
    return false;
  }
  *result = 0;
  helper_->GetActiveUniformBlockName(program, index, kResultBucketId,
                                     GetResultShmId(), result.offset());
  WaitForCmd();
  bool success = !!result;
  if (success) {
    GetResultNameHelper(bufsize, length, name);
  }
  return success;
}
