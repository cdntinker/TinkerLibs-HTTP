#include <WString.h>

String getSDASCL();
String getI2Cscan();
String getDeviceName();
extern int darkState;
String getDarkMode();
String getDeviceType();
String getProcTag();

extern int deviceREBOOTED;
// String getRebootMessage();
String getRebootMessage0();
String getRebootMessage1();

String info_uptime();
String info_chipid();
String info_idesize();
String info_flashsize();
String info_sdkver();
String info_cpufreq();
String info_freeheap();
String info_memsketch();
String info_lastreset();
String info_conx();
extern const char *ssid;
String info_stassid();
String info_staip();
String info_stamac();
String info_stagw();
String info_stasub();
String info_dnss();
extern const char *host;
String info_hostnom();
extern const char *apssid;
String info_apssid();
String info_apip();
String info_apmac();
String info_memsmeter();

String return_reset_reason(uint8_t reason);

extern int TemplateCount;

String DeviceID();
String DeviceTP();
