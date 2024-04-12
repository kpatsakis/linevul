GBool PSOutputDev::checkPageSlice(Page *page, double /*hDPI*/, double /*vDPI*/,
				  int rotateA, GBool useMediaBox, GBool crop,
				  int sliceX, int sliceY,
				  int sliceW, int sliceH,
				  GBool printing, Catalog *catalog,
				  GBool (*abortCheckCbk)(void *data),
				  void *abortCheckCbkData) {
#if HAVE_SPLASH
  PreScanOutputDev *scan;
  GBool rasterize;
  SplashOutputDev *splashOut;
  SplashColor paperColor;
  PDFRectangle box;
  GfxState *state;
  SplashBitmap *bitmap;
  Stream *str0, *str;
  Object obj;
  Guchar *p;
  Guchar col[4];
  double m0, m1, m2, m3, m4, m5;
  int c, w, h, x, y, comp, i;

  if (!forceRasterize) {
    scan = new PreScanOutputDev();
    page->displaySlice(scan, 72, 72, rotateA, useMediaBox, crop,
                     sliceX, sliceY, sliceW, sliceH,
                     printing, catalog, abortCheckCbk, abortCheckCbkData);
    rasterize = scan->usesTransparency();
    delete scan;
  } else {
    rasterize = gTrue;
  }
  if (!rasterize) {
    return gTrue;
  }

  if (level == psLevel1) {
    paperColor[0] = 0xff;
    splashOut = new SplashOutputDev(splashModeMono8, 1, gFalse,
				    paperColor, gTrue, gFalse);
#if SPLASH_CMYK
  } else if (level == psLevel1Sep) {
    paperColor[0] = paperColor[1] = paperColor[2] = paperColor[3] = 0;
    splashOut = new SplashOutputDev(splashModeCMYK8, 1, gFalse,
				    paperColor, gTrue, gFalse);
#endif
  } else {
    paperColor[0] = paperColor[1] = paperColor[2] = 0xff;
    splashOut = new SplashOutputDev(splashModeRGB8, 1, gFalse,
				    paperColor, gTrue, gFalse);
  }
  splashOut->startDoc(xref);
  page->displaySlice(splashOut, splashDPI, splashDPI, rotateA,
		     useMediaBox, crop,
		     sliceX, sliceY, sliceW, sliceH,
		     printing, catalog, abortCheckCbk, abortCheckCbkData);

  page->makeBox(splashDPI, splashDPI, rotateA, useMediaBox, gFalse,
		sliceX, sliceY, sliceW, sliceH, &box, &crop);
  rotateA += page->getRotate();
  if (rotateA >= 360) {
    rotateA -= 360;
  } else if (rotateA < 0) {
    rotateA += 360;
  }
  state = new GfxState(splashDPI, splashDPI, &box, rotateA, gFalse);
  startPage(page->getNum(), state);
  delete state;
  switch (rotateA) {
  case 0:
  default:  // this should never happen
    m0 = box.x2 - box.x1;
    m1 = 0;
    m2 = 0;
    m3 = box.y2 - box.y1;
    m4 = box.x1;
    m5 = box.y1;
    break;
  case 90:
    m0 = 0;
    m1 = box.y2 - box.y1;
    m2 = -(box.x2 - box.x1);
    m3 = 0;
    m4 = box.x2;
    m5 = box.y1;
    break;
  case 180:
    m0 = -(box.x2 - box.x1);
    m1 = 0;
    m2 = 0;
    m3 = -(box.y2 - box.y1);
    m4 = box.x2;
    m5 = box.y2;
    break;
  case 270:
    m0 = 0;
    m1 = -(box.y2 - box.y1);
    m2 = box.x2 - box.x1;
    m3 = 0;
    m4 = box.x1;
    m5 = box.y2;
    break;
  }


  bitmap = splashOut->getBitmap();
  w = bitmap->getWidth();
  h = bitmap->getHeight();
  writePS("gsave\n");
  writePSFmt("[{0:.4g} {1:.4g} {2:.4g} {3:.4g} {4:.4g} {5:.4g}] concat\n",
	     m0, m1, m2, m3, m4, m5);
  switch (level) {
  case psLevel1:
    writePSFmt("{0:d} {1:d} 8 [{2:d} 0 0 {3:d} 0 {4:d}] pdfIm1\n",
	       w, h, w, -h, h);
    p = bitmap->getDataPtr();
    i = 0;
    for (y = 0; y < h; ++y) {
      for (x = 0; x < w; ++x) {
	writePSFmt("{0:02x}", *p++);
	if (++i == 32) {
	  writePSChar('\n');
	  i = 0;
	}
      }
    }
    if (i != 0) {
      writePSChar('\n');
    }
    break;
  case psLevel1Sep:
    writePSFmt("{0:d} {1:d} 8 [{2:d} 0 0 {3:d} 0 {4:d}] pdfIm1Sep\n",
	       w, h, w, -h, h);
    p = bitmap->getDataPtr();
    i = 0;
    col[0] = col[1] = col[2] = col[3] = 0;
    for (y = 0; y < h; ++y) {
      for (comp = 0; comp < 4; ++comp) {
	for (x = 0; x < w; ++x) {
	  writePSFmt("{0:02x}", p[4*x + comp]);
	  col[comp] |= p[4*x + comp];
	  if (++i == 32) {
	    writePSChar('\n');
	    i = 0;
	  }
	}
      }
      p += bitmap->getRowSize();
    }
    if (i != 0) {
      writePSChar('\n');
    }
    if (col[0]) {
      processColors |= psProcessCyan;
    }
    if (col[1]) {
      processColors |= psProcessMagenta;
    }
    if (col[2]) {
      processColors |= psProcessYellow;
    }
    if (col[3]) {
      processColors |= psProcessBlack;
    }
    break;
  case psLevel2:
  case psLevel2Sep:
  case psLevel3:
  case psLevel3Sep:
    writePS("/DeviceRGB setcolorspace\n");
    writePS("<<\n  /ImageType 1\n");
    writePSFmt("  /Width {0:d}\n", bitmap->getWidth());
    writePSFmt("  /Height {0:d}\n", bitmap->getHeight());
    writePSFmt("  /ImageMatrix [{0:d} 0 0 {1:d} 0 {2:d}]\n", w, -h, h);
    writePS("  /BitsPerComponent 8\n");
    writePS("  /Decode [0 1 0 1 0 1]\n");
    writePS("  /DataSource currentfile\n");
    if (globalParams->getPSASCIIHex()) {
      writePS("    /ASCIIHexDecode filter\n");
    } else {
      writePS("    /ASCII85Decode filter\n");
    }
    writePS("    /RunLengthDecode filter\n");
    writePS(">>\n");
    writePS("image\n");
    obj.initNull();
    str0 = new MemStream((char *)bitmap->getDataPtr(), 0, w * h * 3, &obj);
    str = new RunLengthEncoder(str0);
    if (globalParams->getPSASCIIHex()) {
      str = new ASCIIHexEncoder(str);
    } else {
      str = new ASCII85Encoder(str);
    }
    str->reset();
    while ((c = str->getChar()) != EOF) {
      writePSChar(c);
    }
    str->close();
    delete str;
    delete str0;
    processColors |= psProcessCMYK;
    break;
  }
  delete splashOut;
  writePS("grestore\n");

  endPage();

  return gFalse;
#else
  return gTrue;
#endif
}
