bool MediaRecorder::isTypeSupported(ExecutionContext* context,
                                    const String& type) {
  std::unique_ptr<WebMediaRecorderHandler> handler =
      Platform::Current()->CreateMediaRecorderHandler(
          context->GetTaskRunner(TaskType::kInternalMediaRealTime));
  if (!handler)
    return false;

  ContentType content_type(type);
  return handler->CanSupportMimeType(content_type.GetType(),
                                     content_type.Parameter("codecs"));
}
