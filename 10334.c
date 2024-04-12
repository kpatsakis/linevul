bool writeAll(std::ostream& out, const BigBuffer& buffer) {
 for (const auto& b : buffer) {
 if (!out.write(reinterpret_cast<const char*>(b.buffer.get()), b.size)) {
 return false;
 }
 }
 return true;
}
