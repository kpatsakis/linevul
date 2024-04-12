e1000e_get_reg_index_with_offset(const uint16_t *mac_reg_access, hwaddr addr)
{
    uint16_t index = (addr & 0x1ffff) >> 2;
    return index + (mac_reg_access[index] & 0xfffe);
}
