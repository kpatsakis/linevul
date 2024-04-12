int PDFiumEngine::Form_SetTimer(FPDF_FORMFILLINFO* param,
                                int elapse,
                                TimerCallback timer_func) {
  PDFiumEngine* engine = static_cast<PDFiumEngine*>(param);
  engine->timers_[++engine->next_timer_id_] =
      std::pair<int, TimerCallback>(elapse, timer_func);
  engine->client_->ScheduleCallback(engine->next_timer_id_, elapse);
  return engine->next_timer_id_;
}
