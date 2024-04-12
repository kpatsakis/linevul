void Gfx::opSetLineWidth(Object args[], int numArgs) {
  state->setLineWidth(args[0].getNum());
  out->updateLineWidth(state);
}
