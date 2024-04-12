static uint16_t transmit_data(serial_data_type_t type, uint8_t *data, uint16_t length) {
 if (type == DATA_TYPE_ACL) {
 return transmit_data_on(uart_fds[CH_ACL_OUT], data, length);
 } else if (type == DATA_TYPE_COMMAND) {
 return transmit_data_on(uart_fds[CH_CMD], data, length);
 }

  LOG_ERROR("%s invalid data type: %d", __func__, type);
 return 0;
}
