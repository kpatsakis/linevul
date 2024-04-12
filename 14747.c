void RunTwoClosures(const base::Closure* first, const base::Closure* second) {
  first->Run();
   second->Run();
 }
