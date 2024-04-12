void Gfx::opShFill(Object args[], int numArgs) {
  GfxShading *shading;
  GfxPath *savedPath;
  double xMin, yMin, xMax, yMax;

  if (!(shading = res->lookupShading(args[0].getName(), this))) {
    return;
  }

  savedPath = state->getPath()->copy();
  saveState();

  if (shading->getHasBBox()) {
    shading->getBBox(&xMin, &yMin, &xMax, &yMax);
    state->moveTo(xMin, yMin);
    state->lineTo(xMax, yMin);
    state->lineTo(xMax, yMax);
    state->lineTo(xMin, yMax);
    state->closePath();
    state->clip();
    out->clip(state);
    state->clearPath();
  }

  state->setFillColorSpace(shading->getColorSpace()->copy());
  out->updateFillColorSpace(state);

#if 1 //~tmp: turn off anti-aliasing temporarily
  GBool vaa = out->getVectorAntialias();
  if (vaa) {
    out->setVectorAntialias(gFalse);
  }
#endif

  switch (shading->getType()) {
  case 1:
    doFunctionShFill((GfxFunctionShading *)shading);
    break;
  case 2:
    doAxialShFill((GfxAxialShading *)shading);
    break;
  case 3:
    doRadialShFill((GfxRadialShading *)shading);
    break;
  case 4:
  case 5:
    doGouraudTriangleShFill((GfxGouraudTriangleShading *)shading);
    break;
  case 6:
  case 7:
    doPatchMeshShFill((GfxPatchMeshShading *)shading);
    break;
  }

#if 1 //~tmp: turn off anti-aliasing temporarily
  if (vaa) {
    out->setVectorAntialias(gTrue);
  }
#endif

  restoreState();
  state->setPath(savedPath);

  delete shading;
}
