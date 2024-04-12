Function::Function(const Function *func) {
    m = func->m;
    n = func->n;

    memcpy(domain, func->domain, funcMaxInputs * 2 * sizeof(double));
    memcpy(range, func->range, funcMaxOutputs * 2 * sizeof(double));

    hasRange = func->hasRange;
}
