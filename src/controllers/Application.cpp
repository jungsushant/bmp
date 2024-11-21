#include "Application.hpp"
#include "MainScreen.hpp"
#include "UploadView.hpp"
#include "gtkmm/box.h"
#include "gtkmm/cssprovider.h"
#include "gtkmm/enums.h"
#include "gtkmm/stack.h"

Application::Application() : Gtk::Application("com.example.yourdamapp") {
  loadCss();
}

void Application::on_activate() {
  auto mainWindow = Gtk::manage(new Gtk::Window());
  mainWindow->set_title("Image resize and compress");
  mainWindow->set_default_size(1280, 720);

  // Stacks are pages/screens
  auto stack = Gtk::manage(new Gtk::Stack());

  // Main upload component
  auto uploadView = Gtk::make_managed<UploadView>(*mainWindow, "all");

  // Add upload component inside main screen.
  auto mainScreen = Gtk::manage(new MainScreen(*mainWindow, uploadView));

  // Set size and name of main screen
  mainScreen->set_size_request(1280, -1);
  mainScreen->set_name("main-screen");

  // Add main screen to pages.
  stack->add(*mainScreen, "main", "Main");

  stack->set_visible_child("main"); // Show main screen

  // Add stack and switcher to main window
  auto vbox = Gtk::manage(new Gtk::Box(Gtk::Orientation::VERTICAL));
  vbox->append(*stack);

  mainWindow->set_child(*vbox);
  add_window(*mainWindow);
  mainWindow->present();
}
void Application::loadCss() {
  auto cssProvider = Gtk::CssProvider::create();
  std::string cssPath = "../styles.css";
  try {
    cssProvider->load_from_path(cssPath);
  } catch (const Gtk::CssParserError &ex) {
    throw std::runtime_error("Failed to load CSS: " + cssPath + "\n" +
                             ex.what());
  }

  Gtk::StyleProvider::add_provider_for_display(
      Gdk::Display::get_default(), cssProvider,
      GTK_STYLE_PROVIDER_PRIORITY_USER);
}