// #include "NOTARDUINO.h"
#include <Arduino.h>

#include <Tinker_WiFi.h>

#include "OTA_Externs.h"

#include "Template_Maps.h"

#include "_DeviceInfo.h"

#if defined(ESP8266)
#elif defined(ESP32)
#include <rom/rtc.h>
#endif

TemplateMap TemplateMaps[64];
int TemplateCount;

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

String getSDASCL()
{
#if defined(I2Cenable)
    String Replacement = "";
    Replacement += STR2a(I2Cenable);
    Replacement += ",";
    Replacement += STR2b(I2Cenable);
#else
    String Replacement = "Nope";
#endif
    return Replacement;
}

String getI2Cscan()
{
#if defined(I2Cenable)
    extern String FoundI2Cdevices;
    String I2Cing = "";
    I2Cing += FoundI2Cdevices;
#else
    String I2Cing = "Nope";
#endif
    return I2Cing;
}

String getDeviceName()
{
#if defined(DeviceName)
    String id = STR(DeviceName);
#else
    String id = host;
#endif
    return id;
}

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

String getDeviceType()
{
#if defined(DeviceType)
    String id = STR(DeviceType);
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

extern int deviceREBOOTED;

/////////////////////////////////////////////////////////////////////////////////////////
String getRebootMessage0()
{
    Serial.print("Mudda ");
    Serial.print(deviceREBOOTED);

    if (deviceREBOOTED == false)
    {
        Serial.println("NOPE");
        return "foo";
    }
    else
    {
        Serial.println("YUP");
        // deviceREBOOTED = false;
        return "Device Rebooted";
    }
}

String getRebootMessage1()
{
    String erroring = "";
    if (deviceREBOOTED == false)
    {
        erroring += "";
    }
    else
    {
        deviceREBOOTED = false;
        erroring += "(";
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
        erroring += ")";
    }
    return erroring;
}
/////////////////////////////////////////////////////////////////////////////////////////

String getDeviceID()
{
#if defined(DeviceName)
    String id = STR(DeviceName);
#else
    String id = host;
#endif
    return id;
}

String info_uptime()
{
    String uptimeing = " " + ((String)(millis() / 1000 / 60)) + " Mins " + ((String)((millis() / 1000) % 60)) + " Secs";
    return uptimeing;
}

String info_chipid()
{
#ifdef ESP8266
    String chipid = (String(ESP.getChipId(), HEX));
#elif defined ESP32
    uint32_t chipId = 0;
    for (int i = 0; i < 17; i = i + 8)
    {
        chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
    }
    String chipid = ((String)(chipId));
#endif
    return chipid;
}

String info_idesize()
{
    String idesize = ((String)ESP.getFlashChipSize());
    return idesize;
}

String info_flashsize()
{
#ifdef ESP8266
    String flashsize = ((String)ESP.getFlashChipRealSize());
#elif defined ESP32
    String flashsize = ((String)ESP.getPsramSize());
#endif
    return flashsize;
}

String info_sdkver()
{
#ifdef ESP32
    String sdkver = ((String)esp_get_idf_version());
//(String)system_get_sdk_version()); // deprecated
#else
    String sdkver = ((String)system_get_sdk_version());
#endif
    return sdkver;
}

String info_cpufreq()
{
    String cpufreq = ((String)ESP.getCpuFreqMHz());
    return cpufreq;
}

String info_freeheap()
{
    String freeheap = ((String)ESP.getFreeHeap());
    return freeheap;
}

String info_memsketch()
{
    String memsketch = ((String)(ESP.getSketchSize())) + " / " + ((String)(ESP.getSketchSize() + ESP.getFreeSketchSpace())) + "  Used / Total";
    return memsketch;
}

String info_lastreset()
{
    String lastreset = "";
#if defined(ESP8266)
    String RebootReason =
        ESP.getResetReason().c_str();
#elif defined(ESP32)
    String RebootReason =
        return_reset_reason(rtc_get_reset_reason(0));
    lastreset += RebootReason;
    lastreset += "/";
    RebootReason =
        return_reset_reason(rtc_get_reset_reason(1));
#endif
    lastreset += RebootReason;
    return lastreset;
}

String info_conx()
{
    String conx = (WiFi.isConnected() ? ("yes") : ("no"));
    return conx;
}

extern const char *ssid;

String info_stassid()
{
    String stassid = ((String)ssid);
    return stassid;
}

String info_staip()
{
    String staip = (WiFi.localIP().toString());
    return staip;
}

String info_stamac()
{
    String stamac = (WiFi.macAddress());
    return stamac;
}

String info_stagw()
{
    String stagw = (WiFi.gatewayIP().toString());
    return stagw;
}

String info_stasub()
{
    String stasub = (WiFi.subnetMask().toString());
    return stasub;
}

String info_dnss()
{
    String dnss = (WiFi.dnsIP().toString());
    return dnss;
}

extern const char *host;

String info_hostnom()
{
#ifdef ESP32
    String hostnom = ((String)host);
#else
    String hostnom = ((String)host);
#endif
    return hostnom;
}

extern const char *apssid;

String info_apssid()
{
    String ap_ssid = ((String)apssid);
    return ap_ssid;
}

String info_apip()
{
    String apip = (WiFi.softAPIP().toString());
    return apip;
}

String info_apmac()
{
    String apmac = ((String)WiFi.softAPmacAddress());
    return apmac;
}

String info_memsmeter()
{
    int remsize = (((ESP.getSketchSize() + ESP.getFreeSketchSpace()) / (ESP.getSketchSize())) / 4);
    String memsmeter = ((String)remsize) + "rem";
    return memsmeter;
}

void DeviceInfo()
{
    TemplateMap TemplateMaps[] =
        {

            {"SDASCLplaceholder", "", getSDASCL()},
            {"I2Cplaceholder", "", getI2Cscan()},
            {"tPageContent", "", TestPagePart},
            {"hPageContent", "", HomePagePart},
            {"PageHeader", "Page Header", Page_Header},
            {"PageBody", "Page Body", Page_Body},
            {"PageFooter", "Page Footer", Page_Footer},
            {"SCRIPTS", "", Scripts_html},
            {"IPMAC", "", IP_MAC},
            {"title", "", getDeviceName()},
            {"dark", "", getDarkMode()},
            {"type", "", getDeviceType()},
            {"color", "", htmlcolor},
            {"hover", "", htmlhover},
            {"ipplaceholder", "WiFi WTF?", ip3string(WiFi.localIP())},
            {"macplaceholder", "", WiFi.macAddress()},
            {"IDplaceholder", "", getDeviceID()},
            {"processorplaceholder", "", getProcTag()},
            // {"errorplaceholder", "", getRebootMessage()},
            {"WT_ReBootMessage", "", getRebootMessage0()},
            {"WT_ReBootReason", "", getRebootMessage1()},
            {"uptime", "", info_uptime()},
            {"chipid", "", info_chipid()},
            {"idesize", "", info_idesize()},
            {"flashsize", "", info_flashsize()},
            {"sdkver", "", info_sdkver()},
            {"cpufreq", "", info_cpufreq()},
            {"freeheap", "", info_freeheap()},
            {"memsketch", "", info_memsketch()},
            {"lastreset", "", info_lastreset()},
            {"conx", "", info_conx()},
            {"stassid", "", info_stassid()},
            {"staip", "", info_staip()},
            {"stamac", "", info_stamac()},
            {"stagw", "", info_stagw()},
            {"stasub", "", info_stasub()},
            {"dnss", "", info_dnss()},
            {"hostnom", "", info_hostnom()},
            {"apssid", "", info_apssid()},
            {"apip", "", info_apip()},
            {"apmac", "", info_apmac()},
            {"memsmeter", "", info_memsmeter()},
            {"TemplateCount", "", "Device_TemplateCount()"},
        };

    // TemplateMap TemplateMaps[9] = {"Mudda", "Fugga", "SHIT!"};

    // strcpy (TemplateMaps[9].PlaceHolder, "Mudda");
    // strcpy (TemplateMaps[9].DebugMSG , "Fugga");
    //  TemplateMaps[9].p_Content = "SHIT!";

    TemplateCount = sizeof(TemplateMaps) / sizeof(TemplateMaps[0]);

    // Serial.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");
    // for (int ctr = 0; ctr < TemplateCount; ctr++)
    //     Serial.printf("%s\t-\t%s\t-\t%s\n",
    //                   TemplateMaps[ctr].PlaceHolder,
    //                   TemplateMaps[ctr].DebugMSG,
    //                   TemplateMaps[ctr].p_Content.c_str());
    // Serial.println("-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-");

    Serial.printf("info - TemplateMap #9/%i: ", sizeof(TemplateMaps) / sizeof(TemplateMaps[0]));
    Serial.print(TemplateMaps[9].PlaceHolder);
    Serial.print(" --- ");
    Serial.print(TemplateMaps[9].DebugMSG);
    Serial.print(" --- ");
    Serial.println(TemplateMaps[9].p_Content);
}

void poop()
{
    // strcpy (TemplateMaps[9].PlaceHolder, "This");
    // strcpy (TemplateMaps[9].DebugMSG , "Blows");
    //  TemplateMaps[9].p_Content = "Chunks!";

    Serial.printf("poop - TemplateMap #9/%i: ", sizeof(TemplateMaps) / sizeof(TemplateMaps[0]));
    Serial.print(TemplateMaps[9].PlaceHolder);
    Serial.print(" --- ");
    Serial.print(TemplateMaps[9].DebugMSG);
    Serial.print(" --- ");
    Serial.println(TemplateMaps[9].p_Content);
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

String ip3string(IPAddress ip)
{
    String ret = String(ip[0]) + "." + String(ip[1]) + "." + String(ip[2]) + "." + String(ip[3]);
    return ret;
}
