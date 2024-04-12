  virtual void TabMoved(
      TabContentsWrapper* contents, int from_index, int to_index) {
    State* s = new State(contents, to_index, MOVE);
    s->src_index = from_index;
    states_.push_back(s);
  }
