/* ****************************************************
 * Fill in the web page variables & structures
 * ***************************************************/

#include <Arduino.h>

/* include the CSS (done in HTML with a RAW Literal wrapper) */
#include "HTML/css.css"

/* include the webpages (done in HTML with a RAW Literal wrapper) */
#include "HTML/homepage.htm"   // Homepage HTML
#include "HTML/Management.htm" // UPDATEpage HTML
#include "HTML/failedOTA.htm"  // HTML
#include "HTML/reboot.htm"     // HTML
#include "HTML/Finished.htm"   //  HTML


// extern const char TheCSS[];
// extern const char home_html[];
// extern const char management_html[];
// extern const char failOTA_html[];
// extern const char reboot_html[];
// extern const char done_html[];

extern const char* test_html;

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