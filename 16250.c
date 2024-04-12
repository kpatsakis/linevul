bool GLES2DecoderPassthroughImpl::MakeCurrent() {
  if (!context_.get())
    return false;

  if (WasContextLost()) {
    LOG(ERROR) << "  GLES2DecoderPassthroughImpl: Trying to make lost context "
                  "current.";
    return false;
  }

  if (!context_->MakeCurrent(surface_.get())) {
    LOG(ERROR)
        << "  GLES2DecoderPassthroughImpl: Context lost during MakeCurrent.";
    MarkContextLost(error::kMakeCurrentFailed);
    group_->LoseContexts(error::kUnknown);
    return false;
  }
  DCHECK_EQ(api(), gl::g_current_gl_context);

  if (CheckResetStatus()) {
    LOG(ERROR) << "  GLES2DecoderPassthroughImpl: Context reset detected after "
                  "MakeCurrent.";
    group_->LoseContexts(error::kUnknown);
    return false;
  }

  ProcessReadPixels(false);
  ProcessQueries(false);

  resources_->DestroyPendingTextures(/*has_context=*/true);

  return true;
}
