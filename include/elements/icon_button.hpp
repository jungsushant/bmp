#ifndef ICON_BUTTON_H
#define ICON_BUTTON_H

#include <functional>
#include <gtkmm.h>

class IconButton : public Gtk::Button {
public:
  using ClickCallback = std::function<void()>;

  IconButton(const std::string &iconPath, ClickCallback onClick);
  virtual ~IconButton() = default;

protected:
  void onClick();

private:
  ClickCallback mOnClick;
};

#endif // ICON_BUTTON_H
