bool GLES2Implementation::GetActiveUniformsivHelper(GLuint program,
                                                    GLsizei count,
                                                    const GLuint* indices,
                                                    GLenum pname,
                                                    GLint* params) {
  base::CheckedNumeric<uint32_t> bytes = count;
  bytes *= sizeof(GLuint);
  if (!bytes.IsValid()) {
    SetGLError(GL_INVALID_VALUE, "glGetActiveUniformsiv", "count overflow");
    return false;
  }
  SetBucketContents(kResultBucketId, indices, bytes.ValueOrDefault(0));
  typedef cmds::GetActiveUniformsiv::Result Result;
  auto result = GetResultAs<Result>();
  if (!result) {
    return false;
  }
  result->SetNumResults(0);
  helper_->GetActiveUniformsiv(program, kResultBucketId, pname,
                               GetResultShmId(), result.offset());
  WaitForCmd();
  bool success = result->GetNumResults() == count;
  if (success) {
    if (params) {
      result->CopyResult(params);
    }
    GPU_CLIENT_LOG_CODE_BLOCK({
      for (int32_t i = 0; i < result->GetNumResults(); ++i) {
        GPU_CLIENT_LOG("  " << i << ": " << result->GetData()[i]);
      }
    });
  }
  helper_->SetBucketSize(kResultBucketId, 0);
  return success;
}
