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