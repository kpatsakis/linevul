DOMMessageQueue::DOMMessageQueue(WebContents* web_contents)
    : WebContentsObserver(web_contents) {
  registrar_.Add(this, NOTIFICATION_DOM_OPERATION_RESPONSE,
                 Source<WebContents>(web_contents));
}
