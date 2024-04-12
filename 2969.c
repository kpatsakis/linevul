string16 AppListController::GetAppListIconPath() {
  base::FilePath icon_path;
  if (!PathService::Get(base::FILE_EXE, &icon_path)) {
    NOTREACHED();
    return string16();
  }

  std::stringstream ss;
  ss << "," << GetAppListIconIndex();
  string16 result = icon_path.value();
  result.append(UTF8ToUTF16(ss.str()));
  return result;
}
