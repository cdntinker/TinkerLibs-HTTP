// #include "NOTARDUINO.h"
#include <Arduino.h>

#include "HTML/Scripts.htm"

#include "HTML/Parts/Page_Header.htm"
#include "HTML/Parts/Page_Body.htm"
#include "HTML/Parts/Page_Footer.htm"

#include "HTML/Parts/Content_IP_MAC.htm"
#include "HTML/Parts/Content_Firmware_Update.htm"
#include "HTML/Parts/Content_Reboot.htm"

/* These are defined in the parent project */
extern const char* Content_I2C;
extern const char* Content_Poem;
extern const char* Content_SiniLink;
extern const char* Content_Sonoff;

// #if defined(TestPage)
#if (defined(TestPage) && (TestPage == 0)) || (defined(HomePage) && (HomePage == 0))
#include "HTML/Parts/Content_Verkz.htm"
#endif
#if (defined(TestPage) && (TestPage == 3)) || (defined(HomePage) && (HomePage == 3))
#include "HTML/Parts/Content_DeviceInfo.htm"
#endif
// #endif
// #include "HTML/Parts/Content_WTF.htm"
// #include "HTML/Parts/Content_Oops.htm"

/* This kinda sucks...  It's sooooo limiting... */

#if defined(TestPage)
const char *TestPagePart =
#if TestPage == 0
Content_Verkz;
#elif TestPage == 1
Content_Poem;
#elif TestPage == 2
Content_SiniLink;
#elif TestPage == 3
Content_DeviceInfo;
#elif TestPage == 4
Content_I2C;
#elif TestPage == 5
Content_Sonoff;
#else
Content_WTF;
#endif
#else
// Content_Oops;
const char *TestPagePart = "";
#endif

#if defined(HomePage)
const char *HomePagePart =
#if HomePage == 0
Content_Verkz;
#elif HomePage == 1
Content_Poem;
#elif HomePage == 2
Content_SiniLink;
#elif HomePage == 3
Content_DeviceInfo;
#elif HomePage == 4
Content_I2C;
#elif HomePage == 5
Content_Sonoff;
#else
Content_WTF;
#endif
#else
// Content_Oops;
const char *HomePagePart = "";
#endif

/**********************************************************************/

#include "HTML/Parts/Body_Management.htm"
#include "HTML/Parts/Body_HomePage.htm"

/**********************************************************************/
struct ButtonMap
{

    char ButtonAddress[32];
    char ButtonLabel[32];
    String p_Content;
};

ButtonMap Button[] =
    {
#if defined(TestPage)
        {"/test", "TestPage"},
#endif
        {"/home", "Home"},
        {"/management", "Management"},
};
int NumberofButtons = sizeof(Button) / sizeof(Button[0]);
extern char CurrentPage[32];

/**********************************************************************/