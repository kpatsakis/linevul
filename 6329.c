  explicit MockScreenshotManager(content::NavigationControllerImpl* owner)
      : content::NavigationEntryScreenshotManager(owner),
        encoding_screenshot_in_progress_(false) {
  }
