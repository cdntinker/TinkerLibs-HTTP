#include "NOTARDUINO.h"

const char *Page_Header PROGMEM =
#include "HTML/Parts/Page_Header.htm"

const char *Page_Body PROGMEM =
#include "HTML/Parts/Page_Body.htm"

const char *Page_Footer PROGMEM =
#include "HTML/Parts/Page_Footer.htm"

const char *Scripts_html PROGMEM =
#include "HTML/Scripts.htm"

const char *IP_MAC PROGMEM =
#include "HTML/Parts/Content_IP_MAC.htm"

const char *TestPagePart PROGMEM =
#if defined(TestPage)
#if TestPage == 0
#include "HTML/Parts/Content_Verkz.htm"
#elif TestPage == 1
#include "HTML/Parts/Content_Poem.htm"
#elif TestPage == 2
#include "HTML/Parts/Content_SiniLink.htm"
#elif TestPage == 3
#include "HTML/Parts/Content_DeviceInfo.htm"
#elif TestPage == 4
#include "HTML/Parts/Content_I2C.htm"
#elif TestPage == 5
#include "HTML/Parts/Content_Sonoff.htm"
#else
#include "HTML/Parts/Content_WTF.htm"
#endif
#else
#include "HTML/Parts/Content_Oops.htm"
#endif

const char *HomePagePart PROGMEM =
#if defined(HomePage)
#if HomePage == 0
#include "HTML/Parts/Content_Verkz.htm"
#elif HomePage == 2
#include "HTML/Parts/Content_SiniLink.htm"
#elif HomePage == 4
#include "HTML/Parts/Content_I2C.htm"
#elif HomePage == 5
#include "HTML/Parts/Content_Sonoff.htm"
#else
#include "HTML/Parts/Content_WTF.htm"
#endif
#else
#if defined(I2Cenable)
#include "HTML/Parts/Content_I2C.htm"
#else
    "";
#endif
;
#endif
