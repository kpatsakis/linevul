String ToHexString(const void* p) {
  return String::Format("0x%" PRIx64,
                        static_cast<uint64_t>(reinterpret_cast<uintptr_t>(p)));
}
