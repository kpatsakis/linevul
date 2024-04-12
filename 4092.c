  WebInputElement GetInputElementById(const WebString& id) {
    return GetMainFrame()
        ->GetDocument()
        .GetElementById(id)
        .To<WebInputElement>();
  }
