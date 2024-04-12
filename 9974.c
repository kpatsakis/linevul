const CustomButton* CustomButton::AsCustomButton(const views::View* view) {
  return AsCustomButton(const_cast<views::View*>(view));
}
