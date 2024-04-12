double ExecutableAllocator::memoryPressureMultiplier(size_t addedMemoryUsage)
{
    MetaAllocator::Statistics statistics = allocator->currentStatistics();
    ASSERT(statistics.bytesAllocated <= statistics.bytesReserved);
    size_t bytesAllocated = statistics.bytesAllocated + addedMemoryUsage;
    if (bytesAllocated >= statistics.bytesReserved)
        bytesAllocated = statistics.bytesReserved;
    double result = 1.0;
    size_t divisor = statistics.bytesReserved - bytesAllocated;
    if (divisor)
        result = static_cast<double>(statistics.bytesReserved) / divisor;
    if (result < 1.0)
        result = 1.0;
    return result;
}
