  static SandboxedHandler* Get() {
    static SandboxedHandler* instance = new SandboxedHandler();
    return instance;
  }
