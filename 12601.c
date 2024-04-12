  base::FilePath GetTeamDrivePath(const std::string& team_drive_name) {
    return GetTeamDriveGrandRoot().Append(team_drive_name);
  }
