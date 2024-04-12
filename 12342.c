void Backtrace::FillInMap(uintptr_t pc, backtrace_map_t* map) {
 if (map_ != nullptr) {
    map_->FillIn(pc, map);
 }
}
