MediaRecorder* MediaRecorder::Create(ExecutionContext* context,
                                     MediaStream* stream,
                                     ExceptionState& exception_state) {
  MediaRecorder* recorder = new MediaRecorder(
      context, stream, MediaRecorderOptions::Create(), exception_state);
  recorder->PauseIfNeeded();

  return recorder;
}
