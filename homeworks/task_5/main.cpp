#include "logger.hpp"

int main() {
  Logger *log_1 = Logger::Instance();
  log_1->Message(LOG_NORMAL, "log_1 loaded");

  // ...

  log_1->Message(LOG_ERROR, "error happens! help me!");
  log_1->Print();

  Logger *log_2 = Logger::Instance();
  log_2->Message(LOG_NORMAL, "log_2 loaded");
  log_2->Print();

  // Logger log_3;
  // log_3.Message(LOG_NORMAL, "log_3 loaded");
  // log_3.Print();
}
