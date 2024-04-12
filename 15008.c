PermissionRequestGestureType PermissionUtil::GetGestureType(bool user_gesture) {
  return user_gesture ? PermissionRequestGestureType::GESTURE
                      : PermissionRequestGestureType::NO_GESTURE;
}
