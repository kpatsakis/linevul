int select_files(const struct dirent *dirbuf)
{
    if (dirbuf->d_name[0] == '.')
        return 0;
    else
        return 1;
}
