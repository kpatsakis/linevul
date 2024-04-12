  virtual void TearDown() {
    loop_.RunAllPending();
    service_.reset();
  }
