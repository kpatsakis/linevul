void Gfx::doForm1(Object *str, Dict *resDict, double *matrix, double *bbox,
		  GBool transpGroup, GBool softMask,
		  GfxColorSpace *blendingColorSpace,
		  GBool isolated, GBool knockout,
		  GBool alpha, Function *transferFunc,
		  GfxColor *backdropColor) {
  Parser *oldParser;
  double oldBaseMatrix[6];
  int i;

  pushResources(resDict);

  saveState();

  state->clearPath();

  oldParser = parser;

  state->concatCTM(matrix[0], matrix[1], matrix[2],
		   matrix[3], matrix[4], matrix[5]);
  out->updateCTM(state, matrix[0], matrix[1], matrix[2],
		 matrix[3], matrix[4], matrix[5]);

  state->moveTo(bbox[0], bbox[1]);
  state->lineTo(bbox[2], bbox[1]);
  state->lineTo(bbox[2], bbox[3]);
  state->lineTo(bbox[0], bbox[3]);
  state->closePath();
  state->clip();
  out->clip(state);
  state->clearPath();

  if (softMask || transpGroup) {
    if (state->getBlendMode() != gfxBlendNormal) {
      state->setBlendMode(gfxBlendNormal);
      out->updateBlendMode(state);
    }
    if (state->getFillOpacity() != 1) {
      state->setFillOpacity(1);
      out->updateFillOpacity(state);
    }
    if (state->getStrokeOpacity() != 1) {
      state->setStrokeOpacity(1);
      out->updateStrokeOpacity(state);
    }
    out->clearSoftMask(state);
    out->beginTransparencyGroup(state, bbox, blendingColorSpace,
				isolated, knockout, softMask);
  }

  for (i = 0; i < 6; ++i) {
    oldBaseMatrix[i] = baseMatrix[i];
    baseMatrix[i] = state->getCTM()[i];
  }

  GfxState *stateBefore = state;

  display(str, gFalse);
  
  if (stateBefore != state) {
    if (state->isParentState(stateBefore)) {
      error(-1, "There's a form with more q than Q, trying to fix");
      while (stateBefore != state) {
        restoreState();
      }
    } else {
      error(-1, "There's a form with more Q than q");
    }
  }

  if (softMask || transpGroup) {
    out->endTransparencyGroup(state);
  }

  for (i = 0; i < 6; ++i) {
    baseMatrix[i] = oldBaseMatrix[i];
  }

  parser = oldParser;

  restoreState();

  popResources();

  if (softMask) {
    out->setSoftMask(state, bbox, alpha, transferFunc, backdropColor);
  } else if (transpGroup) {
    out->paintTransparencyGroup(state, bbox);
  }

  return;
}
