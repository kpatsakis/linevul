bool TabsGetZoomFunction::RunAsync() {
  std::unique_ptr<tabs::GetZoom::Params> params(
      tabs::GetZoom::Params::Create(*args_));
  EXTENSION_FUNCTION_VALIDATE(params);

  int tab_id = params->tab_id ? *params->tab_id : -1;
  WebContents* web_contents = GetWebContents(tab_id);
  if (!web_contents)
    return false;

  double zoom_level =
      ZoomController::FromWebContents(web_contents)->GetZoomLevel();
  double zoom_factor = content::ZoomLevelToZoomFactor(zoom_level);
  results_ = tabs::GetZoom::Results::Create(zoom_factor);
  SendResponse(true);
  return true;
}
