void MarkingVisitor::RegisterBackingStoreCallback(void* backing_store,
                                                  MovingObjectCallback callback,
                                                  void* callback_data) {
  if (marking_mode_ != kGlobalMarkingWithCompaction)
    return;
  Heap().RegisterMovingObjectCallback(
      reinterpret_cast<MovableReference>(backing_store), callback,
      callback_data);
}
