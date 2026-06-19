#include "disabler.h"

#define HASH_KEY "someenablerkey1"
#define DATA_SIZE 100
//#define LABEL_SIZE 10

namespace esphome {
namespace disabler {

static const char *const TAG = "disabler";



void Disabler::setup() {
  this->loadConfig();
}

void Disabler::save_mppt1(const char *tag) {
  strcpy(this->config_.mppt1, tag);
  this->save();
}

void Disabler::save_mppt2(const char *tag) {
  strcpy(this->config_.mppt2, tag);
  this->save();
}

void Disabler::save_bms1(const char *tag) {
  strcpy(this->config_.bms1, tag);
  this->save();
}

void Disabler::save_bms2(const char *tag) {
  strcpy(this->config_.bms2, tag);
  this->save();
}

void Disabler::save_shunt1(const char *tag) {
  strcpy(this->config_.shunt1, tag);
  this->save();
}

void Disabler::save_dc2dc1(const char *tag) {
  strcpy(this->config_.dc2dc1, tag);
  this->save();
}

void Disabler::save_odbii1(const char *tag) {
  strcpy(this->config_.odbii1, tag);
  this->save();
}

void Disabler::save_airheater1(const char *tag) {
  strcpy(this->config_.airheater1, tag);
  this->save();
}

void Disabler::save_flowmeter1(const char *tag) {
  strcpy(this->config_.flowmeter1, tag);
  this->save();
}

void Disabler::save_inverter1(const char *tag) {
  strcpy(this->config_.inverter1, tag);
  this->save();
}

 bool Disabler::exists(char const *check) {

  this->loadConfig();
 // ESP_LOGD(TAG, "check1: %s", this->config_.mppt1);
  ESP_LOGD(TAG, "check2: %s", check);


  if (strcmp(check, this->config_.mppt1) == 0){ return true; } 
  if (strcmp(check, this->config_.mppt2) == 0){ return true; } 
  if (strcmp(check, this->config_.bms1) == 0){ return true; } 
  if (strcmp(check, this->config_.bms2) == 0){ return true; } 
  if (strcmp(check, this->config_.shunt1) == 0){ return true; } 
  if (strcmp(check, this->config_.dc2dc1) == 0){ return true; } 
  if (strcmp(check, this->config_.odbii1) == 0){ return true; } 
  if (strcmp(check, this->config_.airheater1) == 0){ return true; } 
  if (strcmp(check, this->config_.flowmeter1) == 0){ return true; } 
  if (strcmp(check, this->config_.inverter1) == 0){ return true; } 

  return false;

 }

 void Disabler::save() {

  if(this->pref_.save(&this->config_)) {
      ESP_LOGD(TAG, "saved");
  } else {
      ESP_LOGD(TAG, "not saved");
  }
  global_preferences->sync();

 }

 void Disabler::log_config()
 {
  
 }

  void Disabler::loadConfig() {

    if(this->setupComplete_){
      return void();
    }
    
    uint32_t hash = fnv1_hash(HASH_KEY);
    this->pref_ = global_preferences->make_preference<disablerConfig>(hash, true);
    
    if (this->pref_.load(&this->config_)){
      ESP_LOGD(TAG, "enabler prefs: %s", this->config_.mppt1);
      this->setupComplete_ = true;
    } else {
      ESP_LOGD(TAG, "nothing to show");
    }


  }



}  // namespace preferences
}  // namespace esphome



