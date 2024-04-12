uint32_t DesktopWindowTreeHostX11::DispatchEvent(
    const ui::PlatformEvent& event) {
  XEvent* xev = event;

  TRACE_EVENT1("views", "DesktopWindowTreeHostX11::Dispatch",
               "event->type", event->type);

  UpdateWMUserTime(event);

  switch (xev->type) {
    case EnterNotify:
    case LeaveNotify: {
      OnCrossingEvent(xev->type == EnterNotify, xev->xcrossing.focus,
                      xev->xcrossing.mode, xev->xcrossing.detail);

      if (xev->xcrossing.detail != NotifyInferior) {
        ui::MouseEvent mouse_event(xev);
        DispatchMouseEvent(&mouse_event);
      }
      break;
    }
    case Expose: {
      gfx::Rect damage_rect_in_pixels(xev->xexpose.x, xev->xexpose.y,
                                      xev->xexpose.width, xev->xexpose.height);
      compositor()->ScheduleRedrawRect(damage_rect_in_pixels);
      break;
    }
    case KeyPress: {
      if (ui::AtkUtilAuraLinux::HandleKeyEvent(xev) !=
          ui::DiscardAtkKeyEvent::Discard) {
        ui::KeyEvent keydown_event(xev);
        DispatchKeyEvent(&keydown_event);
      }
      break;
    }
    case KeyRelease: {
      if (!IsActive() && !HasCapture())
        break;

      if (ui::AtkUtilAuraLinux::HandleKeyEvent(xev) !=
          ui::DiscardAtkKeyEvent::Discard) {
        ui::KeyEvent key_event(xev);
        DispatchKeyEvent(&key_event);
      }
      break;
    }
    case ButtonPress:
    case ButtonRelease: {
      ui::EventType event_type = ui::EventTypeFromNative(xev);
      switch (event_type) {
        case ui::ET_MOUSEWHEEL: {
          ui::MouseWheelEvent mouseev(xev);
          DispatchMouseEvent(&mouseev);
          break;
        }
        case ui::ET_MOUSE_PRESSED:
        case ui::ET_MOUSE_RELEASED: {
          ui::MouseEvent mouseev(xev);
          DispatchMouseEvent(&mouseev);
          break;
        }
        case ui::ET_UNKNOWN:
          break;
        default:
          NOTREACHED() << event_type;
      }
      break;
    }
    case x11::FocusIn:
    case x11::FocusOut:
      OnFocusEvent(xev->type == x11::FocusIn, event->xfocus.mode,
                   event->xfocus.detail);
      break;
    case ConfigureNotify: {
      DCHECK_EQ(xwindow_, xev->xconfigure.window);
      DCHECK_EQ(xwindow_, xev->xconfigure.event);
      int translated_x_in_pixels = xev->xconfigure.x;
      int translated_y_in_pixels = xev->xconfigure.y;
      if (!xev->xconfigure.send_event && !xev->xconfigure.override_redirect) {
        Window unused;
        XTranslateCoordinates(xdisplay_, xwindow_, x_root_window_, 0, 0,
                              &translated_x_in_pixels, &translated_y_in_pixels,
                              &unused);
      }
      gfx::Rect bounds_in_pixels(translated_x_in_pixels, translated_y_in_pixels,
                                 xev->xconfigure.width, xev->xconfigure.height);
      bool size_changed = bounds_in_pixels_.size() != bounds_in_pixels.size();
      bool origin_changed =
          bounds_in_pixels_.origin() != bounds_in_pixels.origin();
      previous_bounds_in_pixels_ = bounds_in_pixels_;
      bounds_in_pixels_ = bounds_in_pixels;

      if (origin_changed)
        OnHostMovedInPixels(bounds_in_pixels_.origin());

      if (size_changed)
        RestartDelayedResizeTask();
      break;
    }
    case GenericEvent: {
      ui::TouchFactory* factory = ui::TouchFactory::GetInstance();
      if (!factory->ShouldProcessXI2Event(xev))
        break;

      XIEnterEvent* enter_event = static_cast<XIEnterEvent*>(xev->xcookie.data);
      switch (static_cast<XIEvent*>(xev->xcookie.data)->evtype) {
        case XI_Enter:
        case XI_Leave:
          OnCrossingEvent(enter_event->evtype == XI_Enter, enter_event->focus,
                          XI2ModeToXMode(enter_event->mode),
                          enter_event->detail);
          return ui::POST_DISPATCH_STOP_PROPAGATION;
        case XI_FocusIn:
        case XI_FocusOut:
          OnFocusEvent(enter_event->evtype == XI_FocusIn,
                       XI2ModeToXMode(enter_event->mode), enter_event->detail);
          return ui::POST_DISPATCH_STOP_PROPAGATION;
        default:
          break;
      }

      ui::EventType type = ui::EventTypeFromNative(xev);
      XEvent last_event;
      int num_coalesced = 0;

      switch (type) {
        case ui::ET_TOUCH_MOVED:
          num_coalesced = ui::CoalescePendingMotionEvents(xev, &last_event);
          if (num_coalesced > 0)
            xev = &last_event;
          FALLTHROUGH;
        case ui::ET_TOUCH_PRESSED:
        case ui::ET_TOUCH_RELEASED: {
          ui::TouchEvent touchev(xev);
          DispatchTouchEvent(&touchev);
          break;
        }
        case ui::ET_MOUSE_MOVED:
        case ui::ET_MOUSE_DRAGGED:
        case ui::ET_MOUSE_PRESSED:
        case ui::ET_MOUSE_RELEASED:
        case ui::ET_MOUSE_ENTERED:
        case ui::ET_MOUSE_EXITED: {
          if (type == ui::ET_MOUSE_MOVED || type == ui::ET_MOUSE_DRAGGED) {
            num_coalesced = ui::CoalescePendingMotionEvents(xev, &last_event);
            if (num_coalesced > 0)
              xev = &last_event;
          }
          ui::MouseEvent mouseev(xev);
          if (mouseev.type() != ui::ET_UNKNOWN)
            DispatchMouseEvent(&mouseev);
          break;
        }
        case ui::ET_MOUSEWHEEL: {
          ui::MouseWheelEvent mouseev(xev);
          DispatchMouseEvent(&mouseev);
          break;
        }
        case ui::ET_SCROLL_FLING_START:
        case ui::ET_SCROLL_FLING_CANCEL:
        case ui::ET_SCROLL: {
          ui::ScrollEvent scrollev(xev);
          if (scrollev.x_offset() != 0.0 || scrollev.y_offset() != 0.0)
            SendEventToSink(&scrollev);
          break;
        }
        case ui::ET_KEY_PRESSED:
        case ui::ET_KEY_RELEASED: {
          ui::KeyEvent key_event(xev);
          DispatchKeyEvent(&key_event);
          break;
        }
        case ui::ET_UNKNOWN:
          break;
        default:
          NOTREACHED();
      }

      if (num_coalesced > 0)
        XFreeEventData(xev->xgeneric.display, &last_event.xcookie);
      break;
    }
    case MapNotify: {
      window_mapped_in_server_ = true;

      for (DesktopWindowTreeHostObserverX11& observer : observer_list_)
        observer.OnWindowMapped(xwindow_);

      if (should_maximize_after_map_) {
        Maximize();
        should_maximize_after_map_ = false;
      }

      break;
    }
    case UnmapNotify: {
      window_mapped_in_server_ = false;
      has_pointer_ = false;
      has_pointer_grab_ = false;
      has_pointer_focus_ = false;
      has_window_focus_ = false;
      for (DesktopWindowTreeHostObserverX11& observer : observer_list_)
        observer.OnWindowUnmapped(xwindow_);
      break;
    }
    case ClientMessage: {
      Atom message_type = xev->xclient.message_type;
      if (message_type == gfx::GetAtom("WM_PROTOCOLS")) {
        Atom protocol = static_cast<Atom>(xev->xclient.data.l[0]);
        if (protocol == gfx::GetAtom("WM_DELETE_WINDOW")) {
          OnHostCloseRequested();
        } else if (protocol == gfx::GetAtom("_NET_WM_PING")) {
          XEvent reply_event = *xev;
          reply_event.xclient.window = x_root_window_;

          XSendEvent(xdisplay_, reply_event.xclient.window, x11::False,
                     SubstructureRedirectMask | SubstructureNotifyMask,
                     &reply_event);
        }
      } else if (message_type == gfx::GetAtom("XdndEnter")) {
        drag_drop_client_->OnXdndEnter(xev->xclient);
      } else if (message_type == gfx::GetAtom("XdndLeave")) {
        drag_drop_client_->OnXdndLeave(xev->xclient);
      } else if (message_type == gfx::GetAtom("XdndPosition")) {
        drag_drop_client_->OnXdndPosition(xev->xclient);
      } else if (message_type == gfx::GetAtom("XdndStatus")) {
        drag_drop_client_->OnXdndStatus(xev->xclient);
      } else if (message_type == gfx::GetAtom("XdndFinished")) {
        drag_drop_client_->OnXdndFinished(xev->xclient);
      } else if (message_type == gfx::GetAtom("XdndDrop")) {
        drag_drop_client_->OnXdndDrop(xev->xclient);
      }
      break;
    }
    case MappingNotify: {
      switch (xev->xmapping.request) {
        case MappingModifier:
        case MappingKeyboard:
          XRefreshKeyboardMapping(&xev->xmapping);
          break;
        case MappingPointer:
          ui::DeviceDataManagerX11::GetInstance()->UpdateButtonMap();
          break;
        default:
          NOTIMPLEMENTED() << " Unknown request: " << xev->xmapping.request;
          break;
      }
      break;
    }
    case MotionNotify: {
      XEvent last_event;
      while (XPending(xev->xany.display)) {
        XEvent next_event;
        XPeekEvent(xev->xany.display, &next_event);
        if (next_event.type == MotionNotify &&
            next_event.xmotion.window == xev->xmotion.window &&
            next_event.xmotion.subwindow == xev->xmotion.subwindow &&
            next_event.xmotion.state == xev->xmotion.state) {
          XNextEvent(xev->xany.display, &last_event);
          xev = &last_event;
        } else {
          break;
        }
      }

      ui::MouseEvent mouseev(xev);
      DispatchMouseEvent(&mouseev);
      break;
    }
    case PropertyNotify: {
      XAtom changed_atom = xev->xproperty.atom;
      if (changed_atom == gfx::GetAtom("_NET_WM_STATE")) {
        OnWMStateUpdated();
      } else if (changed_atom == gfx::GetAtom("_NET_FRAME_EXTENTS")) {
        OnFrameExtentsUpdated();
      } else if (changed_atom == gfx::GetAtom("_NET_WM_DESKTOP")) {
        base::Optional<int> old_workspace = workspace_;
        UpdateWorkspace();
        if (workspace_ != old_workspace)
          OnHostWorkspaceChanged();
      }
      break;
    }
    case SelectionNotify: {
      drag_drop_client_->OnSelectionNotify(xev->xselection);
      break;
    }
  }
  return ui::POST_DISPATCH_STOP_PROPAGATION;
}
