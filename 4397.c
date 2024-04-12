void Insert() {
  Object* obj = Object::Create();
  Container container;
  {
    ExpectWriteBarrierFires scope(ThreadState::Current(), {obj});
    container.insert(obj);
  }
}
