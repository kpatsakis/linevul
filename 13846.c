void Gfx::opSetDash(Object args[], int numArgs) {
  Array *a;
  int length;
  Object obj;
  double *dash;
  int i;

  a = args[0].getArray();
  length = a->getLength();
  if (length == 0) {
    dash = NULL;
  } else {
    dash = (double *)gmallocn(length, sizeof(double));
    for (i = 0; i < length; ++i) {
      dash[i] = a->get(i, &obj)->getNum();
      obj.free();
    }
  }
  state->setLineDash(dash, length, args[1].getNum());
  out->updateLineDash(state);
}
