  BackingVisitor(ThreadState* state, std::vector<void*>* objects)
      : Visitor(state), objects_(objects) {}
