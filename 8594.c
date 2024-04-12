bool IsTabDiscarded(content::WebContents* web_contents) {
  return TabLifecycleUnitExternal::FromWebContents(web_contents)->IsDiscarded();
}
