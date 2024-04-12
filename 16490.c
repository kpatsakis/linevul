content::WebContentsViewDelegate* AwMainDelegate::CreateViewDelegate(
    content::WebContents* web_contents) {
  return AwWebContentsViewDelegate::Create(web_contents);
}
