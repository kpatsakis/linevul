IdentityFunction::IdentityFunction() {
  int i;

  m = funcMaxInputs;
  n = funcMaxOutputs;
  for (i = 0; i < funcMaxInputs; ++i) {
    domain[i][0] = 0;
    domain[i][1] = 1;
  }
  hasRange = gFalse;
}
