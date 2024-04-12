void ShelfWidget::DelegateView::ReorderChildLayers(ui::Layer* parent_layer) {
  views::View::ReorderChildLayers(parent_layer);
  parent_layer->StackAtBottom(&opaque_background_);
}
