ChromeClient* InputType::GetChromeClient() const {
  if (Page* page = GetElement().GetDocument().GetPage())
    return &page->GetChromeClient();
  return nullptr;
}
