void LargeObjectPage::RemoveFromHeap() {
  static_cast<LargeObjectArena*>(Arena())->FreeLargeObjectPage(this);
}
