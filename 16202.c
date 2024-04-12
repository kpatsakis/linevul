static int do_explicit_dump(pid_t tid, bool dump_backtrace) {
  fprintf(stdout, "Sending request to dump task %d.\n", tid);

 if (dump_backtrace) {
    fflush(stdout);
 if (dump_backtrace_to_file(tid, fileno(stdout)) < 0) {
      fputs("Error dumping backtrace.\n", stderr);
 return 1;
 }
 } else {
 char tombstone_path[PATH_MAX];
 if (dump_tombstone(tid, tombstone_path, sizeof(tombstone_path)) < 0) {
      fputs("Error dumping tombstone.\n", stderr);
 return 1;
 }
    fprintf(stderr, "Tombstone written to: %s\n", tombstone_path);
 }
 return 0;
}
