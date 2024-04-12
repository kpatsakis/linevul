  explicit RenderViewCreatedObserver(WebContents* web_contents)
      : WebContentsObserver(web_contents),
        render_view_created_called_(false),
        main_frame_created_called_(false) {}
