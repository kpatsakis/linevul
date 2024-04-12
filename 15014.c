ExponentialFunction::ExponentialFunction(const ExponentialFunction *func) : Function(func) {
  memcpy(c0, func->c0, funcMaxOutputs * sizeof(double));
  memcpy(c1, func->c1, funcMaxOutputs * sizeof(double));

  e = func->e;
  isLinear = func->isLinear;
  ok = func->ok;
}
