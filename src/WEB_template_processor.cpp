// #include "NOTARDUINO.h"
#include <Arduino.h>

#include <Tinker_DEBUG.h>
#include <Tinker_WiFi.h>

#include "HTML_Loadup.h"
#include "OTA_Externs.h"
// #include "DeviceInfo.h"
String ip3string(IPAddress ip);
String info_memsketch();

#include "Tinker_HTTP.h"

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

#else // original processor

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

    if (var == "WT_IPMAC")
    {
        return IP_MAC;
    }
    if (var == "WT_IP")
    {
        return ip3string(WiFi.localIP());
    }
    if (var == "WT_MAC")
    {
        return WiFi.macAddress();
    }
    if (var == "memsketch")
    {
        return info_memsketch();
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

    return String();
}

#endif // original processor

/////////////////////////////////////////////////////////////////////////////////////////
extern int darkState;

String getDarkMode()
{
    if (darkState == false)
    {
        return "body { background-color: white; color: black; }";
    }
    else
    {
        return "body { background-color: black; color: white; }";
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
extern int deviceREBOOTED;

String getRebootMessage0()
{
    if (deviceREBOOTED == false)
    {
        return "";
    }
    else
    {
        return "Device Rebooted";
    }
}

String getRebootMessage1()
{
    String erroring = "";
    // if (deviceREBOOTED == false)
    // {
    //     erroring += "";
    // }
    // else
    if (deviceREBOOTED)
    {
        deviceREBOOTED = false;
#if defined(ESP8266)
        String RebootReason =
            ESP.getResetReason().c_str();
#elif defined(ESP32)
        String RebootReason =
            return_reset_reason(rtc_get_reset_reason(0));
        erroring += RebootReason;
        erroring += "/";
        RebootReason =
            return_reset_reason(rtc_get_reset_reason(1));
#endif
        erroring += RebootReason;
    }
    return erroring;
}

String DeviceID()
{
#if defined(DeviceName)
    String id = STR(DeviceName);
#else
    String id = host;
#endif
    return id;
}

String getProcTag()
{
    String PROing = "";
#if defined(ESP8266)
    PROing += "ESP8266";
#elif defined(ESP32)
    PROing += "ESP32";
#endif
    PROing += " (";
    PROing += String(ESP.getFlashChipSize() / 1024 / 1024, DEC);
    PROing += "MB )";
    return PROing;
}

String getDeviceType()
{
#if defined(DeviceType)
    String id = STR(DeviceType);
#else
    String id = host;
#endif
    return id;
}
/////////////////////////////////////////////////////////////////////////////////////////
String ip3string(IPAddress ip)
{
    String ret = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    return ret;
}

String info_memsketch()
{
    int Size = ESP.getSketchSize();
    int Free = ESP.getFreeSketchSpace();
    int Total = Size + Free;
    
Serial.printf("Sketch Size: %d\n", Size);
Serial.printf(" Free Space: %d\n", Free);

Serial.printf("Total Space: %d\n", Total);

Serial.println( (Size / (Size + Free)) );

    String memsketch =
        ((String)(ESP.getSketchSize())) +
        " / " +
        ((String)(ESP.getSketchSize() + ESP.getFreeSketchSpace())) +
        " Used / Total " +
        (String)(ESP.getSketchSize() / ((ESP.getSketchSize() + ESP.getFreeSketchSpace()))) +
        "%%";
    return memsketch;
}
