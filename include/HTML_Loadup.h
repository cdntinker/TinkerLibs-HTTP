// #include "NOTARDUINO.h"
#include <Arduino.h>

#include "HTML/Scripts.htm"

#include "HTML/Parts/Page_Header.htm"
#include "HTML/Parts/Page_Body.htm"
#include "HTML/Parts/Page_Footer.htm"

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
Content_Oops;
#endif

