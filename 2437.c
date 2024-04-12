static VOID SharedMemAllocateCompleteHandler(
    IN NDIS_HANDLE  MiniportAdapterContext,
    IN PVOID  VirtualAddress,
    IN PNDIS_PHYSICAL_ADDRESS  PhysicalAddress,
    IN ULONG  Length,
    IN PVOID  Context
    )
{
    UNREFERENCED_PARAMETER(MiniportAdapterContext);
    UNREFERENCED_PARAMETER(VirtualAddress);
    UNREFERENCED_PARAMETER(PhysicalAddress);
    UNREFERENCED_PARAMETER(Length);
    UNREFERENCED_PARAMETER(Context);
}
