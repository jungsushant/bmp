#include "Application.hpp"

int main(int argc, char *argv[]) {
  auto app = std::make_unique<Application>();
  return app->run(argc, argv);
}