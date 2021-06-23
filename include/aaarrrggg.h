    /* I2C pin numbers */
    if (var == "WT_SDASCL")
    {
        return getSDASCL();
    }
    if (var == "WT_I2C")
    {
        return getI2Cscan();
    }


    if (var == "WT_IP")
    {
        return ip3string(WiFi.localIP());
    }
    if (var == "WT_MAC")
    {
        return WiFi.macAddress();
    }

    if (var == "uptime")
    {
        return info_uptime();
    }
    if (var == "chipid")
    {
        return info_chipid();
    }
    if (var == "idesize")
    {
        return info_idesize();
    }
    if (var == "flashsize")
    {
        return info_flashsize();
    }
    if (var == "sdkver")
    {
        return info_sdkver();
    }
    if (var == "cpufreq")
    {
        return info_cpufreq();
    }
    if (var == "freeheap")
    {
        return info_freeheap();
    }
    if (var == "memsketch")
    {
        return info_memsketch();
    }
    if (var == "lastreset")
    {
        return info_lastreset();
    }
    if (var == "conx")
    {
        return info_conx();
    }
    if (var == "stassid")
    {
        return info_stassid();
    }
    if (var == "staip")
    {
        return info_staip();
    }
    if (var == "stamac")
    {
        return info_stamac();
    }
    if (var == "stagw")
    {
        return info_stagw();
    }
    if (var == "stasub")
    {
        return info_stasub();
    }
    if (var == "dnss")
    {
        return info_dnss();
    }
    if (var == "hostnom")
    {
        return info_hostnom();
    }
    if (var == "apssid")
    {
        return info_apssid();
    }
    if (var == "apip")
    {
        return info_apip();
    }
    if (var == "apmac")
    {
        return info_apmac();
    }
    if (var == "memsmeter")
    {
        return info_memsmeter();
    }
