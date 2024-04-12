  PropertyAccessor<int>* GetIDAccessor() {
    static PropertyAccessor<int> accessor;
    return &accessor;
  }
