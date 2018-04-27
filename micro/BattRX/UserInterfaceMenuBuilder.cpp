#ifndef __USERINTERFACEMENUBUILDER_CPP_
#define __USERINTERFACEMENUBUILDER_CPP_

#include "UserInterfaceMenuBuilder.h"
#include "UserInterface.h"
#include "UserInterfaceLang.h"

namespace UserInterface
{
  __flash const TMenuFunctionReference menuFunctions[] =
  {
    {.entryPoint = 0},                                                                                            //   0 - NONE
    {.entryPoint = (void*)(&(UserInterface::functionScreenSaver)),                                                //   1 - SCREENSAVER
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionWidget)),                                                     //   2 - WIDGET
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionCancel)),                                                     //   3 - CANCEL
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //   4 - USER_MENU_MAIN_MENU
     .args.parm = USER_MENU_MAIN_MENU},                                                                           //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //   5 - USER_MENU_REPORTS
     .args.parm = USER_MENU_REPORTS},                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //   6 - USER_MENU_SETUP
     .args.parm = USER_MENU_SETUP},                                                                               //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //   7 - USER_MENU_MAINTENANCE
     .args.parm = USER_MENU_MAINTENANCE},                                                                         //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //   8 - USER_MENU_INFO
     .args.parm = USER_MENU_INFO},                                                                                //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //   9 - USER_MENU_REPORTS_VISITORS
     .args.parm = USER_MENU_REPORTS_VISITORS},                                                                    //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  10 - USER_MENU_REPORTS_NOSENSOR
     .args.parm = USER_MENU_REPORTS_NOSENSOR},                                                                    //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSummerTimeMenu)),                                        //  11 - USER_MENU_SETUP_SUMMERTIME
     .args.parm = USER_MENU_SETUP_SUMMERTIME},                                                                    //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  12 - USER_MENU_SETUP_COUNTER
     .args.parm = USER_MENU_SETUP_COUNTER},                                                                       //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  13 - USER_MENU_SETUP_ENERGYSAVING
     .args.parm = USER_MENU_SETUP_ENERGYSAVING},                                                                  //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  14 - USER_MENU_SETUP_INTERFACE
     .args.parm = USER_MENU_SETUP_INTERFACE},                                                                     //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  15 - USER_MENU_MAINTENANCE_RESET
     .args.parm = USER_MENU_MAINTENANCE_RESET},                                                                   //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  16 - USER_MENU_INFO_RESETNUM
     .args.parm = USER_MENU_INFO_RESETNUM},                                                                       //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDetectorMenu)),                                          //  17 - USER_MENU_SETUP_COUNTER_DETECTOR
     .args.parm = USER_MENU_SETUP_COUNTER_DETECTOR},                                                              //
    {.entryPoint = (void*)(&(UserInterface::functionSetupInventCntMenu)),                                         //  18 - USER_MENU_SETUP_COUNTER_INVERTCOUNT
     .args.parm = USER_MENU_SETUP_COUNTER_INVERTCOUNT},                                                           //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSaveModeMenu)),                                          //  19 - USER_MENU_SETUP_ENERGYSAVING_SAVEMODE
     .args.parm = USER_MENU_SETUP_ENERGYSAVING_SAVEMODE},                                                         //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkTodayMenu)),                                         //  20 - USER_MENU_SETUP_ENERGYSAVING_WORKTODAY
     .args.parm = USER_MENU_SETUP_ENERGYSAVING_WORKTODAY},                                                        //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkDayMenu)),                                           //  21 - USER_MENU_SETUP_ENERGYSAVING_WORKDAY
     .args.parm = USER_MENU_SETUP_ENERGYSAVING_WORKDAY},                                                          //
    {.entryPoint = (void*)(&(UserInterface::functionSetupBacklightMenu)),                                         //  22 - USER_MENU_SETUP_ENERGYSAVING_BACKLIGHT
     .args.parm = USER_MENU_SETUP_ENERGYSAVING_BACKLIGHT},                                                        //
    {.entryPoint = (void*)(&(UserInterface::functionScreenSaverMenu)),                                            //  23 - USER_MENU_SETUP_SCREENSAVER
     .args.parm = USER_MENU_SETUP_SCREENSAVER},                                                                   //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  24 - USER_MENU_SETUP_WIDGETS
     .args.parm = USER_MENU_SETUP_WIDGETS},                                                                       //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  25 - USER_MENU_MAINTENANCE_RESET_COUNTERS
     .args.parm = USER_MENU_MAINTENANCE_RESET_COUNTERS},                                                          //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  26 - USER_MENU_MAINTENANCE_RESET_FACTORY
     .args.parm = USER_MENU_MAINTENANCE_RESET_FACTORY},                                                           //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  27 - USER_MENU_MAINTENANCE_RESET_DATA
     .args.parm = USER_MENU_MAINTENANCE_RESET_DATA},                                                              //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  28 - USER_MENU_MAINTENANCE_RESET_FULL
     .args.parm = USER_MENU_MAINTENANCE_RESET_FULL},                                                              //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  29 - USER_MENU_MAIN_MENU_REPORTS
     .args.parm = USER_MENU_MAIN_MENU_REPORTS},                                                                   //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  30 - USER_MENU_REPORTS_VISITORS2
     .args.parm = USER_MENU_REPORTS_VISITORS2},                                                                   //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  31 - USER_MENU_REPORTS_NOSENSOR2
     .args.parm = USER_MENU_REPORTS_NOSENSOR2},                                                                   //
    {.entryPoint = (void*)(&(UserInterface::functionMenu)),                                                       //  32 - USER_MENU_SETUP2
     .args.parm = USER_MENU_SETUP2},                                                                              //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkTodayMenu)),                                         //  33 - USER_MENU_SETUP_ENERGYSAVING_WORKTODAY2
     .args.parm = USER_MENU_SETUP_ENERGYSAVING_WORKTODAY2},                                                       //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDateTime)),                                              //  34 - SETUP_CLOCK
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSummerTime)),                                            //  35 - SETUP_SUMMERTIME_OFF
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSummerTime)),                                            //  36 - SETUP_SUMMERTIME_ON
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSummerTime)),                                            //  37 - SETUP_SUMMERTIME_UKR
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDetector)),                                              //  38 - SETUP_COUNTER_DETECTOR_NODETECTION
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDetector)),                                              //  39 - SETUP_COUNTER_DETECTOR_NODETECTIONDIV2
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDetector)),                                              //  40 - SETUP_COUNTER_DETECTOR_SIMULATION
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDetector)),                                              //  41 - SETUP_COUNTER_DETECTOR_STRONGDETECTION
     .args.parm = 3},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDetector)),                                              //  42 - SETUP_COUNTER_DETECTOR_SOFTDETECTION
     .args.parm = 4},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupInventCnt)),                                             //  43 - SETUP_COUNTER_INVERTCOUNT_OFF
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupInventCnt)),                                             //  44 - SETUP_COUNTER_INVERTCOUNT_ON
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupDetectionTime)),                                         //  45 - SETUP_COUNTER_DETECTIONTIME
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSaveMode)),                                              //  46 - SETUP_ENERGYSAVING_SAVEMODE_MIN
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSaveMode)),                                              //  47 - SETUP_ENERGYSAVING_SAVEMODE_NOCOUNT
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSaveMode)),                                              //  48 - SETUP_ENERGYSAVING_SAVEMODE_NOSCREEN
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupSaveMode)),                                              //  49 - SETUP_ENERGYSAVING_SAVEMODE_MAX
     .args.parm = 3},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupInactivityTime)),                                        //  50 - SETUP_ENERGYSAVING_INACTIVITYTIME
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkWeek)),                                              //  51 - SETUP_ENERGYSAVING_WORKWEEK
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkToday)),                                             //  52 - SETUP_ENERGYSAVING_WORKTODAY_OFF
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkToday)),                                             //  53 - SETUP_ENERGYSAVING_WORKTODAY_ON
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkDay)),                                               //  54 - SETUP_ENERGYSAVING_WORKDAY_24H
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkDay)),                                               //  55 - SETUP_ENERGYSAVING_WORKDAY_1SHIFT
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkDay)),                                               //  56 - SETUP_ENERGYSAVING_WORKDAY_2SHIFTS
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWorkDay)),                                               //  57 - SETUP_ENERGYSAVING_WORKDAY_1SH_WITHLUNCH
     .args.parm = 3},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupPassword)),                                              //  58 - SETUP_PASSWORD_MASTER
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupPassword)),                                              //  59 - SETUP_PASSWORD_MANAGER
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReset)),                                                      //  60 - MAINTENANCE_RESET_COUNTERS
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReset)),                                                      //  61 - MAINTENANCE_RESET_FACTORY
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReset)),                                                      //  62 - MAINTENANCE_RESET_DATA
     .args.parm = 3},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReset)),                                                      //  63 - MAINTENANCE_RESET_FULL
     .args.parm = 4},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSafeBattRemove)),                                             //  64 - MAINTENANCE_SAFE_BATT_REMOVE
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReportVisitorsTotal)),                                        //  65 - REPORTS_VISITORS_TOTAL
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReports)),                                                    //  66 - REPORTS_VISITORS_HOUR
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReports)),                                                    //  67 - REPORTS_VISITORS_DAY
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReports)),                                                    //  68 - REPORTS_VISITORS_WEEK
     .args.parm = 3},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReports)),                                                    //  69 - REPORTS_VISITORS_MONTH
     .args.parm = 4},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReports)),                                                    //  70 - REPORTS_NOSENSOR_HOUR
     .args.parm = 5},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionReports)),                                                    //  71 - REPORTS_NOSENSOR_DAY
     .args.parm = 6},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionAuthenticationScreen)),                                       //  72 - AUTHENTICATION_SCREEN
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionResetNum)),                                                   //  73 - INFO_RESETNUM_RESTARTS
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionResetNum)),                                                   //  74 - INFO_RESETNUM_DATARESET
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionResetNum)),                                                   //  75 - INFO_RESETNUM_FACTORYRESET
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionResetNum)),                                                   //  76 - INFO_RESETNUM_PASSWORDFAILS
     .args.parm = 3},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSerialNumber)),                                               //  77 - INFO_SERIALNUM
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionBatteryVoltage)),                                             //  78 - INFO_BATTERY_VOLTAGE
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSensorQuality)),                                              //  79 - MAINTENANCE_SENSORQUALITY
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupBacklight)),                                             //  80 - SETUP_ENERGYSAVING_BACKLIGHT_OFF
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupBacklight)),                                             //  81 - SETUP_ENERGYSAVING_BACKLIGHT_ON
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWidgets)),                                               //  82 - SETUP_WIDGETS_MAIN
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWidgets)),                                               //  83 - SETUP_WIDGETS_LEFT
     .args.parm = 1},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionSetupWidgets)),                                               //  84 - SETUP_WIDGETS_RIGHT
     .args.parm = 2},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionScreenSaverSetup)),                                           //  85 - SETUP_SCREENSAVER_OFF
     .args.parm = 0},                                                                                             //
    {.entryPoint = (void*)(&(UserInterface::functionScreenSaverSetup)),                                           //  86 - SETUP_SCREENSAVER_ON
     .args.parm = 1},                                                                                             //
  };

  __flash const TMenuDescription menuDescription[] =
  {
    {                                                                                                             //   0
      .menuFunction = USER_MENUITEM_REPORTS,
      .textRefLine0 = USER_TEXT_CONST_MENU_REPORTS,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //   1
      .menuFunction = USER_MENUITEM_SETUP,
      .textRefLine0 = USER_TEXT_CONST_MENU_SETUP,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //   2
      .menuFunction = USER_MENUITEM_MAINTENANCE,
      .textRefLine0 = USER_TEXT_CONST_MENU_MAINTENANCE,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //   3
      .menuFunction = USER_MENUITEM_INFO,
      .textRefLine0 = USER_TEXT_CONST_MENU_INFO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //   4
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //   5
      .menuFunction = USER_MENUITEM_REPORTS_VISITORS,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //   6
      .menuFunction = USER_MENUITEM_REPORTS_NOSENSOR,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_NOSENSOR,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //   7
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //   8
      .menuFunction = USER_FUNCTION_SETUP_CLOCK,
      .textRefLine0 = USER_TEXT_CONST_SETUP_CLOCK,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //   9
      .menuFunction = USER_MENUITEM_SETUP_SUMMERTIME,
      .textRefLine0 = USER_TEXT_CONST_SETUP_SUMMERTIME_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_SUMMERTIME_L2,
    },
    {                                                                                                             //  10
      .menuFunction = USER_MENUITEM_SETUP_COUNTER,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_COUNTER_L2,
    },
    {                                                                                                             //  11
      .menuFunction = USER_MENUITEM_SETUP_ENERGYSAVING,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_L2,
    },
    {                                                                                                             //  12
      .menuFunction = USER_FUNCTION_SETUP_PASSWORD_MASTER,
      .textRefLine0 = USER_TEXT_CONST_SETUP_PASSWORD,
      .textRefLine1 = USER_TEXT_CONST_SETUP_PASSWORD_MASTER,
    },
    {                                                                                                             //  13
      .menuFunction = USER_FUNCTION_SETUP_PASSWORD_MANAGER,
      .textRefLine0 = USER_TEXT_CONST_SETUP_PASSWORD,
      .textRefLine1 = USER_TEXT_CONST_SETUP_PASSWORD_MANAGER,
    },
    {                                                                                                             //  14
      .menuFunction = USER_MENUITEM_SETUP_INTERFACE,
      .textRefLine0 = USER_TEXT_CONST_SETUP_INTERFACE,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  15
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  16
      .menuFunction = USER_FUNCTION_MAINTENANCE_SENSORQUALITY,
      .textRefLine0 = USER_TEXT_CONST_MAINTENANCE_SENSORQUALITY_L1,
      .textRefLine1 = USER_TEXT_CONST_MAINTENANCE_SENSORQUALITY_L2,
    },
    {                                                                                                             //  17
      .menuFunction = USER_MENUITEM_MAINTENANCE_RESET,
      .textRefLine0 = USER_TEXT_CONST_MAINTENANCE_RESET_COUNTERS_L1,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  18
      .menuFunction = USER_FUNCTION_MAINTENANCE_SAFE_BATT_REMOVE,
      .textRefLine0 = USER_TEXT_CONST_MAINTENANCE_SAFE_BATT_REMOVE_L1,
      .textRefLine1 = USER_TEXT_CONST_MAINTENANCE_SAFE_BATT_REMOVE_L2,
    },
    {                                                                                                             //  19
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  20
      .menuFunction = USER_MENUITEM_INFO_RESETNUM,
      .textRefLine0 = USER_TEXT_CONST_INFO_RESETNUM_L1,
      .textRefLine1 = USER_TEXT_CONST_INFO_RESETNUM_L2,
    },
    {                                                                                                             //  21
      .menuFunction = USER_FUNCTION_INFO_SERIALNUM,
      .textRefLine0 = USER_TEXT_CONST_INFO_SERIALNUM,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  22
      .menuFunction = USER_FUNCTION_INFO_BATTERY_VOLTAGE,
      .textRefLine0 = USER_TEXT_CONST_INFO_BATTERY_VOLTAGE,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  23
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  24
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_TOTAL,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_TOTAL,
    },
    {                                                                                                             //  25
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_HOUR,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_HOUR,
    },
    {                                                                                                             //  26
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_DAY,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_DAY,
    },
    {                                                                                                             //  27
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_WEEK,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_WEEK,
    },
    {                                                                                                             //  28
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_MONTH,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_MONTH,
    },
    {                                                                                                             //  29
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  30
      .menuFunction = USER_FUNCTION_REPORTS_NOSENSOR_HOUR,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_NOSENSOR,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_HOUR,
    },
    {                                                                                                             //  31
      .menuFunction = USER_FUNCTION_REPORTS_NOSENSOR_DAY,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_NOSENSOR,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_DAY,
    },
    {                                                                                                             //  32
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  33
      .menuFunction = USER_FUNCTION_SETUP_SUMMERTIME_OFF,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_OFF,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  34
      .menuFunction = USER_FUNCTION_SETUP_SUMMERTIME_ON,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_ON,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  35
      .menuFunction = USER_FUNCTION_SETUP_SUMMERTIME_UKR,
      .textRefLine0 = USER_TEXT_CONST_SETUP_SUMMERTIME_AUTO,
      .textRefLine1 = USER_TEXT_CONST_SETUP_SUMMERTIME_UKR,
    },
    {                                                                                                             //  36
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  37
      .menuFunction = USER_MENUITEM_SETUP_COUNTER_DETECTOR,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_DETECTOR_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_COUNTER_DETECTOR_L2,
    },
    {                                                                                                             //  38
      .menuFunction = USER_MENUITEM_SETUP_COUNTER_INVERTCOUNT,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_INVERTCOUNT_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_COUNTER_INVERTCOUNT_L2,
    },
    {                                                                                                             //  39
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_DETECTIONTIME,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_DETECTIONTIME,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  40
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  41
      .menuFunction = USER_MENUITEM_SETUP_ENERGYSAVING_SAVEMODE,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_L2,
    },
    {                                                                                                             //  42
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_INACTIVITYTIME,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_INACTIVITYTIME_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_INACTIVITYTIME_L2,
    },
    {                                                                                                             //  43
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKWEEK,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKWEEK_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKWEEK_L2,
    },
    {                                                                                                             //  44
      .menuFunction = USER_MENUITEM_SETUP_ENERGYSAVING_WORKTODAY,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKTODAY_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKTODAY_L2,
    },
    {                                                                                                             //  45
      .menuFunction = USER_MENUITEM_SETUP_ENERGYSAVING_WORKDAY,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKDAY_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKDAY_L2,
    },
    {                                                                                                             //  46
      .menuFunction = USER_MENUITEM_SETUP_ENERGYSAVING_BACKLIGHT,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_BACKLIGHT,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  47
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  48
      .menuFunction = USER_MENUITEM_SETUP_SCREENSAVER,
      .textRefLine0 = USER_TEXT_CONST_SETUP_SCREENSAVER,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  49
      .menuFunction = USER_MENUITEM_SETUP_WIDGETS,
      .textRefLine0 = USER_TEXT_CONST_SETUP_WIDGETS,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  50
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  51
      .menuFunction = USER_MENUITEM_MAINTENANCE_RESET_COUNTERS,
      .textRefLine0 = USER_TEXT_CONST_MAINTENANCE_RESET_COUNTERS_L1,
      .textRefLine1 = USER_TEXT_CONST_MAINTENANCE_RESET_COUNTERS_L2,
    },
    {                                                                                                             //  52
      .menuFunction = USER_MENUITEM_MAINTENANCE_RESET_FACTORY,
      .textRefLine0 = USER_TEXT_CONST_MAINTENANCE_RESET_FACTORY_L1,
      .textRefLine1 = USER_TEXT_CONST_MAINTENANCE_RESET_FACTORY_L2,
    },
    {                                                                                                             //  53
      .menuFunction = USER_MENUITEM_MAINTENANCE_RESET_DATA,
      .textRefLine0 = USER_TEXT_CONST_MAINTENANCE_RESET_DATA,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  54
      .menuFunction = USER_MENUITEM_MAINTENANCE_RESET_FULL,
      .textRefLine0 = USER_TEXT_CONST_MAINTENANCE_RESET_FULL,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  55
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  56
      .menuFunction = USER_FUNCTION_INFO_RESETNUM_RESTARTS,
      .textRefLine0 = USER_TEXT_CONST_INFO_RESETNUM_RESTARTS,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  57
      .menuFunction = USER_FUNCTION_INFO_RESETNUM_DATARESET,
      .textRefLine0 = USER_TEXT_CONST_INFO_RESETNUM_DATARESET,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  58
      .menuFunction = USER_FUNCTION_INFO_RESETNUM_FACTORYRESET,
      .textRefLine0 = USER_TEXT_CONST_INFO_RESETNUM_FACTORYRESET,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  59
      .menuFunction = USER_FUNCTION_INFO_RESETNUM_PASSWORDFAILS,
      .textRefLine0 = USER_TEXT_CONST_INFO_RESETNUM_PASSWORDFAILS_L1,
      .textRefLine1 = USER_TEXT_CONST_INFO_RESETNUM_PASSWORDFAILS_L2,
    },
    {                                                                                                             //  60
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  61
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_DETECTOR_NODETECTION,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_DETECTOR_NODETECTION,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  62
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_DETECTOR_NODETECTIONDIV2,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_DETECTOR_NODETECTIONDIV2,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  63
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_DETECTOR_SIMULATION,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_DETECTOR_SIMULATION,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  64
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_DETECTOR_STRONGDETECTION,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_DETECTOR_STRONGDETECTION,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  65
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_DETECTOR_SOFTDETECTION,
      .textRefLine0 = USER_TEXT_CONST_SETUP_COUNTER_DETECTOR_SOFTDETECTION,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  66
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  67
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_INVERTCOUNT_OFF,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_NO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  68
      .menuFunction = USER_FUNCTION_SETUP_COUNTER_INVERTCOUNT_ON,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_YES,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  69
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  70
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_MIN,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_MIN,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  71
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_NOCOUNT,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_NOCOUNT_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_NOCOUNT_L2,
    },
    {                                                                                                             //  72
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_NOSCREEN,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_NOSCREEN_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_NOSCREEN_L2,
    },
    {                                                                                                             //  73
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_MAX,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_SAVEMODE_MAX,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  74
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  75
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKTODAY_OFF,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_NO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  76
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKTODAY_ON,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_YES,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  77
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  78
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_24H,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKDAY_24H,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  79
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_1SHIFT,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKDAY_1SHIFT,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  80
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_2SHIFTS,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKDAY_2SHIFTS,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  81
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_1SH_WITHLUNCH,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKDAY_1SHIFT,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKDAY_WITHLUNCH,
    },
    {                                                                                                             //  82
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  83
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_BACKLIGHT_OFF,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_OFF,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  84
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_BACKLIGHT_ON,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_ON,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  85
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  86
      .menuFunction = USER_FUNCTION_SETUP_SCREENSAVER_OFF,
      .textRefLine0 = USER_TEXT_CONST_SETUP_SCREENSAVER,
      .textRefLine1 = USER_TEXT_CONST_SETUP_SCREENSAVER_OFF,
    },
    {                                                                                                             //  87
      .menuFunction = USER_FUNCTION_SETUP_SCREENSAVER_ON,
      .textRefLine0 = USER_TEXT_CONST_SETUP_SCREENSAVER,
      .textRefLine1 = USER_TEXT_CONST_SETUP_SCREENSAVER_ON,
    },
    {                                                                                                             //  88
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  89
      .menuFunction = USER_FUNCTION_SETUP_WIDGETS_MAIN,
      .textRefLine0 = USER_TEXT_CONST_SETUP_WIDGETS_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_WIDGETS_MAIN,
    },
    {                                                                                                             //  90
      .menuFunction = USER_FUNCTION_SETUP_WIDGETS_LEFT,
      .textRefLine0 = USER_TEXT_CONST_SETUP_WIDGETS_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_WIDGETS_LEFT,
    },
    {                                                                                                             //  91
      .menuFunction = USER_FUNCTION_SETUP_WIDGETS_RIGHT,
      .textRefLine0 = USER_TEXT_CONST_SETUP_WIDGETS_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_WIDGETS_RIGHT,
    },
    {                                                                                                             //  92
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  93
      .menuFunction = USER_FUNCTION_CANCEL,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_NO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  94
      .menuFunction = USER_FUNCTION_MAINTENANCE_RESET_COUNTERS,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_YES,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  95
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  96
      .menuFunction = USER_FUNCTION_CANCEL,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_NO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  97
      .menuFunction = USER_FUNCTION_MAINTENANCE_RESET_FACTORY,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_YES,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             //  98
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             //  99
      .menuFunction = USER_FUNCTION_CANCEL,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_NO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 100
      .menuFunction = USER_FUNCTION_MAINTENANCE_RESET_DATA,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_YES,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 101
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             // 102
      .menuFunction = USER_FUNCTION_CANCEL,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_NO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 103
      .menuFunction = USER_FUNCTION_MAINTENANCE_RESET_FULL,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_YES,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 104
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             // 105
      .menuFunction = USER_MENUITEM_REPORTS_VISITORS2,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 106
      .menuFunction = USER_MENUITEM_REPORTS_NOSENSOR2,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_NOSENSOR,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 107
      .menuFunction = USER_MENUITEM_SETUP2,
      .textRefLine0 = USER_TEXT_CONST_MENU_SETUP,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 108
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             // 109
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_TOTAL,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_TOTAL,
    },
    {                                                                                                             // 110
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_HOUR,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_HOUR,
    },
    {                                                                                                             // 111
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_DAY,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_DAY,
    },
    {                                                                                                             // 112
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_WEEK,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_WEEK,
    },
    {                                                                                                             // 113
      .menuFunction = USER_FUNCTION_REPORTS_VISITORS_MONTH,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_VISITORS,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_MONTH,
    },
    {                                                                                                             // 114
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             // 115
      .menuFunction = USER_FUNCTION_REPORTS_NOSENSOR_HOUR,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_NOSENSOR,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_HOUR,
    },
    {                                                                                                             // 116
      .menuFunction = USER_FUNCTION_REPORTS_NOSENSOR_DAY,
      .textRefLine0 = USER_TEXT_CONST_REPORTS_NOSENSOR,
      .textRefLine1 = USER_TEXT_CONST_REPORTS_DAY,
    },
    {                                                                                                             // 117
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             // 118
      .menuFunction = USER_FUNCTION_SETUP_PASSWORD_MANAGER,
      .textRefLine0 = USER_TEXT_CONST_SETUP_PASSWORD,
      .textRefLine1 = USER_TEXT_CONST_SETUP_PASSWORD_MANAGER,
    },
    {                                                                                                             // 119
      .menuFunction = USER_MENUITEM_SETUP_ENERGYSAVING_WORKTODAY2,
      .textRefLine0 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKTODAY_L1,
      .textRefLine1 = USER_TEXT_CONST_SETUP_ENERGYSAVING_WORKTODAY_L2,
    },
    {                                                                                                             // 120
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
    {                                                                                                             // 121
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKTODAY_OFF,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_NO,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 122
      .menuFunction = USER_FUNCTION_SETUP_ENERGYSAVING_WORKTODAY_ON,
      .textRefLine0 = USER_TEXT_CONST_SWITCH_YES,
      .textRefLine1 = USER_TEXT_CONST_EMPTY,
    },
    {                                                                                                             // 123
      .menuFunction = 0,
      .textRefLine0 = 0,
      .textRefLine1 = 0,
    },
  };

}

#endif
