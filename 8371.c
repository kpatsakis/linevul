bool Browser::RequestPpapiBrokerPermission(
    WebContents* web_contents,
    const GURL& url,
    const base::FilePath& plugin_path,
    const base::Callback<void(bool)>& callback) {
  PepperBrokerInfoBarDelegate::Create(web_contents, url, plugin_path, callback);
  return true;
}
