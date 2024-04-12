send_disable_carbons(void **state)
{
    prof_input("/carbons on");

    prof_connect();

    prof_input("/carbons off");

    assert_true(stbbr_received(
        "<iq id='*' type='set'><disable xmlns='urn:xmpp:carbons:2'/></iq>"
    ));
}
