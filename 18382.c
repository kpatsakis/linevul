  bool AreAllFramesInTab() {
    std::set<content::RenderFrameHost*> current_frames;
    web_contents()->ForEachFrame(
        base::BindRepeating(&AddFrameToSet, base::Unretained(&current_frames)));
    for (content::RenderFrameHost* frame : frames_) {
      if (!base::ContainsKey(current_frames, frame))
        return false;
    }
    return true;
  }
