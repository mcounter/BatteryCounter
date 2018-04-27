#ifndef __USERINTERFACEMENUBUILDER_H_
#define __USERINTERFACEMENUBUILDER_H_

#define USER_FUNCTION_NONE                                                                                        (0)
#define USER_FUNCTION_SCREENSAVER                                                                                 (1)
#define USER_FUNCTION_WIDGET                                                                                      (2)
#define USER_FUNCTION_CANCEL                                                                                      (3)
#define USER_MENUITEM_MAIN_MENU                                                                                   (4)
#define USER_MENUITEM_REPORTS                                                                                     (5)
#define USER_MENUITEM_SETUP                                                                                       (6)
#define USER_MENUITEM_MAINTENANCE                                                                                 (7)
#define USER_MENUITEM_INFO                                                                                        (8)
#define USER_MENUITEM_REPORTS_VISITORS                                                                            (9)
#define USER_MENUITEM_REPORTS_NOSENSOR                                                                            (10)
#define USER_MENUITEM_SETUP_SUMMERTIME                                                                            (11)
#define USER_MENUITEM_SETUP_COUNTER                                                                               (12)
#define USER_MENUITEM_SETUP_ENERGYSAVING                                                                          (13)
#define USER_MENUITEM_SETUP_INTERFACE                                                                             (14)
#define USER_MENUITEM_MAINTENANCE_RESET                                                                           (15)
#define USER_MENUITEM_INFO_RESETNUM                                                                               (16)
#define USER_MENUITEM_SETUP_COUNTER_DETECTOR                                                                      (17)
#define USER_MENUITEM_SETUP_COUNTER_INVERTCOUNT                                                                   (18)
#define USER_MENUITEM_SETUP_ENERGYSAVING_SAVEMODE                                                                 (19)
#define USER_MENUITEM_SETUP_ENERGYSAVING_WORKTODAY                                                                (20)
#define USER_MENUITEM_SETUP_ENERGYSAVING_WORKDAY                                                                  (21)
#define USER_MENUITEM_SETUP_ENERGYSAVING_BACKLIGHT                                                                (22)
#define USER_MENUITEM_SETUP_SCREENSAVER                                                                           (23)
#define USER_MENUITEM_SETUP_WIDGETS                                                                               (24)
#define USER_MENUITEM_MAINTENANCE_RESET_COUNTERS                                                                  (25)
#define USER_MENUITEM_MAINTENANCE_RESET_FACTORY                                                                   (26)
#define USER_MENUITEM_MAINTENANCE_RESET_DATA                                                                      (27)
#define USER_MENUITEM_MAINTENANCE_RESET_FULL                                                                      (28)
#define USER_MENUITEM_MAIN_MENU_REPORTS                                                                           (29)
#define USER_MENUITEM_REPORTS_VISITORS2                                                                           (30)
#define USER_MENUITEM_REPORTS_NOSENSOR2                                                                           (31)
#define USER_MENUITEM_SETUP2                                                                                      (32)
#define USER_MENUITEM_SETUP_ENERGYSAVING_WORKTODAY2                                                               (33)
#define USER_FUNCTION_SETUP_CLOCK                                                                                 (34)
#define USER_FUNCTION_SETUP_SUMMERTIME_OFF                                                                        (35)
#define USER_FUNCTION_SETUP_SUMMERTIME_ON                                                                         (36)
#define USER_FUNCTION_SETUP_SUMMERTIME_UKR                                                                        (37)
#define USER_FUNCTION_SETUP_COUNTER_DETECTOR_NODETECTION                                                          (38)
#define USER_FUNCTION_SETUP_COUNTER_DETECTOR_NODETECTIONDIV2                                                      (39)
#define USER_FUNCTION_SETUP_COUNTER_DETECTOR_SIMULATION                                                           (40)
#define USER_FUNCTION_SETUP_COUNTER_DETECTOR_STRONGDETECTION                                                      (41)
#define USER_FUNCTION_SETUP_COUNTER_DETECTOR_SOFTDETECTION                                                        (42)
#define USER_FUNCTION_SETUP_COUNTER_INVERTCOUNT_OFF                                                               (43)
#define USER_FUNCTION_SETUP_COUNTER_INVERTCOUNT_ON                                                                (44)
#define USER_FUNCTION_SETUP_COUNTER_DETECTIONTIME                                                                 (45)
#define USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_MIN                                                             (46)
#define USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_NOCOUNT                                                         (47)
#define USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_NOSCREEN                                                        (48)
#define USER_FUNCTION_SETUP_ENERGYSAVING_SAVEMODE_MAX                                                             (49)
#define USER_FUNCTION_SETUP_ENERGYSAVING_INACTIVITYTIME                                                           (50)
#define USER_FUNCTION_SETUP_ENERGYSAVING_WORKWEEK                                                                 (51)
#define USER_FUNCTION_SETUP_ENERGYSAVING_WORKTODAY_OFF                                                            (52)
#define USER_FUNCTION_SETUP_ENERGYSAVING_WORKTODAY_ON                                                             (53)
#define USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_24H                                                              (54)
#define USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_1SHIFT                                                           (55)
#define USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_2SHIFTS                                                          (56)
#define USER_FUNCTION_SETUP_ENERGYSAVING_WORKDAY_1SH_WITHLUNCH                                                    (57)
#define USER_FUNCTION_SETUP_PASSWORD_MASTER                                                                       (58)
#define USER_FUNCTION_SETUP_PASSWORD_MANAGER                                                                      (59)
#define USER_FUNCTION_MAINTENANCE_RESET_COUNTERS                                                                  (60)
#define USER_FUNCTION_MAINTENANCE_RESET_FACTORY                                                                   (61)
#define USER_FUNCTION_MAINTENANCE_RESET_DATA                                                                      (62)
#define USER_FUNCTION_MAINTENANCE_RESET_FULL                                                                      (63)
#define USER_FUNCTION_MAINTENANCE_SAFE_BATT_REMOVE                                                                (64)
#define USER_FUNCTION_REPORTS_VISITORS_TOTAL                                                                      (65)
#define USER_FUNCTION_REPORTS_VISITORS_HOUR                                                                       (66)
#define USER_FUNCTION_REPORTS_VISITORS_DAY                                                                        (67)
#define USER_FUNCTION_REPORTS_VISITORS_WEEK                                                                       (68)
#define USER_FUNCTION_REPORTS_VISITORS_MONTH                                                                      (69)
#define USER_FUNCTION_REPORTS_NOSENSOR_HOUR                                                                       (70)
#define USER_FUNCTION_REPORTS_NOSENSOR_DAY                                                                        (71)
#define USER_FUNCTION_AUTHENTICATION_SCREEN                                                                       (72)
#define USER_FUNCTION_INFO_RESETNUM_RESTARTS                                                                      (73)
#define USER_FUNCTION_INFO_RESETNUM_DATARESET                                                                     (74)
#define USER_FUNCTION_INFO_RESETNUM_FACTORYRESET                                                                  (75)
#define USER_FUNCTION_INFO_RESETNUM_PASSWORDFAILS                                                                 (76)
#define USER_FUNCTION_INFO_SERIALNUM                                                                              (77)
#define USER_FUNCTION_INFO_BATTERY_VOLTAGE                                                                        (78)
#define USER_FUNCTION_MAINTENANCE_SENSORQUALITY                                                                   (79)
#define USER_FUNCTION_SETUP_ENERGYSAVING_BACKLIGHT_OFF                                                            (80)
#define USER_FUNCTION_SETUP_ENERGYSAVING_BACKLIGHT_ON                                                             (81)
#define USER_FUNCTION_SETUP_WIDGETS_MAIN                                                                          (82)
#define USER_FUNCTION_SETUP_WIDGETS_LEFT                                                                          (83)
#define USER_FUNCTION_SETUP_WIDGETS_RIGHT                                                                         (84)
#define USER_FUNCTION_SETUP_SCREENSAVER_OFF                                                                       (85)
#define USER_FUNCTION_SETUP_SCREENSAVER_ON                                                                        (86)

