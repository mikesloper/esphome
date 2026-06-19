#pragma once

#include "esphome/core/preferences.h"
#include "esphome/core/component.h"
#include "esphome/core/log.h"


namespace esphome {
namespace disabler {


struct disablerConfig {
  char mppt1[20];
  char mppt2[20];
  char bms1[20];
  char bms2[20];
  char shunt1[20];
  char dc2dc1[20];
  char odbii1[20];
  char airheater1[20];
  char flowmeter1[20];
  char inverter1[20];
  char charger1[20];
  char device1[20];   //spare 
  char device2[20];   //spare 
  

};

class Disabler : public Component {
 public:
 
  void setup() override;
  void save();
  void loadConfig();
  bool exists(char const *check);
  void log_config();


  void save_mppt1(const char *tag);
  void save_mppt2(const char *tag);
  void save_bms1(const char *tag);
  void save_bms2(const char *tag);
  void save_shunt1(const char *tag);
  void save_dc2dc1(const char *tag);
  void save_odbii1(const char *tag);
  void save_airheater1(const char *tag);
  void save_flowmeter1(const char *tag);
  void save_inverter1(const char *tag);
  
  float get_setup_priority() const override { return setup_priority::BUS; }

  

  protected:
    ESPPreferenceObject pref_;
    disablerConfig config_;
    bool setupComplete_ = false;


};

}  // namespace disabler
}  // namespace esphome



