#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "utils/Constants.hpp"

class UIManager {
public:
    explicit UIManager(tgui::Gui& gui);
    void initialize();
    void bindRedrawOnInteraction(const tgui::Widget::Ptr& widget, bool* needsRedraw);
    tgui::Button::Ptr visualizeButton;
    tgui::Button::Ptr resetButton;
    tgui::Button::Ptr resetPathButton;
    tgui::Slider::Ptr animationSpeedSlider;
    tgui::Label::Ptr speedLabel;
    tgui::Label::Ptr pathLengthLabel;
private:
    static tgui::Panel::Ptr createSidebarPanel(const tgui::String& title);
    static tgui::HorizontalLayout::Ptr createLegendEntry(const tgui::Color& color, const tgui::String& text);
    tgui::Gui& m_gui;
};
