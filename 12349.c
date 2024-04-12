void GamepadProvider::RemoveSourceGamepadDataFetcher(GamepadSource source) {
  polling_thread_->task_runner()->PostTask(
      FROM_HERE, base::Bind(&GamepadProvider::DoRemoveSourceGamepadDataFetcher,
                            base::Unretained(this), source));
}
