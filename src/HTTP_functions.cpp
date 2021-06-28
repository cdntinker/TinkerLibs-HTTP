#include <Tinker_DEBUG.h>

#include <Tinker_HTTP.h>

#include <OTA_Externs.h>

#if defined(ESP8266)
#include <flash_hal.h>
#elif defined(ESP32)
#include "Update.h"
#endif

////////////////////////////////////////////////////
#include <ESPAsyncWebServer.h>

#include <FS.h> // SPIFFS is declared
// #include "LittleFS.h" // LittleFS is declared
////////////////////////////////////////////////////

#if defined(SiniLink)
#include <Tinker_SiniLink.h>
#endif

AsyncWebServer server(80);

const char *PARAM_dark_1 = "state";

extern int darkState;

extern bool restartRequired;

/* ********************************************************
 * Fill in the web page variables & structures
 * *******************************************************/
#include "The_Pages.h"

#include "HTML/Parts/NEW_HTML_SKELETON.htm"

extern char DEBUGtxt[48];

/**********************************************************************/
char CurrentPage[32];
/**********************************************************************/

int PageNumber;
int ditditdit;

boolean setup_HTTP()
{
    DEBUG_Init("WebServer");

    /* poop page */
    server.on("/poop", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_LineOut("poop Loaded");
                  request->send_P(200, "text/html", "%PageHeader%\n<H1>W T F ?</H1>", processor);
              });

    /* test home page */
    server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_LineOut("home Loaded");
                  request->send_P(200, "text/html", Skeleton, processor);
              });

    /* test management page */
    server.on("/management", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_LineOut("management Loaded");
                  request->send_P(200, "text/html", Skeleton, processor);
              });

    /*
    {   // Multi-page macro setup
// ********************************************************
// This #define builds the page request handlers for
// pages defined in the PageContent[] array of structures.
// 
// This exists because the process is inlined.
// This kinda borks the whole call by reference thing.
// *******************************************************
#define InitializePage(PageNumber)                                                            \
    server.on(PageContent[PageNumber].Address, HTTP_GET, [](AsyncWebServerRequest *request) { \
        DEBUG_SectionTitle("HTTP Action");                                                    \
        strcpy(CurrentPage, PageContent[PageNumber].Address);                                 \
        request->send_P(200, "text/html", PageContent[PageNumber].p_Content, processor);      \
        sprintf(DEBUGtxt, "Page: %s accessed", PageContent[PageNumber].Address);              \
        DEBUG_LineOut(DEBUGtxt);                                                              \
    });                                                                                       \
    sprintf(DEBUGtxt, "Page: [%d] %s set up", PageNumber, PageContent[PageNumber].Address);   \
    DEBUG_LineOut(DEBUGtxt);

        // for(int PageCount = 0; PageCount <= 5; PageCount++)
        //     InitializePage(PageCount);

        InitializePage(0);
        InitializePage(1);
        InitializePage(2);
        InitializePage(3);
        // InitializePage(4);
#if defined(TestPage)
        InitializePage(4);
#endif
    }
    */

    /* root page */
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_SectionTitle("HTTP Action");
                  request->redirect("/home");
                  sprintf(DEBUGtxt, "Page: %s", "/");
                  DEBUG_LineOut(DEBUGtxt);
              });

    /* Load the CSS */
    server.on("/TheCSS.css", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "text/html", TheCSS, processor);
                  DEBUG_LineOut("TheCSS Loaded");
              });

    /* reboot page */
    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_SectionTitle("HTTP Action");
                  request->send_P(200, "text/html", reboot_html, processor);
                  restartRequired = true;
              });

    /* darkmode page */
    server.on("/darkmode", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_SectionTitle("HTTP Action");
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

    /* management (POST) page */
    server.on(
        "/management", HTTP_POST, [&](AsyncWebServerRequest *request)
        {
            ditditdit = 0;
            // the request handler is triggered after the upload has finished...
            // create the response, add header, and send response
            AsyncWebServerResponse *response = request->beginResponse((Update.hasError()) ? 500 : 200, "text/plain", (Update.hasError()) ? "FAIL" : "OK");
            response->addHeader("Connection", "close");
            response->addHeader("Access-Control-Allow-Origin", "*");
            request->send(response);
            restartRequired = true;
        },
        [&](AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final)
        {
            //Upload handler chunks in data
            if (!index)
            {

                DEBUG_SectionTitle("UPDATING");
#if defined(ESP8266)
                DEBUG_LineOut("ESP8266");
                int cmd = (filename == "filesystem") ? U_FS : U_FLASH;
                Update.runAsync(true);
                size_t fsSize = ((size_t)&_FS_end - (size_t)&_FS_start);
                uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
                if (!Update.begin((cmd == U_FS) ? fsSize : maxSketchSpace, cmd))
                { // Start with max available size
                    DEBUG_Trouble("error:  OTA could not begin");
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "OTA could not begin");
                }
#elif defined(ESP32)
                DEBUG_LineOut("ESP32");
                int cmd = (filename == "filesystem") ? U_SPIFFS : U_FLASH;
                if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd))
                { // Start with max available size
                    DEBUG_Trouble("error:  OTA could not begin");
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "OTA could not begin");
                }
#endif // ESP32

                DEBUG_LineOut("uploading");
            }

            // Write chunked data to the free sketch space
            if (len)
            {
                // DEBUG_LineOut("BOTH good");
                if (Update.write(data, len) != len)
                {
                    // ditditdit = DEBUG_ProgressBar(ditditdit, '!');      // Why does this carry on???
                    return request->send(400, "text/plain", "OTA could not begin");
                }
                else
                    ditditdit = DEBUG_ProgressBar(ditditdit, '.');
            }

            if (final)
            { // if the final flag is set then this is the last frame of data
                DEBUG_ProgressBar2(ditditdit);
                DEBUG_Success("complete!");
                if (!Update.end(true))
                { //true to set the size to the current progress
                    DEBUG_Trouble("error:  Could not end OTA");
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
    sprintf(DEBUGtxt, "Page: %s", "/management (POST)");
    DEBUG_LineOut(DEBUGtxt);

    /* error 404 */
    server.onNotFound([](AsyncWebServerRequest *request)
                      {
                          DEBUG_SectionTitle("HTTP Action");
                          request->send(404);
                          sprintf(DEBUGtxt, "Page: %s", "404");
                          DEBUG_LineOut(DEBUGtxt);
                      });

#if defined(SiniLink)
    /* SiniLink pages */
    server.on("/SiniLink_ON", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  SiniLink_Relay(HIGH);
                  request->redirect("/home");
              });
    server.on("/SiniLink_toggle", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  SiniLink_Toggle();
                  request->redirect("/home");
              });
    server.on("/SiniLink_OFF", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  SiniLink_Relay(LOW);
                  request->redirect("/home");
              });
#endif

    server.begin();
    ////////////////////////////////////////////////////////////
    return (true);
    ////////////////////////////////////////////////////////////
}