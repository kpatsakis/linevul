void Gfx::opMoveShowText(Object args[], int numArgs) {
  double tx, ty;

  if (!state->getFont()) {
    error(getPos(), "No font in move/show");
    return;
  }
  if (fontChanged) {
    out->updateFont(state);
    fontChanged = gFalse;
  }
  tx = state->getLineX();
  ty = state->getLineY() - state->getLeading();
  state->textMoveTo(tx, ty);
  out->updateTextPos(state);
  out->beginStringOp(state);
  doShowText(args[0].getString());
  out->endStringOp(state);
}
