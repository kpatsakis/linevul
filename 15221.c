  void CreateTabCaptureUIRequest(int target_render_process_id,
                                 int target_render_frame_id) {
    DCHECK(!ui_request_);
    target_process_id_ = target_render_process_id;
    target_frame_id_ = target_render_frame_id;
    ui_request_.reset(new MediaStreamRequest(
        target_render_process_id, target_render_frame_id, page_request_id,
        security_origin.GetURL(), user_gesture, request_type, "", "",
        audio_type_, video_type_, controls.disable_local_echo));
  }
