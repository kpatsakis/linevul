base::Optional<Gamepad> GamepadBuilder::GetGamepad() const {
  if (IsValid())
    return gamepad_;

  return base::nullopt;
}
