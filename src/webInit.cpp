#include <Tinker_DEBUG.h>
// #include "Tinker_WiFi.h"
// #include "OTA_async_AP.h"
#if defined(ESP8266)
    // #include "ESP8266WiFi.h"
    // #include "ESPAsyncTCP.h"
    #include <flash_hal.h>
#elif defined(ESP32)
    // #include "WiFi.h"
    // #include "AsyncTCP.h"
    // #include "Update.h"
    // #include "esp_int_wdt.h"
    // #include "esp_task_wdt.h"
#endif
/////////////////////////////////////////////////////
#include <ESPAsyncWebServer.h>

#include <FS.h> // SPIFFS is declared
// #include "LittleFS.h" // LittleFS is declared
////////////////////////////////////////////////////
String processor(const String &var);
// #if defined(ESP8266)
// #include "NOTARDUINO.h"
// #elif defined(ESP32)
// #include <rom/rtc.h>
// String return_reset_reason(uint8_t reason);
// #endif

AsyncWebServer server(80);

const char *PARAM_dark_1 = "state";

extern int darkState;

extern bool restartRequired;

/* include the webpages (done in HTML) */
const char home_html[] PROGMEM = 
#include "HTML/homepage.htm"   // Homepage HTML
;
const char management_html[] PROGMEM = 
#include "HTML/Management.htm" // UPDATEpage HTML
;
const char failOTA_html[] PROGMEM = 
#include "HTML/failedOTA.htm"  // HTML to be created
;
const char reboot_html[] PROGMEM = 
#include "HTML/reboot.htm"     // HTML to be created
;
const char done_html[] PROGMEM = 
#include "HTML/Finished.htm"   //  HTML
;
const char *test_html PROGMEM = 
#include "HTML/testpage.htm"   //  HTML
;
const char TheCSS[] PROGMEM = 
#include "HTML/css.css"
;

struct PageMapping
{
    char Address[16];
    const char *p_Content;
};

PageMapping PageContent[] =
    {
        {"/TheCSS.css", &TheCSS[0]},
        {"/home", &home_html[0]},
        {"/management", &management_html[0]},
        {"/complete", &done_html[0]},
        {"/failedOTA", &failOTA_html[0]},
        // {"/reboot", &reboot_html[0]},
        {"/test", &test_html[0]},
};

extern char DEBUGtxt[48];

int PageNumber;

boolean webInit()
{
    DEBUG_Init("WebServer");

#define InitializePage(PageNumber)                                                            \
    server.on(PageContent[PageNumber].Address, HTTP_GET, [](AsyncWebServerRequest *request) { \
        request->send_P(200, "text/html", PageContent[PageNumber].p_Content, processor);      \
        sprintf(DEBUGtxt, "Page: %s accessed", PageContent[PageNumber].Address);              \
        DEBUG_LineOut(DEBUGtxt);                                                              \
    });                                                                                       \
    sprintf(DEBUGtxt, "Page: [%d] %s set up", PageNumber, PageContent[PageNumber].Address);   \
    DEBUG_LineOut(DEBUGtxt);

    InitializePage(0);
    InitializePage(1);
    InitializePage(2);
    InitializePage(3);
    InitializePage(4);
    InitializePage(5);
    // InitializePage(6);

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->redirect("/home");
                  sprintf(DEBUGtxt, "Page: %s", "/");
                  DEBUG_LineOut(DEBUGtxt);
              });
    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "text/html", reboot_html, processor);
                  restartRequired = true;
              });
    server.on("/darkmode", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  String inputMessage1;
                  if (request->hasParam(PARAM_dark_1))
                  {
                      inputMessage1 = request->getParam(PARAM_dark_1)->value();
                      if (inputMessage1 == "1")
                      {
                          darkState = !darkState;
                      }
                  }
                  request->send(200, "text/plain", "OK");

                  sprintf(DEBUGtxt, "Page: %s", "/darkmode");
                  DEBUG_LineOut(DEBUGtxt);
              });

    server.on(
        "/management", HTTP_POST, [&](AsyncWebServerRequest *request)
        {
            // the request handler is triggered after the upload has finished...
            // create the response, add header, and send response
            AsyncWebServerResponse *response = request->beginResponse((Update.hasError()) ? 500 : 200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
            response->addHeader("Connection", "close");
            response->addHeader("Access-Control-Allow-Origin", "*");
            request->send(response);
            restartRequired = true;
            sprintf(DEBUGtxt, "Page: %s", "/management 2 happened");
            DEBUG_LineOut(DEBUGtxt);
        },
        [&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
        {
            //Upload handler chunks in data
            // sprintf(DEBUGtxt, "Page: %s", "/management 2 happened");
            // DEBUG_LineOut(DEBUGtxt);
            if (!index)
            {

#if defined(ESP8266)
    DEBUG_LineOut("UPDATING: ESP8266");
                int cmd = (filename == "filesystem") ? U_FS : U_FLASH;
                Update.runAsync(true);
                size_t fsSize = ((size_t)&_FS_end - (size_t)&_FS_start);
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if (!Update.begin((cmd == U_FS) ? fsSize : maxSketchSpace, cmd))
                { // Start with max available size
#elif defined(ESP32)
    DEBUG_LineOut("UPDATING: ESP32");
                int cmd = (filename == "filesystem") ? U_SPIFFS : U_FLASH;
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd))
                { // Start with max available size
#endif
    DEBUG_LineOut("UPDATING:  errored?");
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "OTA could not begin");
                }
    DEBUG_LineOut("UPDATING:  uploading");
            }

            // Write chunked data to the free sketch space
            if (len)
            {
    // DEBUG_LineOut("BOTH good");
    Serial.print("~");
                if (Update.write(data, len) != len)
                {
    DEBUG_LineOut("UPDATING:  bad");
                    return request->send(400, "text/plain", "OTA could not begin");
                }
            }

            if (final)
            { // if the final flag is set then this is the last frame of data
    Serial.println();
    DEBUG_LineOut("UPDATING:  complete!");
                if (!Update.end(true))
                { //true to set the size to the current progress
    DEBUG_LineOut("UPDATING:  Poop!");
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "Could not end OTA");
                }
            }
            else
            {
    // DEBUG_LineOut("BOTH complete!");
                return;
            }
        });
    sprintf(DEBUGtxt, "Page: %s", "/management 2");
    DEBUG_LineOut(DEBUGtxt);

    server.onNotFound([](AsyncWebServerRequest *request)
                      { request->send(404); });
    sprintf(DEBUGtxt, "Page: %s", "404");
    DEBUG_LineOut(DEBUGtxt);

    server.begin();
    ////////////////////////////////////////////////////////////
    return (true);
    ////////////////////////////////////////////////////////////
}