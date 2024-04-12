int XI2ModeToXMode(int xi2_mode) {
  switch (xi2_mode) {
    case XINotifyNormal:
      return NotifyNormal;
    case XINotifyGrab:
    case XINotifyPassiveGrab:
      return NotifyGrab;
    case XINotifyUngrab:
    case XINotifyPassiveUngrab:
      return NotifyUngrab;
    case XINotifyWhileGrabbed:
      return NotifyWhileGrabbed;
    default:
      NOTREACHED();
      return NotifyNormal;
  }
}
