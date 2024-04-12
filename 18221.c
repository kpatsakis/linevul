struct arg arg_init(char **argv) {
 struct arg a;

  a.argv      = argv;
  a.argv_step = 1;
  a.name      = NULL;
  a.val       = NULL;
  a.def       = NULL;
 return a;
}
