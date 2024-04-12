void BrowserTabStripController::SetTabDataAt(content::WebContents* web_contents,
                                             int model_index) {
  TabRendererData data;
  SetTabRendererDataFromModel(web_contents, model_index, &data, EXISTING_TAB);
  tabstrip_->SetTabData(model_index, data);
}
