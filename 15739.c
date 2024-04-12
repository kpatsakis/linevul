Backtrace::~Backtrace() {
 if (map_ && !map_shared_) {
 delete map_;
    map_ = nullptr;

   }
 }
