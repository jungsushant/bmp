#include "input.hpp"
#include "glibmm/ustring.h"
#include "sigc++/functors/mem_fun.h"
#include <iostream>
#include <string>

Input::Input() : Gtk::Box(Gtk::Orientation::VERTICAL) {
  m_Entry.set_max_length(16);
  connectSignals();
  m_Entry.set_name("input");
  append(m_Entry);
}

Input::~Input() {}

void Input::setText(const Glib::ustring &text) { m_Entry.set_text(text); }

Glib::ustring Input::getText() const { return m_Entry.get_text(); }

Gtk::Entry &Input::getEntry() { return m_Entry; }

void Input::onTextChange() {
  // Get text from m_Entry, which is of type Glib::ustring
  Glib::ustring text = m_Entry.get_text();

  // Convert Glib::ustring to std::string for processing
  std::string numericText;
  for (char c : text) {
    if (std::isdigit(c)) {
      numericText += c;
    }
  }

  if (!numericText.empty()) {
    int _num = std::stoi(numericText);
    if (_num < 15) {
      numericText = "15";
      m_Entry.set_position(numericText.length());
    }
    if (_num > 900) {
      numericText = "900";
      m_Entry.set_position(numericText.length());
    }
  }

  // Compare the strings (convert Glib::ustring to std::string or vice versa)
  if (text != Glib::ustring(numericText)) {
    setText(numericText); // Assuming setText takes a std::string or a
                          // compatible type
    m_Entry.set_position(numericText.length()); // Keep cursor at the end
  }

  // signalTextChanged.emit(m_Entry.get_text());
  // TODO: Emite text change signal with current value, and update and set
  // max/min from outside.
}
// TODO: use key press event in another class
void Input::onKeyPressEvent() {
  // if (event->get_keyval() == GDK_KEY_Return) {
  signalEnterPressed.emit(m_Entry.get_text());
  // }
}
void Input::connectSignals() {
  // Connect Entry widget signals
  m_Entry.signal_changed().connect(sigc::mem_fun(*this, &Input::onTextChange));
  m_Entry.signal_activate().connect(
      sigc::mem_fun(*this, &Input::onKeyPressEvent));
}