void mca_ccb_ll_open(tMCA_CCB* p_ccb, tMCA_CCB_EVT* p_data) {
  tMCA_CTRL evt_data;
  p_ccb->cong = false;
  evt_data.connect_ind.mtu = p_data->open.peer_mtu;
  evt_data.connect_ind.bd_addr = p_ccb->peer_addr;
  mca_ccb_report_event(p_ccb, MCA_CONNECT_IND_EVT, &evt_data);
}
