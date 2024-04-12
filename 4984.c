e1000e_set_dbal(E1000ECore *core, int index, uint32_t val)
{
    core->mac[index] = val & E1000_XDBAL_MASK;
}
