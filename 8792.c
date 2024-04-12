iperf_json_start(struct iperf_test *test)
{
    test->json_top = cJSON_CreateObject();
    if (test->json_top == NULL)
        return -1;
    if (test->title)
	cJSON_AddStringToObject(test->json_top, "title", test->title);
    test->json_start = cJSON_CreateObject();
    if (test->json_start == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_top, "start", test->json_start);
    test->json_connected = cJSON_CreateArray();
    if (test->json_connected == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_start, "connected", test->json_connected);
    test->json_intervals = cJSON_CreateArray();
    if (test->json_intervals == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_top, "intervals", test->json_intervals);
    test->json_end = cJSON_CreateObject();
    if (test->json_end == NULL)
        return -1;
    cJSON_AddItemToObject(test->json_top, "end", test->json_end);
    return 0;
}
