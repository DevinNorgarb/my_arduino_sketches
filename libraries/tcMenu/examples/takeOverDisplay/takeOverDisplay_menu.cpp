/*
    The code in this file uses open source libraries provided by thecoderscorner

    DO NOT EDIT THIS FILE, IT WILL BE GENERATED EVERY TIME YOU USE THE UI DESIGNER
    INSTEAD EITHER PUT CODE IN YOUR SKETCH OR CREATE ANOTHER SOURCE FILE.

    All the variables you may need access to are marked extern in this file for easy
    use elsewhere.
*/

#include <Arduino.h>
#include <tcMenu.h>
#include "takeOverDisplay_menu.h"

// Global variable declarations

const PROGMEM ConnectorLocalInfo applicationInfo = { "Take Over Display", "40722ec4-e8bc-4889-b54e-d81b14cb429c" };
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
LiquidCrystalRenderer renderer(lcd, 20, 4);
EthernetServer server(3333);

// Global Menu Item declarations

RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityIPAddressRtCall, ipAddressRenderFn, "IPAddress", 7, NO_CALLBACK)
IpAddressMenuItem menuConnectivityIPAddress(fnConnectivityIPAddressRtCall, 12, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityChangePinRtCall, textItemRenderFn, "ChangePin", -1, onChangePin)
TextMenuItem menuConnectivityChangePin(fnConnectivityChangePinRtCall, 14, 15, &menuConnectivityIPAddress);
const SubMenuInfo PROGMEM minfoConnectivity = { "Connectivity", 11, 0xFFFF, 0, NO_CALLBACK };
RENDERING_CALLBACK_NAME_INVOKE(fnConnectivityRtCall, backSubItemRenderFn, "Connectivity", -1, NO_CALLBACK)
BackMenuItem menuBackConnectivity(fnConnectivityRtCall, &menuConnectivityChangePin);
SubMenuItem menuConnectivity(&minfoConnectivity, &menuBackConnectivity, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsDateRtCall, dateItemRenderFn, "Date", -1, NO_CALLBACK)
DateFormattedMenuItem menuSettingsDate(fnSettingsDateRtCall, 18, NULL);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsTimeRtCall, timeItemRenderFn, "Time", -1, NO_CALLBACK)
TimeFormattedMenuItem menuSettingsTime(fnSettingsTimeRtCall, 17, (MultiEditWireType)EDITMODE_TIME_12H, &menuSettingsDate);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsNum6x4RtCall, largeNumItemRenderFn, "Num6x4", -1, NO_CALLBACK)
EditableLargeNumberMenuItem menuSettingsNum6x4(fnSettingsNum6x4RtCall, 16, 10, 4, &menuSettingsTime);
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsPositiveIntsRtCall, largeNumItemRenderFn, "PositiveInts", -1, NO_CALLBACK)
EditableLargeNumberMenuItem menuSettingsPositiveInts(fnSettingsPositiveIntsRtCall, 15, 9, 0, false, &menuSettingsNum6x4);
const AnyMenuInfo PROGMEM minfoSettingsSaveSettings = { "Save Settings", 6, 0xFFFF, 0, onSaveSettings };
ActionMenuItem menuSettingsSaveSettings(&minfoSettingsSaveSettings, &menuSettingsPositiveInts);
const AnalogMenuInfo PROGMEM minfoSettingsPower = { "Power", 5, 5, 250, NO_CALLBACK, 0, 10, "W" };
AnalogMenuItem menuSettingsPower(&minfoSettingsPower, 0, &menuSettingsSaveSettings);
const BooleanMenuInfo PROGMEM minfoSettingsEnabled = { "Enabled", 4, 2, 1, NO_CALLBACK, NAMING_TRUE_FALSE };
BooleanMenuItem menuSettingsEnabled(&minfoSettingsEnabled, false, &menuSettingsPower);
const SubMenuInfo PROGMEM minfoSettings = { "Settings", 3, 0xFFFF, 0, NO_CALLBACK };
RENDERING_CALLBACK_NAME_INVOKE(fnSettingsRtCall, backSubItemRenderFn, "Settings", -1, NO_CALLBACK)
BackMenuItem menuBackSettings(fnSettingsRtCall, &menuSettingsEnabled);
SubMenuItem menuSettings(&minfoSettings, &menuBackSettings, &menuConnectivity);
const AnyMenuInfo PROGMEM minfoQuestionDialog = { "Question Dialog", 9, 0xFFFF, 0, onQuestionDlg };
ActionMenuItem menuQuestionDialog(&minfoQuestionDialog, &menuSettings);
const AnyMenuInfo PROGMEM minfoInfoDialog = { "Info Dialog", 8, 0xFFFF, 0, onInfoDlg };
ActionMenuItem menuInfoDialog(&minfoInfoDialog, &menuQuestionDialog);
RENDERING_CALLBACK_NAME_INVOKE(fnTextRtCall, textItemRenderFn, "Text", -1, NO_CALLBACK)
TextMenuItem menuText(fnTextRtCall, 7, 10, &menuInfoDialog);
const char enumStrFood_0[] PROGMEM  = "Pizza";
const char enumStrFood_1[] PROGMEM  = "Pasta";
const char enumStrFood_2[] PROGMEM  = "Salad";
const char* const enumStrFood[] PROGMEM  = { enumStrFood_0, enumStrFood_1, enumStrFood_2 };
const EnumMenuInfo PROGMEM minfoFood = { "Food", 2, 3, 2, onFoodChoice, enumStrFood };
EnumMenuItem menuFood(&minfoFood, 0, &menuText);
const AnyMenuInfo PROGMEM minfoTakeDisplay = { "Take Display", 1, 0xFFFF, 0, onTakeOverDisplay };
ActionMenuItem menuTakeDisplay(&minfoTakeDisplay, &menuFood);
RENDERING_CALLBACK_NAME_INVOKE(fnTimeRtCall, timeItemRenderFn, "Time", -1, NO_CALLBACK)
TimeFormattedMenuItem menuTime(fnTimeRtCall, 13, (MultiEditWireType)EDITMODE_TIME_12H, &menuTakeDisplay);


// Set up code

void setupMenu() {
    menuText.setReadOnly(true);
    menuInfoDialog.setLocalOnly(true);
    menuConnectivity.setSecured(true);
    menuConnectivity.setLocalOnly(true);
    menuSettingsSaveSettings.setLocalOnly(true);

    lcd.setIoAbstraction(io23017);
    lcd.begin(20, 4);
    switches.initialise(io23017, true);
    menuMgr.initForEncoder(&renderer, &menuTime, 6, 7, 5);
    remoteServer.begin(&server, &applicationInfo);
}
