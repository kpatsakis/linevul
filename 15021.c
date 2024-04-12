void ValidateAllTraceMacrosCreatedData(const ListValue& trace_parsed) {
  const DictionaryValue* item = NULL;

#define EXPECT_FIND_(string) \
    item = FindTraceEntry(trace_parsed, string); \
    EXPECT_TRUE(item);
#define EXPECT_NOT_FIND_(string) \
    item = FindTraceEntry(trace_parsed, string); \
    EXPECT_FALSE(item);
#define EXPECT_SUB_FIND_(string) \
    if (item) \
      EXPECT_TRUE(IsStringInDict(string, item));

  EXPECT_FIND_("TRACE_EVENT0 call");
  {
    std::string ph;
    std::string ph_end;
    EXPECT_TRUE((item = FindTraceEntry(trace_parsed, "TRACE_EVENT0 call")));
    EXPECT_TRUE((item && item->GetString("ph", &ph)));
    EXPECT_EQ("X", ph);
    item = FindTraceEntry(trace_parsed, "TRACE_EVENT0 call", item);
    EXPECT_FALSE(item);
  }
  EXPECT_FIND_("TRACE_EVENT1 call");
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_FIND_("TRACE_EVENT2 call");
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("\"value1\"");
  EXPECT_SUB_FIND_("name2");
  EXPECT_SUB_FIND_("value\\2");

  EXPECT_FIND_("TRACE_EVENT_INSTANT0 call");
  {
    std::string scope;
    EXPECT_TRUE((item && item->GetString("s", &scope)));
    EXPECT_EQ("g", scope);
  }
  EXPECT_FIND_("TRACE_EVENT_INSTANT1 call");
  {
    std::string scope;
    EXPECT_TRUE((item && item->GetString("s", &scope)));
    EXPECT_EQ("p", scope);
  }
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_FIND_("TRACE_EVENT_INSTANT2 call");
  {
    std::string scope;
    EXPECT_TRUE((item && item->GetString("s", &scope)));
    EXPECT_EQ("t", scope);
  }
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_SUB_FIND_("name2");
  EXPECT_SUB_FIND_("value2");

  EXPECT_FIND_("TRACE_EVENT_BEGIN0 call");
  EXPECT_FIND_("TRACE_EVENT_BEGIN1 call");
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_FIND_("TRACE_EVENT_BEGIN2 call");
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_SUB_FIND_("name2");
  EXPECT_SUB_FIND_("value2");

  EXPECT_FIND_("TRACE_EVENT_END0 call");
  EXPECT_FIND_("TRACE_EVENT_END1 call");
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_FIND_("TRACE_EVENT_END2 call");
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_SUB_FIND_("name2");
  EXPECT_SUB_FIND_("value2");

  EXPECT_FIND_("TRACE_EVENT_ASYNC_BEGIN0 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_FIND_("TRACE_EVENT_ASYNC_BEGIN1 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_FIND_("TRACE_EVENT_ASYNC_BEGIN2 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_SUB_FIND_("name2");
  EXPECT_SUB_FIND_("value2");

  EXPECT_FIND_("TRACE_EVENT_ASYNC_STEP_INTO0 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_SUB_FIND_("step_begin1");
  EXPECT_FIND_("TRACE_EVENT_ASYNC_STEP_INTO1 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_SUB_FIND_("step_begin2");
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");

  EXPECT_FIND_("TRACE_EVENT_ASYNC_END0 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_FIND_("TRACE_EVENT_ASYNC_END1 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_FIND_("TRACE_EVENT_ASYNC_END2 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kAsyncIdStr);
  EXPECT_SUB_FIND_("name1");
  EXPECT_SUB_FIND_("value1");
  EXPECT_SUB_FIND_("name2");
  EXPECT_SUB_FIND_("value2");

  EXPECT_FIND_("TRACE_EVENT_FLOW_BEGIN0 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kFlowIdStr);
  EXPECT_FIND_("TRACE_EVENT_FLOW_STEP0 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kFlowIdStr);
  EXPECT_SUB_FIND_("step1");
  EXPECT_FIND_("TRACE_EVENT_FLOW_END_BIND_TO_ENCLOSING0 call");
  EXPECT_SUB_FIND_("id");
  EXPECT_SUB_FIND_(kFlowIdStr);

  EXPECT_FIND_("TRACE_COUNTER1 call");
  {
    std::string ph;
    EXPECT_TRUE((item && item->GetString("ph", &ph)));
    EXPECT_EQ("C", ph);

    int value;
    EXPECT_TRUE((item && item->GetInteger("args.value", &value)));
    EXPECT_EQ(31415, value);
  }

  EXPECT_FIND_("TRACE_COUNTER2 call");
  {
    std::string ph;
    EXPECT_TRUE((item && item->GetString("ph", &ph)));
    EXPECT_EQ("C", ph);

    int value;
    EXPECT_TRUE((item && item->GetInteger("args.a", &value)));
    EXPECT_EQ(30000, value);

    EXPECT_TRUE((item && item->GetInteger("args.b", &value)));
    EXPECT_EQ(1415, value);
  }

  EXPECT_FIND_("TRACE_COUNTER_ID1 call");
  {
    std::string id;
    EXPECT_TRUE((item && item->GetString("id", &id)));
    EXPECT_EQ("0x319009", id);

    std::string ph;
    EXPECT_TRUE((item && item->GetString("ph", &ph)));
    EXPECT_EQ("C", ph);

    int value;
    EXPECT_TRUE((item && item->GetInteger("args.value", &value)));
    EXPECT_EQ(31415, value);
  }

  EXPECT_FIND_("TRACE_COUNTER_ID2 call");
  {
    std::string id;
    EXPECT_TRUE((item && item->GetString("id", &id)));
    EXPECT_EQ("0x319009", id);

    std::string ph;
    EXPECT_TRUE((item && item->GetString("ph", &ph)));
    EXPECT_EQ("C", ph);

    int value;
    EXPECT_TRUE((item && item->GetInteger("args.a", &value)));
    EXPECT_EQ(30000, value);

    EXPECT_TRUE((item && item->GetInteger("args.b", &value)));
    EXPECT_EQ(1415, value);
  }

  EXPECT_FIND_("TRACE_EVENT_COPY_BEGIN_WITH_ID_TID_AND_TIMESTAMP0 call");
  {
    int val;
    EXPECT_TRUE((item && item->GetInteger("ts", &val)));
    EXPECT_EQ(12345, val);
    EXPECT_TRUE((item && item->GetInteger("tid", &val)));
    EXPECT_EQ(kThreadId, val);
    std::string id;
    EXPECT_TRUE((item && item->GetString("id", &id)));
    EXPECT_EQ(kAsyncIdStr, id);
  }

  EXPECT_FIND_("TRACE_EVENT_COPY_END_WITH_ID_TID_AND_TIMESTAMP0 call");
  {
    int val;
    EXPECT_TRUE((item && item->GetInteger("ts", &val)));
    EXPECT_EQ(23456, val);
    EXPECT_TRUE((item && item->GetInteger("tid", &val)));
    EXPECT_EQ(kThreadId, val);
    std::string id;
    EXPECT_TRUE((item && item->GetString("id", &id)));
    EXPECT_EQ(kAsyncIdStr, id);
  }

  EXPECT_FIND_("TRACE_EVENT_BEGIN_WITH_ID_TID_AND_TIMESTAMP0 call");
  {
    int val;
    EXPECT_TRUE((item && item->GetInteger("ts", &val)));
    EXPECT_EQ(34567, val);
    EXPECT_TRUE((item && item->GetInteger("tid", &val)));
    EXPECT_EQ(kThreadId, val);
    std::string id;
    EXPECT_TRUE((item && item->GetString("id", &id)));
    EXPECT_EQ(kAsyncId2Str, id);
  }

  EXPECT_FIND_("TRACE_EVENT_ASYNC_STEP_PAST0 call");
  {
    EXPECT_SUB_FIND_("id");
    EXPECT_SUB_FIND_(kAsyncId2Str);
    EXPECT_SUB_FIND_("step_end1");
    EXPECT_FIND_("TRACE_EVENT_ASYNC_STEP_PAST1 call");
    EXPECT_SUB_FIND_("id");
    EXPECT_SUB_FIND_(kAsyncId2Str);
    EXPECT_SUB_FIND_("step_end2");
    EXPECT_SUB_FIND_("name1");
    EXPECT_SUB_FIND_("value1");
  }

  EXPECT_FIND_("TRACE_EVENT_END_WITH_ID_TID_AND_TIMESTAMP0 call");
  {
    int val;
    EXPECT_TRUE((item && item->GetInteger("ts", &val)));
    EXPECT_EQ(45678, val);
    EXPECT_TRUE((item && item->GetInteger("tid", &val)));
    EXPECT_EQ(kThreadId, val);
    std::string id;
    EXPECT_TRUE((item && item->GetString("id", &id)));
    EXPECT_EQ(kAsyncId2Str, id);
  }

  EXPECT_FIND_("tracked object 1");
  {
    std::string phase;
    std::string id;
    std::string snapshot;

    EXPECT_TRUE((item && item->GetString("ph", &phase)));
    EXPECT_EQ("N", phase);
    EXPECT_TRUE((item && item->GetString("id", &id)));
    EXPECT_EQ("0x42", id);

    item = FindTraceEntry(trace_parsed, "tracked object 1", item);
    EXPECT_TRUE(item);
    EXPECT_TRUE(item && item->GetString("ph", &phase));
    EXPECT_EQ("O", phase);
    EXPECT_TRUE(item && item->GetString("id", &id));
    EXPECT_EQ("0x42", id);
    EXPECT_TRUE(item && item->GetString("args.snapshot", &snapshot));
    EXPECT_EQ("hello", snapshot);

    item = FindTraceEntry(trace_parsed, "tracked object 1", item);
    EXPECT_TRUE(item);
    EXPECT_TRUE(item && item->GetString("ph", &phase));
    EXPECT_EQ("D", phase);
    EXPECT_TRUE(item && item->GetString("id", &id));
    EXPECT_EQ("0x42", id);
  }

  EXPECT_FIND_("tracked object 2");
  {
    std::string phase;
    std::string id;
    std::string snapshot;

    EXPECT_TRUE(item && item->GetString("ph", &phase));
    EXPECT_EQ("N", phase);
    EXPECT_TRUE(item && item->GetString("id", &id));
    EXPECT_EQ("0x2128506", id);

    item = FindTraceEntry(trace_parsed, "tracked object 2", item);
    EXPECT_TRUE(item);
    EXPECT_TRUE(item && item->GetString("ph", &phase));
    EXPECT_EQ("O", phase);
    EXPECT_TRUE(item && item->GetString("id", &id));
    EXPECT_EQ("0x2128506", id);
    EXPECT_TRUE(item && item->GetString("args.snapshot", &snapshot));
    EXPECT_EQ("world", snapshot);

    item = FindTraceEntry(trace_parsed, "tracked object 2", item);
    EXPECT_TRUE(item);
    EXPECT_TRUE(item && item->GetString("ph", &phase));
    EXPECT_EQ("D", phase);
    EXPECT_TRUE(item && item->GetString("id", &id));
    EXPECT_EQ("0x2128506", id);
  }

  EXPECT_FIND_(kControlCharacters);
  EXPECT_SUB_FIND_(kControlCharacters);
}
