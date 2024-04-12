  static void Destroy(const internal::BindStateBase* self) {
    delete static_cast<const FakeBindState*>(self);
  }
