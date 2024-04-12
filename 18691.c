void HTMLInputElement::SelectColorInColorChooser(const Color& color) {
  if (ColorChooserClient* client = input_type_->GetColorChooserClient())
    client->DidChooseColor(color);
}
