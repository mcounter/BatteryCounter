#ifndef __USERINTERFACE_H_
#define __USERINTERFACE_H_

namespace UserInterface
{
  void init();
  void run();

  void enable(bool _withUserKey);
  void disable();
  bool enabled();
  void leaveInterface();
  bool menuActive();
  bool photoActive();

  void functionScreenSaver();
  void functionWidget();
  void functionMenu();
  void functionCancel();

  void functionSetupSummerTimeMenu();
  void functionSetupDetectorMenu();
  void functionSetupInventCntMenu();
  void functionSetupSaveModeMenu();
  void functionSetupWorkTodayMenu();
  void functionSetupWorkDayMenu();
  void functionSetupBacklightMenu();

  void functionSetupDateTime();
  void functionSetupSummerTime();
  void functionSetupDetector();
  void functionSetupInventCnt();
  void functionSetupDetectionTime();
  void functionSetupSaveMode();
  void functionSetupInactivityTime();
  void functionSetupWorkWeek();
  void functionSetupWorkToday();
  void functionSetupWorkDay();
  void functionSetupPassword();
  void functionReset();
  void functionSafeBattRemove();
  void functionReportVisitorsTotal();
  void functionReports();
  void functionBatteryVoltage();
  void functionSensorQuality();
  void functionSetupBacklight();
  void functionResetNum();
  void functionSerialNumber();
  void functionSetupWidgets();

  void functionAuthenticationScreen();

  void functionScreenSaverMenu();
  void functionScreenSaverSetup();
}

#endif
