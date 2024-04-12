bool LargeObjectPage::contains(Address object) {
  return roundToBlinkPageStart(getAddress()) <= object &&
         object < roundToBlinkPageEnd(getAddress() + size());
}
