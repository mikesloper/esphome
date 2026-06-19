#include <vector>
#include <string>
#include <cmath>
#include <map>

using namespace std;

std::map<short int, unsigned int> elm327_pid_status;

bool is_ATRV_reponse = false;

void init_elm327_pid_status()
{
   for (int i = 0; i < 20; i++)
   {
      elm327_pid_status[i] = 0;
   }
}

void handle_eml_reponse(const vector<uint8_t> &x)
{
   int receivedSize = x.size();
   ESP_LOGD("ble_client_lambda", "Received bytes size: %d", receivedSize);
   // Log each byte in the array
   for (size_t i = 0; i < receivedSize; ++i)
   {
      //ESP_LOGD("main", "Response Byte %d: 0x%02X", i, x[i]);
   }

   // split by space
   std::string sen(x.begin(), x.end());
   std::vector<std::string> words;
   size_t start = 0;
   size_t end1;
   while ((end1 = sen.find(' ', start)) != std::string::npos)
   {
      words.push_back(sen.substr(start, end1 - start));
      start = end1 + 1;
   }
   words.push_back(sen.substr(start));

   for (size_t i = 0; i < words.size(); ++i)
   {
      //ESP_LOGD("main", "Response Byte %d: %s", i, words[i].c_str());
   }

   ESP_LOGD("main", "WORD SIZE: %d", words.size());
   ESP_LOGD("main", "FIRST BYTE: %s", words[0].c_str()); // if there is a problem with the response first byte is = "NO" (like says "NO CONNECTION"). implement error reporting here.



   if (x[0] == 0x41 && x[1] == 0x54 && x[2] == 0x52 && x[3] == 0x56)
   { // is atvr
         is_ATRV_reponse = true;
   }

   if(is_ATRV_reponse & x.size() == 9 && x[5] == 0x56 )  //0x56 = "V"
   {

         std::string voltage(x.begin(), x.end());
         voltage.erase(voltage.begin() + 5, voltage.end());
         voltage.erase(voltage.begin(), voltage.begin()+1);

         ESP_LOGI("main", "VOLTAGE STRING: %s", voltage.c_str());

         float voltage_float = std::stof(voltage);
         ESP_LOGI("main", "VOLTAGE FLOAT: %f", voltage_float);

         id(odbii_device_voltage).publish_state(voltage_float);

         is_ATRV_reponse  = false;

         
   }



   if (x[1] == 0x34 && x[2] == 0x31 && words.size() >= 3)
   { /// is PID response with header 41

      int pid = 0;
      sscanf(words[1].c_str(), "%x", &pid);

      ESP_LOGD("main", "PID: %d", pid);

      int sensorint = 0;
      std::string joined = "";

      elm327_pid_status[pid] = round(id(uptime_minutes).raw_state); // raw is seconds

      switch (pid)
      {
      case 12:

         if (words.size() != 5)
         {
            break;
         }

         joined = words[2] + words[3];
         sensorint = std::stoi(joined, nullptr, 16);
         ESP_LOGD("main", "RPM: %d", sensorint);
         sensorint = sensorint / 4;
         id(odbii_rpm).publish_state(sensorint);
         break;

      case 5:

         if (words.size() != 4)
         {
            break;
         }
         sensorint = std::stoi(words[2], nullptr, 16);
         ESP_LOGD("main", "Coolant Temperaturemp: %d", sensorint);
         sensorint = sensorint - 40;
         id(odbii_coolant_temp).publish_state(sensorint);
         break;

      case 13:

         if (words.size() != 4)
         {
            break;
         }
         sensorint = std::stoi(words[2], nullptr, 16);
         ESP_LOGD("main", "Speed KPH: %d", sensorint);
         id(odbii_kph).publish_state(sensorint);
         break;
      }
   }
}
