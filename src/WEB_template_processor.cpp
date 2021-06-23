// #include "NOTARDUINO.h"
#include <Arduino.h>

#include <Tinker_DEBUG.h>
#include <Tinker_WiFi.h>

#include "HTML_Loadup.h"
#include "OTA_Externs.h"
#include "DeviceInfo.h"

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

#else   // original processor

#if defined(SiniLink)
extern String SiniLink_TurnOn;
extern String SiniLink_TurnOff;
#endif

String processor(const String &var) // Change placeholders on webpage
{

    if (var == "SCRIPTS")
    {
        return Scripts_html;
    }

    if (var == "PageHeader")
    {
        DEBUG_LineOut("Page Header");
        return Page_Header;
    }

    if (var == "WT_PageTitle")
    {
        for (int ButtonCTR = 0; ButtonCTR < NumberofButtons; ButtonCTR++)
        {
            if (!strcmp(Button[ButtonCTR].ButtonAddress, CurrentPage))
                return Button[ButtonCTR].ButtonLabel;
        }
        return "WTF?";
    }

    /**********************************************************************/
    if (var == "Buttons")
    {

        String TheHTML = "";
        char TheButton[1024];
        String ButtonClass;

        for (int ButtonCTR = 0; ButtonCTR < NumberofButtons; ButtonCTR++)
        {
            if (!strcmp(Button[ButtonCTR].ButtonAddress, CurrentPage))
            {
                ButtonClass = "ButtonHere";
            }
            else
            {
                ButtonClass = "ButtonClickable";
            }

            sprintf(TheButton,
                    "<div class = \"button %s\"> <button%d onclick=\"location.href='%s'\">%s</button> </div>",
                    ButtonClass.c_str(), ButtonCTR, Button[ButtonCTR].ButtonAddress, Button[ButtonCTR].ButtonLabel);
            TheHTML += TheButton;
        }
        return TheHTML;
    }
    /**********************************************************************/

#if defined(SiniLink)
    if (var == "SiniLink_TurnOn")
        return SiniLink_TurnOn;
    if (var == "SiniLink_TurnOff")
        return SiniLink_TurnOff;
#endif

    if (var == "PageBody") // The placeholder
    {
        DEBUG_LineOut("Page Body");
        if (!strcmp(CurrentPage, "/test"))
        {
            return TestPagePart;
        }
        if (!strcmp(CurrentPage, "/home"))
        {
            return Content_HomePage;
        }
        if (!strcmp(CurrentPage, "/management"))
        {
            return Content_Management;
        }

        return "<H1>WTF?</H1>";
    }
    if (var == "tPageContent") // The placeholder
    {
        return TestPagePart;
    }
    if (var == "hPageContent") // The placeholder
    {
        return HomePagePart;
    }

    if (var == "PageFooter") // The placeholder
    {
        DEBUG_LineOut("Page Footer");
        return Page_Footer;
    }
    // The Footer Section
    {
        if (var == "WT_ReBootMSG")
        {
            return getRebootMessage0();
        }
        if (var == "WT_DeviceID")
        {
            return DeviceID();
        }
        if (var == "WT_Processor")
        {
            return getProcTag();
        }
        if (var == "WT_type")
        {
            return getDeviceType();
        }
        if (var == "WT_ReBootReason")
        {
            return getRebootMessage1();
        }
    }
    /////////////////////////////////////////////////////////////

    // if (var == "TemplateCount") // The placeholder
    // {
    //     String Fugga = "TemplateCount = " + String(TemplateCount);

    //     // DEBUG_LineOut(Fugga);
    //     return Fugga;
    // }

    /* I2C pin numbers */
    if (var == "WT_SDASCL")
    {
        return getSDASCL();
    }
    if (var == "WT_I2C")
    {
        return getI2Cscan();
    }

    if (var == "WT_IPMAC")
    {
        return IP_MAC;
    }
    if (var == "WT_dark")
    {
        return getDarkMode();
    }
    if (var == "WT_color")
    {
        return htmlcolor;
    }
    if (var == "WT_hover")
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

#endif   // original processor
