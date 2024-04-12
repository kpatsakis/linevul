static void vmxnet3_validate_queues(VMXNET3State *s)
{
    /*
    * txq_num and rxq_num are total number of queues
    * configured by guest. These numbers must not
    * exceed corresponding maximal values.
    */

    if (s->txq_num > VMXNET3_DEVICE_MAX_TX_QUEUES) {
        hw_error("Bad TX queues number: %d\n", s->txq_num);
    }

    if (s->rxq_num > VMXNET3_DEVICE_MAX_RX_QUEUES) {
        hw_error("Bad RX queues number: %d\n", s->rxq_num);
    }
}