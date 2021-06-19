// #include "NOTARDUINO.h"
#include <Arduino.h>

// const char *Page_Header PROGMEM =
// #include "HTML/Parts/Page_Header.htm"

#include "HTML/Scripts.htm"

#include "HTML/Parts/Page_Header.htm"
#include "HTML/Parts/Page_Body.htm"
#include "HTML/Parts/Page_Footer.htm"

const char *IP_MAC PROGMEM =
#include "HTML/Parts/Content_IP_MAC.htm"

extern char* Content_I2C;
extern char* Content_Poem;
extern char* Content_SiniLink;
extern char* Content_Sonoff;

#if defined(TestPage)
#if (TestPage == 0) || (HomePage == 0)
#include "HTML/Parts/Content_Verkz.htm"
#endif
#if (TestPage == 3) || (HomePage == 3)
#include "HTML/Parts/Content_DeviceInfo.htm"
#endif
#endif
#include "HTML/Parts/Content_WTF.htm"
#include "HTML/Parts/Content_Oops.htm"

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
Content_Oops;
#endif

// const char *TestPagePart PROGMEM =
// #if defined(TestPage)
// #if TestPage == 0
// #include "HTML/Parts/Content_Verkz.htm"
// #elif TestPage == 1
// #include "HTML/Parts/Content_Poem.htm"
// #elif TestPage == 2
// #include "HTML/Parts/Content_SiniLink.htm"
// #elif TestPage == 3
// #include "HTML/Parts/Content_DeviceInfo.htm"
// #elif TestPage == 4
// #include "HTML/Parts/Content_I2C.htm"
// #elif TestPage == 5
// #include "HTML/Parts/Content_Sonoff.htm"
// #else
// #include "HTML/Parts/Content_WTF.htm"
// #endif
// #else
// #include "HTML/Parts/Content_Oops.htm"
// #endif

#if defined(HomePage)
const char *HomePagePart =
#if HomePage == 0
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
Content_Oops;
#endif

// const char *HomePagePart PROGMEM =
// #if defined(HomePage)
// #if HomePage == 0
// #include "HTML/Parts/Content_Verkz.htm"
// #elif HomePage == 1
// #include "HTML/Parts/Content_Poem.htm"
// #elif HomePage == 2
// #include "HTML/Parts/Content_SiniLink.htm"
// #elif HomePage == 3
// #include "HTML/Parts/Content_DeviceInfo.htm"
// #elif HomePage == 4
// #include "HTML/Parts/Content_I2C.htm"
// #elif HomePage == 5
// #include "HTML/Parts/Content_Sonoff.htm"
// #else
// #include "HTML/Parts/Content_WTF.htm"
// #endif
// #else

// #if defined(I2Cenable)
// #include "HTML/Parts/Content_I2C.htm"
// #else
//     "";
// #endif
// ;
// #endif
