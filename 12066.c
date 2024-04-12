void LocalFrame::PrintNavigationErrorMessage(const Frame& target_frame,
                                             const char* reason) {
  String target_frame_description =
      target_frame.IsLocalFrame()
          ? "with URL '" +
                ToLocalFrame(target_frame).GetDocument()->Url().GetString() +
                "'"
          : "with origin '" +
                target_frame.GetSecurityContext()
                    ->GetSecurityOrigin()
                    ->ToString() +
                "'";
  String message =
      "Unsafe JavaScript attempt to initiate navigation for frame " +
      target_frame_description + " from frame with URL '" +
      GetDocument()->Url().GetString() + "'. " + reason + "\n";

  DomWindow()->PrintErrorMessage(message);
}
