TabletEventConverterEvdev::TabletEventConverterEvdev(
    int fd,
    base::FilePath path,
    int id,
    InputDeviceType type,
    CursorDelegateEvdev* cursor,
    const EventDeviceInfo& info,
    DeviceEventDispatcherEvdev* dispatcher)
    : EventConverterEvdev(fd,
                          path,
                          id,
                          type,
                          info.name(),
                          info.vendor_id(),
                          info.product_id()),
      cursor_(cursor),
      dispatcher_(dispatcher),
      stylus_(0),
      abs_value_dirty_(false) {
  x_abs_min_ = info.GetAbsMinimum(ABS_X);
  x_abs_range_ = info.GetAbsMaximum(ABS_X) - x_abs_min_ + 1;
  y_abs_min_ = info.GetAbsMinimum(ABS_Y);
  y_abs_range_ = info.GetAbsMaximum(ABS_Y) - y_abs_min_ + 1;
}
