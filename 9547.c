void NormalPage::removeFromHeap() {
  arenaForNormalPage()->freePage(this);
}
