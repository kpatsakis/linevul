static void uipc_check_task_flags_locked(void)
{
 int i;

 for (i=0; i<UIPC_CH_NUM; i++)
 {
 if (uipc_main.ch[i].task_evt_flags & UIPC_TASK_FLAG_DISCONNECT_CHAN)
 {
            uipc_main.ch[i].task_evt_flags &= ~UIPC_TASK_FLAG_DISCONNECT_CHAN;
            uipc_close_ch_locked(i);
 }

 /* add here */

 }
}