#define USER_MENU_MAIN_MENU                                                                                       (0)
#define USER_MENU_REPORTS                                                                                         (5)
#define USER_MENU_SETUP                                                                                           (8)
#define USER_MENU_MAINTENANCE                                                                                     (16)
#define USER_MENU_INFO                                                                                            (20)
#define USER_MENU_REPORTS_VISITORS                                                                                (24)
#define USER_MENU_REPORTS_NOSENSOR                                                                                (30)
#define USER_MENU_SETUP_SUMMERTIME                                                                                (33)
#define USER_MENU_SETUP_COUNTER                                                                                   (37)
#define USER_MENU_SETUP_ENERGYSAVING                                                                              (41)
#define USER_MENU_SETUP_INTERFACE                                                                                 (48)
#define USER_MENU_MAINTENANCE_RESET                                                                               (51)
#define USER_MENU_INFO_RESETNUM                                                                                   (56)
#define USER_MENU_SETUP_COUNTER_DETECTOR                                                                          (61)
#define USER_MENU_SETUP_COUNTER_INVERTCOUNT                                                                       (67)
#define USER_MENU_SETUP_ENERGYSAVING_SAVEMODE                                                                     (70)
#define USER_MENU_SETUP_ENERGYSAVING_WORKTODAY                                                                    (75)
#define USER_MENU_SETUP_ENERGYSAVING_WORKDAY                                                                      (78)
#define USER_MENU_SETUP_ENERGYSAVING_BACKLIGHT                                                                    (83)
#define USER_MENU_SETUP_SCREENSAVER                                                                               (86)
#define USER_MENU_SETUP_WIDGETS                                                                                   (89)
#define USER_MENU_MAINTENANCE_RESET_COUNTERS                                                                      (93)
#define USER_MENU_MAINTENANCE_RESET_FACTORY                                                                       (96)
#define USER_MENU_MAINTENANCE_RESET_DATA                                                                          (99)
#define USER_MENU_MAINTENANCE_RESET_FULL                                                                          (102)
#define USER_MENU_MAIN_MENU_REPORTS                                                                               (105)
#define USER_MENU_REPORTS_VISITORS2                                                                               (109)
#define USER_MENU_REPORTS_NOSENSOR2                                                                               (115)
#define USER_MENU_SETUP2                                                                                          (118)
#define USER_MENU_SETUP_ENERGYSAVING_WORKTODAY2                                                                   (121)

namespace UserInterface
{
  typedef struct
  {
    unsigned char parm;
  } TMenuFunctionArgs;

  typedef struct
  {
    void* entryPoint;
    TMenuFunctionArgs args;
  } TMenuFunctionReference;

  typedef struct
  {
    unsigned char menuFunction;
    unsigned char textRefLine0;
    unsigned char textRefLine1;
  } TMenuDescription;

  extern __flash const TMenuFunctionReference menuFunctions[];
  extern __flash const TMenuDescription menuDescription[];
}

#endif
