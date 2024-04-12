void NormalPageArena::updateRemainingAllocationSize() {
  if (m_lastRemainingAllocationSize > remainingAllocationSize()) {
    getThreadState()->increaseAllocatedObjectSize(
        m_lastRemainingAllocationSize - remainingAllocationSize());
    m_lastRemainingAllocationSize = remainingAllocationSize();
  }
  ASSERT(m_lastRemainingAllocationSize == remainingAllocationSize());
}
