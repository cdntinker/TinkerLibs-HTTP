// #include "NOTARDUINO.h"
#include <Arduino.h>

// const char *Page_Header PROGMEM =
// #include "HTML/Parts/Page_Header.htm"

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
                        switch (TestPage)
{
case 0:
#include "HTML/Parts/Content_Verkz.htm"
    break;
case 1:
#include "HTML/Parts/Content_Poem.htm"
    break;
case 2:
#include "HTML/Parts/Content_SiniLink.htm"
    break;
case 3:
#include "HTML/Parts/Content_DeviceInfo.htm"
    break;
case 4:
#include "HTML/Parts/Content_I2C.htm"
    break;
case 5:
#include "HTML/Parts/Content_Sonoff.htm"
    break;

default:
#include "HTML/Parts/Content_WTF.htm"
    break;
}
#else
#include "HTML/Parts/Content_Oops.htm"
#endif

const char *HomePagePart PROGMEM =
#if defined(HomePage)
    switch (TestPage)
{
case 0:
#include "HTML/Parts/Content_Verkz.htm"
    break;
case 1:
#include "HTML/Parts/Content_Poem.htm"
    break;
case 2:
#include "HTML/Parts/Content_SiniLink.htm"
    break;
case 3:
#include "HTML/Parts/Content_DeviceInfo.htm"
    break;
case 4:
#include "HTML/Parts/Content_I2C.htm"
    break;
case 5:
#include "HTML/Parts/Content_Sonoff.htm"
    break;

default:
#include "HTML/Parts/Content_WTF.htm"
    break;
}
#else
#if defined(I2Cenable)
#include "HTML/Parts/Content_I2C.htm"
#else
                            "";
#endif
    ;
#endif
