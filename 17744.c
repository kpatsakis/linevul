void OnSuggestionModelRemoved(UiScene* scene, SuggestionBinding* binding) {
  scene->RemoveUiElement(binding->view()->id());
}
