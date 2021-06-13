// #include "NOTARDUINO.h"
#include "Tinker_DEBUG.h"
// #include "OTA_async_AP.h"
#include "Tinker_WiFi.h"

/////////////////////////////////////////////////////////
// #if defined(ESP8266)
// #include "NOTARDUINO.h"
// #elif defined(ESP32)
// #include <rom/rtc.h>
// String return_reset_reason(uint8_t reason);
// #endif
/////////////////////////////////////////////////////////
// #include "info_placement.h"

#include "HTML_Loadup.h"

// #include "OTA_Externs.h"

// #include "Template_Maps.h"

/* Convert a #defined value to a string */
#define ST(A) #A
#define STR(A) ST(A)
////////////////////
// This is probably more complex than it really needs to be...
#define ST2a(A, B) #A
#define ST2b(A, B) #B
#define STR2a(A) ST2a(A)
#define STR2b(B) ST2b(B)
////////////////////

extern int deviceREBOOTED;

#if defined(NEWprocessor)
// extern TemplateMap TemplateMaps[];
extern int TemplateCount;

// #include "_POOP.h"

String processor(const String &var) // Change placeholders on webpage
{
Serial.printf("dang - TemplateMap #9/%i: ", TemplateCount);
Serial.print(TemplateMaps[9].PlaceHolder);
Serial.print(" --- ");
Serial.print(TemplateMaps[9].DebugMSG);
Serial.print(" --- ");
Serial.println(TemplateMaps[9].p_Content);

    for (int ctr = 0; ctr < TemplateCount; ctr++)
        if (var == TemplateMaps[ctr].PlaceHolder)
        {
            if (strlen(TemplateMaps[ctr].DebugMSG) > 0)
                DEBUG_LineOut(TemplateMaps[ctr].DebugMSG);
            return TemplateMaps[ctr].p_Content;
        }
    return String("Woopsie!!!");
}

#else

// #include "_DeviceInfo.h"
String processor(const String &var) // Change placeholders on webpage
{
    if (var == "SDASCLplaceholder")
    {
        return getSDASCL();
    }
    if (var == "I2Cplaceholder")
    {
        return getI2Cscan();
    }

    /////////////////////////////////////////////////////////////
    // How to add a block to a web page...
    //  Based on a #define conditional (look up a few lines...)
    //  TestPage was defined as a number in platformio.ini
    /////////////////////////////////////////////////////////////

    if (var == "tPageContent") // The placeholder
    {
        return TestPagePart;
    }
    /////////////////////////////////////////////////////////////
    if (var == "hPageContent") // The placeholder
    {
        return HomePagePart;
    }
    /////////////////////////////////////////////////////////////
    if (var == "PageHeader") // The placeholder
    {
        DEBUG_LineOut("Page Header");
        return Page_Header;
    }
    if (var == "PageBody") // The placeholder
    {
        DEBUG_LineOut("Page Body");
        return Page_Body;
    }
    if (var == "PageFooter") // The placeholder
    {
        DEBUG_LineOut("Page Footer");
        return Page_Footer;
    }
    /////////////////////////////////////////////////////////////
    if (var == "TemplateCount") // The placeholder
    {
        String Fugga = "TemplateCount = " + String(TemplateCount);

        // DEBUG_LineOut(Fugga);
        return Fugga;
    }

    if (var == "SCRIPTS")
    {
        return Scripts_html;
    }

    if (var == "IPMAC")
    {
        return IP_MAC;
    }

    if (var == "title")
    {
        return getDeviceName();
    }
    if (var == "dark")
    {
        return getDarkMode();
    }
    if (var == "type")
    {
        return getDeviceType();
    }
    if (var == "color")
    {
        return htmlcolor;
    }
    if (var == "hover")
    {
        return htmlhover;
    }
    if (var == "ipplaceholder")
    {
        return ip3string(WiFi.localIP());
    }
    if (var == "macplaceholder")
    {
        return WiFi.macAddress();
    }
    if (var == "IDplaceholder")
    {
        return DeviceID();
    }
    if (var == "processorplaceholder")
    {
        return getProcTag();
    }
    if (var == "errorplaceholder")
    {
        return getRebootMessage();
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
    return String();
}

#endif

