double GetZoomLevel(const content::WebContents* web_contents) {
  return zoom::ZoomController::FromWebContents(web_contents)->GetZoomLevel();
}
