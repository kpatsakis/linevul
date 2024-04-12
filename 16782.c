void Gfx::opSetCharWidth(Object args[], int numArgs) {
  out->type3D0(state, args[0].getNum(), args[1].getNum());
}
