bool CopyDirectory(const FilePath& from_path,
const FilePath& to_path,
bool recursive) {
base::ThreadRestrictions::AssertIOAllowed();
// Some old callers of CopyDirectory want it to support wildcards.
// After some discussion, we decided to fix those callers.
// Break loudly here if anyone tries to do this.
// TODO(evanm): remove this once we're sure it's ok.
DCHECK(to_path.value().find('*') == std::string::npos);
DCHECK(from_path.value().find('*') == std::string::npos);

char top_dir[PATH_MAX];
if (base::strlcpy(top_dir, from_path.value().c_str(),
arraysize(top_dir)) >= arraysize(top_dir)) {
return false;
}

// This function does not properly handle destinations within the source
FilePath real_to_path = to_path;
if (PathExists(real_to_path)) {
if (!AbsolutePath(&real_to_path))
return false;
} else {
real_to_path = real_to_path.DirName();
if (!AbsolutePath(&real_to_path))
return false;
}
FilePath real_from_path = from_path;
if (!AbsolutePath(&real_from_path))
return false;
if (real_to_path.value().size() >= real_from_path.value().size() &&
real_to_path.value().compare(0, real_from_path.value().size(),
real_from_path.value()) == 0)
return false;

bool success = true;
int traverse_type = FileEnumerator::FILES | FileEnumerator::SHOW_SYM_LINKS;
if (recursive)
traverse_type |= FileEnumerator::DIRECTORIES;
FileEnumerator traversal(from_path, recursive, traverse_type);

// We have to mimic windows behavior here. |to_path| may not exist yet,
// start the loop with |to_path|.
FileEnumerator::FindInfo info;
FilePath current = from_path;
if (stat(from_path.value().c_str(), &info.stat) < 0) {
DLOG(ERROR) << "CopyDirectory() couldn't stat source directory: "
<< from_path.value() << " errno = " << errno;
success = false;
}
struct stat to_path_stat;
FilePath from_path_base = from_path;
if (recursive && stat(to_path.value().c_str(), &to_path_stat) == 0 &&
S_ISDIR(to_path_stat.st_mode)) {
// If the destination already exists and is a directory, then the
// top level of source needs to be copied.
from_path_base = from_path.DirName();
}

// The Windows version of this function assumes that non-recursive calls
// will always have a directory for from_path.
DCHECK(recursive || S_ISDIR(info.stat.st_mode));

while (success && !current.empty()) {
    // current is the source path, including from_path, so paste
    // the suffix after from_path onto to_path to create the target_path.
    std::string suffix(&current.value().c_str()[from_path_base.value().size()]);
    // Strip the leading '/' (if any).
    if (!suffix.empty()) {
      DCHECK_EQ('/', suffix[0]);
      suffix.erase(0, 1);
}
    const FilePath target_path = to_path.Append(suffix);

if (S_ISDIR(info.stat.st_mode)) {
if (mkdir(target_path.value().c_str(), info.stat.st_mode & 01777) != 0 &&
errno != EEXIST) {
DLOG(ERROR) << "CopyDirectory() couldn't create directory: "
<< target_path.value() << " errno = " << errno;
success = false;
}
} else if (S_ISREG(info.stat.st_mode)) {
if (!CopyFile(current, target_path)) {
DLOG(ERROR) << "CopyDirectory() couldn't create file: "
<< target_path.value();
success = false;
}
} else {
DLOG(WARNING) << "CopyDirectory() skipping non-regular file: "
<< current.value();
}

current = traversal.Next();
traversal.GetFindInfo(&info);
}

return success;
}
