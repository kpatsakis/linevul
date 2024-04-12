void Gfx::opSetFillCMYKColor(Object args[], int numArgs) {
  GfxColor color;
  int i;

  if (textHaveCSPattern && drawText) {
    GBool needFill = out->deviceHasTextClip(state);
    out->endTextObject(state);
    if (needFill) {
      doPatternFill(gTrue);
    }
    out->restoreState(state);
  }
  state->setFillPattern(NULL);
  state->setFillColorSpace(new GfxDeviceCMYKColorSpace());
  out->updateFillColorSpace(state);
  for (i = 0; i < 4; ++i) {
    color.c[i] = dblToCol(args[i].getNum());
  }
  state->setFillColor(&color);
  out->updateFillColor(state);
  if (textHaveCSPattern) {
    out->beginTextObject(state);
    out->updateRender(state);
    out->updateTextMat(state);
    out->updateTextPos(state);
    textHaveCSPattern = gFalse;
  }
}
