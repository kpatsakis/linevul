nautilus_directory_is_anyone_monitoring_file_list (NautilusDirectory *directory)
{
    if (directory->details->call_when_ready_counters[REQUEST_FILE_LIST] > 0)
    {
        return TRUE;
    }

    if (directory->details->monitor_counters[REQUEST_FILE_LIST] > 0)
    {
        return TRUE;
    }

    return FALSE;
}
