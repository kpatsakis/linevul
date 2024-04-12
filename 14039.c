int main(int argc, char **argv)
{
    /* I18n */
    setlocale(LC_ALL, "");
#if ENABLE_NLS
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);
#endif

    abrt_init(argv);

    /* Can't keep these strings/structs static: _() doesn't support that */
    const char *program_usage_string = _(
        "& [-vusoxm] [-d DIR]/[-D] [FILE]\n"
        "\n"
        "Extract oops from FILE (or standard input)"
    );
    enum {
        OPT_v = 1 << 0,
        OPT_s = 1 << 1,
        OPT_o = 1 << 2,
        OPT_d = 1 << 3,
        OPT_D = 1 << 4,
        OPT_u = 1 << 5,
        OPT_x = 1 << 6,
        OPT_t = 1 << 7,
        OPT_m = 1 << 8,
    };
    char *problem_dir = NULL;
    /* Keep enum above and order of options below in sync! */
    struct options program_options[] = {
        OPT__VERBOSE(&g_verbose),
        OPT_BOOL(  's', NULL, NULL, _("Log to syslog")),
        OPT_BOOL(  'o', NULL, NULL, _("Print found oopses on standard output")),
        /* oopses don't contain any sensitive info, and even
         * the old koops app was showing the oopses to all users
         */
        OPT_STRING('d', NULL, &debug_dumps_dir, "DIR", _("Create new problem directory in DIR for every oops found")),
        OPT_BOOL(  'D', NULL, NULL, _("Same as -d DumpLocation, DumpLocation is specified in abrt.conf")),
        OPT_STRING('u', NULL, &problem_dir, "PROBLEM", _("Save the extracted information in PROBLEM")),
        OPT_BOOL(  'x', NULL, NULL, _("Make the problem directory world readable")),
        OPT_BOOL(  't', NULL, NULL, _("Throttle problem directory creation to 1 per second")),
        OPT_BOOL(  'm', NULL, NULL, _("Print search string(s) to stdout and exit")),
        OPT_END()
    };
    unsigned opts = parse_opts(argc, argv, program_options, program_usage_string);

    export_abrt_envvars(0);

    msg_prefix = g_progname;
    if ((opts & OPT_s) || getenv("ABRT_SYSLOG"))
    {
        logmode = LOGMODE_JOURNAL;
    }

    if (opts & OPT_m)
    {
        map_string_t *settings = new_map_string();

        load_abrt_plugin_conf_file("oops.conf", settings);

        int only_fatal_mce = 1;
        try_get_map_string_item_as_bool(settings, "OnlyFatalMCE", &only_fatal_mce);

        free_map_string(settings);

        if (only_fatal_mce)
        {
            regex_t mce_re;
            if (regcomp(&mce_re, "^Machine .*$", REG_NOSUB) != 0)
                perror_msg_and_die(_("Failed to compile regex"));

            const regex_t *filter[] = { &mce_re, NULL };

            koops_print_suspicious_strings_filtered(filter);

            regfree(&mce_re);
        }
        else
            koops_print_suspicious_strings();

        return 1;
    }

    if (opts & OPT_D)
    {
        if (opts & OPT_d)
            show_usage_and_die(program_usage_string, program_options);
        load_abrt_conf();
        debug_dumps_dir = g_settings_dump_location;
        g_settings_dump_location = NULL;
        free_abrt_conf_data();
    }

    argv += optind;
    if (argv[0])
        xmove_fd(xopen(argv[0], O_RDONLY), STDIN_FILENO);

    world_readable_dump = (opts & OPT_x);
    throttle_dd_creation = (opts & OPT_t);
    unsigned errors = 0;
    GList *oops_list = NULL;
    scan_syslog_file(&oops_list, STDIN_FILENO);

    int oops_cnt = g_list_length(oops_list);
    if (oops_cnt != 0)
    {
        log("Found oopses: %d", oops_cnt);
        if (opts & OPT_o)
        {
            int i = 0;
            while (i < oops_cnt)
            {
                char *kernel_bt = (char*)g_list_nth_data(oops_list, i++);
                char *tainted_short = kernel_tainted_short(kernel_bt);
                if (tainted_short)
                    log("Kernel is tainted '%s'", tainted_short);

                free(tainted_short);
                printf("\nVersion: %s", kernel_bt);
            }
        }
        if (opts & (OPT_d|OPT_D))
        {
            if (opts & OPT_D)
            {
                load_abrt_conf();
                debug_dumps_dir = g_settings_dump_location;
            }

            log("Creating problem directories");
            errors = create_oops_dump_dirs(oops_list, oops_cnt);
            if (errors)
                log("%d errors while dumping oopses", errors);
            /*
             * This marker in syslog file prevents us from
             * re-parsing old oopses. The only problem is that we
             * can't be sure here that the file we are watching
             * is the same file where syslog(xxx) stuff ends up.
             */
            syslog(LOG_WARNING,
                    "Reported %u kernel oopses to Abrt",
                    oops_cnt
            );
        }
        if (opts & OPT_u)
        {
            log("Updating problem directory");
            switch (oops_cnt)
            {
                case 1:
                    {
                        struct dump_dir *dd = dd_opendir(problem_dir, /*open for writing*/0);
                        if (dd)
                        {
                            save_oops_data_in_dump_dir(dd, (char *)oops_list->data, /*no proc modules*/NULL);
                            dd_close(dd);
                        }
                    }
                    break;
                default:
                    error_msg(_("Can't update the problem: more than one oops found"));
                    break;
            }
        }
    }
    list_free_with_free(oops_list);

    /* If we are run by a log watcher, this delays log rescan
     * (because log watcher waits to us to terminate)
     * and possibly prevents dreaded "abrt storm".
     */
    int unreported_cnt = oops_cnt - MAX_DUMPED_DD_COUNT;
    if (unreported_cnt > 0 && throttle_dd_creation)
    {
        /* Quadratic throttle time growth, but careful to not overflow in "n*n" */
        int n = unreported_cnt > 30 ? 30 : unreported_cnt;
        n = n * n;
        if (n > 9)
            log(_("Sleeping for %d seconds"), n);
        sleep(n); /* max 15 mins */
    }

    return errors;
}
