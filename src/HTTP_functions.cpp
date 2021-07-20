#include <Tinker_DEBUG.h>

#include <Tinker_HTTP.h>

#include <OTA_Externs.h>

#if defined(ESP8266)
#include <flash_hal.h>
// #define MYFS LITTLEFS
#include <LittleFS.h>
#elif defined(ESP32)
#include "Update.h"
// #define MYFS LITTLEFS
#include <LittleFS.h>
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
bool Refresh_Needed = false;
// Need to add a placeholder in the <head> section
// And a handler in WEB_template_processor.cpp to add in
//      <meta http-equiv="refresh" content="5; URL='/'" />
// (and possibly clear this variable back to false)
/**********************************************************************/

int PageNumber;
int ditditdit;

boolean setup_HTTP()
{
    DEBUG_Init("WebServer");

    /* root page */
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_SectionTitle("HTTP Action");
                  request->redirect("/home");
                  sprintf(DEBUGtxt, "Page: %s", "/");
                  DEBUG_LineOut(DEBUGtxt);
              });
    DEBUG_LineOut("Page: / set up");

    /* home page */
    server.on("/home", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_SectionTitle("HTTP Action");
                  strcpy(CurrentPage, "/home");
                  request->send_P(200, "text/html", Skeleton, processor);
                  DEBUG_LineOut("home Loaded");
              });
    DEBUG_LineOut("Page: /home set up");

    /* management page */
    server.on("/management", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_SectionTitle("HTTP Action");
                  strcpy(CurrentPage, "/management");
                  request->send_P(200, "text/html", Skeleton, processor);
                  DEBUG_LineOut("management Loaded");
              });
    DEBUG_LineOut("Page: /management set up");

    /* complete page */
    server.on("/complete", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  Refresh_Needed = true;
                  DEBUG_SectionTitle("HTTP Action");
                  strcpy(CurrentPage, "/complete");
                  //   request->send_P(200, "text/html", done_html, processor); ////////////
                  request->send_P(200, "text/html", Skeleton, processor); ////////////
                  DEBUG_LineOut("complete Loaded");
              });
    DEBUG_LineOut("Page: /complete set up");

    /* failedOTA page */
    server.on("/failedOTA", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  DEBUG_SectionTitle("HTTP Action");
                  strcpy(CurrentPage, "/failedOTA");
                  request->send_P(200, "text/html", Skeleton, processor);
                  DEBUG_LineOut("failedOTA Loaded");
              });
    DEBUG_LineOut("Page: /failedOTA set up");

    /* reboot page */
    server.on("/reboot", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  Refresh_Needed = true;
                  DEBUG_SectionTitle("HTTP Action");
                  strcpy(CurrentPage, "/reboot");
                  //   request->send_P(200, "text/html", reboot_html, processor);
                  request->send_P(200, "text/html", Skeleton, processor); ////////////
                  restartRequired = true;
              });
    DEBUG_LineOut("Page: /reboot set up");

    /* Load the CSS */
    server.on("/TheCSS.css", HTTP_GET, [](AsyncWebServerRequest *request)
              {
                  request->send_P(200, "text/html", TheCSS, processor);
                  DEBUG_LineOut("TheCSS Loaded");
              });
    DEBUG_LineOut("Page: /TheCSS.css set up");

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
    DEBUG_LineOut("Page: /darkmode set up");

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
                if (Update.write(data, len) != len) // This happens if bin file is too big
                {                                   // Why does this carry on trying???
                    ditditdit = DEBUG_ProgressBar(ditditdit, '!');
                    return request->send(400, "text/plain", "OTA could not begin"); // Yet this doesn't seem to happen...
                }
                // else // Happens for each good chunk.
                // {
                //     ditditdit = DEBUG_ProgressBar(ditditdit, ',');
                // }
            }

            if (final) // if the final flag is set then this is the last frame of data
            {          // Happens once upon successful upload
                // DEBUG_ProgressBar2(ditditdit);
                // DEBUG_ProgressBar2(ditditdit);
                if (!Update.end(true))
                { //true to set the size to the current progress
                    DEBUG_Trouble("error:  Could not end OTA");
                    Update.printError(Serial);
                    return request->send(400, "text/plain", "Could not end OTA");
                }
                // else
                // {
                //     DEBUG_Success("complete!");
                // }
            }
            else
            {
                ditditdit = DEBUG_ProgressBar(ditditdit, '.');
                // DEBUG_LineOut("BOTH complete!");
                return;
            }
            DEBUG_ProgressBar2(ditditdit);
            DEBUG_Success("complete!");
        });
    sprintf(DEBUGtxt, "Page: %s", "/management (POST)");
    DEBUG_LineOut(DEBUGtxt);

    /* error 404 */
    server.onNotFound([](AsyncWebServerRequest *request)
                      {
                          DEBUG_SectionTitle("HTTP Action");
                          request->send(404);
                          //  It'd be kinda cool to be able to print out the requested address here...
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