void GLES2DecoderImpl::DoLinkProgram(GLuint program_id) {
  TRACE_EVENT0("gpu", "GLES2DecoderImpl::DoLinkProgram");
  SCOPED_UMA_HISTOGRAM_TIMER("GPU.DoLinkProgramTime");
  Program* program = GetProgramInfoNotShader(
      program_id, "glLinkProgram");
  if (!program) {
    return;
  }

  LogClientServiceForInfo(program, program_id, "glLinkProgram");
  if (program->Link(shader_manager(),
                    workarounds().count_all_in_varyings_packing
                        ? Program::kCountAll
                        : Program::kCountOnlyStaticallyUsed,
                    client())) {
    if (program == state_.current_program.get()) {
      if (workarounds().clear_uniforms_before_first_program_use)
        program_manager()->ClearUniforms(program);
    }
    if (features().webgl_multi_draw || features().webgl_multi_draw_instanced)
      program_manager()->UpdateDrawIDUniformLocation(program);
  }

  ExitCommandProcessingEarly();
}
