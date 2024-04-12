process_mouse(int btn, int x, int y)
{
    int delta_x, delta_y, i;
    static int press_btn = MOUSE_BTN_RESET, press_x, press_y;
    TabBuffer *t;
    int ny = -1;

    if (nTab > 1 || mouse_action.menu_str)
	ny = LastTab->y + 1;
    if (btn == MOUSE_BTN_UP) {
	switch (press_btn) {
	case MOUSE_BTN1_DOWN:
	    if (press_y == y && press_x == x)
		do_mouse_action(press_btn, x, y);
	    else if (ny > 0 && y < ny) {
		if (press_y < ny) {
		    moveTab(posTab(press_x, press_y), posTab(x, y),
			    (press_y == y) ? (press_x < x) : (press_y < y));
		    return;
		}
		else if (press_x >= Currentbuf->rootX) {
		    Buffer *buf = Currentbuf;
		    int cx = Currentbuf->cursorX, cy = Currentbuf->cursorY;

		    t = posTab(x, y);
		    if (t == NULL)
			return;
		    if (t == NO_TABBUFFER)
			t = NULL;	/* open new tab */
		    cursorXY(Currentbuf, press_x - Currentbuf->rootX,
			     press_y - Currentbuf->rootY);
		    if (Currentbuf->cursorY == press_y - Currentbuf->rootY &&
			(Currentbuf->cursorX == press_x - Currentbuf->rootX
#ifdef USE_M17N
			 || (WcOption.use_wide &&
			     Currentbuf->currentLine != NULL &&
			     (CharType(Currentbuf->currentLine->
				       propBuf[Currentbuf->pos]) == PC_KANJI1)
			     && Currentbuf->cursorX == press_x
			     - Currentbuf->rootX - 1)
#endif
			)) {
			displayBuffer(Currentbuf, B_NORMAL);
			followTab(t);
		    }
		    if (buf == Currentbuf)
			cursorXY(Currentbuf, cx, cy);
		}
		return;
	    }
	    else {
		delta_x = x - press_x;
		delta_y = y - press_y;

		if (abs(delta_x) < abs(delta_y) / 3)
		    delta_x = 0;
		if (abs(delta_y) < abs(delta_x) / 3)
		    delta_y = 0;
		if (reverse_mouse) {
		    delta_y = -delta_y;
		    delta_x = -delta_x;
		}
		if (delta_y > 0) {
		    prec_num = delta_y;
		    ldown1();
		}
		else if (delta_y < 0) {
		    prec_num = -delta_y;
		    lup1();
		}
		if (delta_x > 0) {
		    prec_num = delta_x;
		    col1L();
		}
		else if (delta_x < 0) {
		    prec_num = -delta_x;
		    col1R();
		}
	    }
	    break;
	case MOUSE_BTN2_DOWN:
	case MOUSE_BTN3_DOWN:
	    if (press_y == y && press_x == x)
		do_mouse_action(press_btn, x, y);
	    break;
	case MOUSE_BTN4_DOWN_RXVT:
	    for (i = 0; i < mouse_scroll_line(); i++)
		ldown1();
	    break;
	case MOUSE_BTN5_DOWN_RXVT:
	    for (i = 0; i < mouse_scroll_line(); i++)
		lup1();
	    break;
	}
    }
    else if (btn == MOUSE_BTN4_DOWN_XTERM) {
	for (i = 0; i < mouse_scroll_line(); i++)
	    ldown1();
    }
    else if (btn == MOUSE_BTN5_DOWN_XTERM) {
	for (i = 0; i < mouse_scroll_line(); i++)
	    lup1();
    }

    if (btn != MOUSE_BTN4_DOWN_RXVT || press_btn == MOUSE_BTN_RESET) {
	press_btn = btn;
	press_x = x;
	press_y = y;
    }
    else {
	press_btn = MOUSE_BTN_RESET;
    }
}
