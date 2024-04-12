WebContents* GetEmbedderForGuest(content::WebContents* guest) {
  CHECK(guest);
  return static_cast<content::WebContentsImpl*>(guest)->GetOuterWebContents();
}
