bool Backtrace::VerifyReadWordArgs(uintptr_t ptr, word_t* out_value) {
 if (ptr & (sizeof(word_t)-1)) {
    BACK_LOGW("invalid pointer %p", reinterpret_cast<void*>(ptr));
 *out_value = static_cast<word_t>(-1);
 return false;
 }
 return true;
}
