 void MediaStreamDispatcherHost::GenerateStream(
    int32_t page_request_id,
    const StreamControls& controls,
    bool user_gesture,
    GenerateStreamCallback callback) {
  DCHECK_CURRENTLY_ON(BrowserThread::IO);

  base::PostTaskAndReplyWithResult(
      base::CreateSingleThreadTaskRunnerWithTraits({BrowserThread::UI}).get(),
      FROM_HERE,
      base::BindOnce(salt_and_origin_callback_, render_process_id_,
                     render_frame_id_),
      base::BindOnce(&MediaStreamDispatcherHost::DoGenerateStream,
                     weak_factory_.GetWeakPtr(), page_request_id, controls,
                     user_gesture, std::move(callback)));
}
