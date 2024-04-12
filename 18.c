Closure MessageLoop::QuitWhenIdleClosure() {
  return Bind(&RunLoop::QuitCurrentWhenIdleDeprecated);
}
