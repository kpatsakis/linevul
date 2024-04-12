static void cryptographicallyRandomValues(unsigned char* buffer, size_t length)
{
    Platform::current()->cryptographicallyRandomValues(buffer, length);
}
