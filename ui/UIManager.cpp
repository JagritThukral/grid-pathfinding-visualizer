#include "UIManager.hpp"

UIManager::UIManager(tgui::Gui &gui) : m_gui(gui) {
}

void UIManager::initialize() {
    const auto header = tgui::Panel::create();
    header->setSize(headerSize);
    header->getRenderer()->setBackgroundColor(CARD_COLOR);
    header->getRenderer()->setRoundedBorderRadius(borderRadius);
    header->setPosition(headerPos);


    const auto title = tgui::Label::create("Pathfinding Visualizer");
    title->setTextSize(36);
    title->getRenderer()->setTextColor(tgui::Color::White);
    title->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
    title->setHorizontalAlignment(tgui::HorizontalAlignment::Left);
    title->setVerticalAlignment(tgui::VerticalAlignment::Center);
    title->setPosition(10, 0);
    title->setSize("100%", "100%");
    header->add(title, "title");

    m_gui.add(header);


    const auto controlPanel = tgui::Panel::create();
    controlPanel->getRenderer()->setBackgroundColor(CARD_COLOR);
    controlPanel->getRenderer()->setRoundedBorderRadius(borderRadius);
    controlPanel->setPosition(controlPanelPos);
    controlPanel->setSize(controlPanelSize);
    controlPanel->getRenderer()->setPadding(20);
    m_gui.add(controlPanel);

    visualizeButton = tgui::Button::create("Visualize");
    visualizeButton->setSize(btnSize);
    visualizeButton->getRenderer()->setBackgroundColor(ACCENT_COLOR);
    visualizeButton->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
    visualizeButton->getRenderer()->setTextColor(sf::Color::White);
    visualizeButton->getRenderer()->setTextSize(16);
    visualizeButton->getRenderer()->setRoundedBorderRadius(8);
    visualizeButton->getRenderer()->setBorderColor(tgui::Color::Transparent);
    controlPanel->add(visualizeButton);

    resetButton = tgui::Button::create("Reset");
    resetButton->setSize(btnSize);
    resetButton->getRenderer()->setBackgroundColor(BTN_COLOR);
    resetButton->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
    resetButton->getRenderer()->setTextColor(sf::Color::White);
    resetButton->getRenderer()->setTextSize(16);
    resetButton->getRenderer()->setRoundedBorderRadius(8);
    resetButton->getRenderer()->setBorderColor(tgui::Color::Transparent);
    resetButton->setPosition({tgui::bindRight(visualizeButton) + "20.f", tgui::bindTop(visualizeButton)});
    controlPanel->add(resetButton);

    const auto speedPanel = tgui::Panel::create();
    speedPanel->setPosition({tgui::bindRight(resetButton) + "20.f", tgui::bindTop(resetButton)});
    speedPanel->setSize(speedPanelSize);
    speedPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);

    speedLabel = tgui::Label::create("Animation Speed");
    speedLabel->getRenderer()->setTextColor(tgui::Color(200, 200, 200));
    speedLabel->getRenderer()->setTextStyle(tgui::TextStyle::Bold);
    speedLabel->setPosition(0, 0);
    speedLabel->setTextSize(16);
    speedPanel->add(speedLabel);

    animationSpeedSlider = tgui::Slider::create(1, 100);
    animationSpeedSlider->setPosition(0, 35);
    animationSpeedSlider->setSize("100%", 12);
    animationSpeedSlider->getRenderer()->setTrackColor(tgui::Color(60, 65, 77));
    animationSpeedSlider->getRenderer()->setThumbColor(ACCENT_COLOR);
    speedPanel->add(animationSpeedSlider);

    controlPanel->add(speedPanel);


    auto sidebar = tgui::Panel::create();
    sidebar->setPosition(sidebarPos);
    sidebar->setSize(sidebarSize);
    sidebar->getRenderer()->setBackgroundColor(tgui::Color::Transparent);
    m_gui.add(sidebar);

    auto legend = tgui::Panel::create();
    legend->setSize({sidebarSize.x, legendPanelHeight});
    legend->setPosition(0, 0);
    legend->getRenderer()->setBackgroundColor(CARD_COLOR);
    legend->getRenderer()->setRoundedBorderRadius(borderRadius);
    legend->getRenderer()->setPadding(20);

    auto legendTitle = tgui::Label::create("Legend");
    legendTitle->setTextSize(20);
    legendTitle->getRenderer()->setTextColor(tgui::Color::White);
    legend->add(legendTitle);

    // function to add legend entries
    auto addLegend2Col = [&](sf::Color color, const char *text, int index) {
        int col = index % 2;
        int row = index / 2;

        tgui::Layout x = col == 0 ? 0.f : (sidebarSize.x / 2.f) + 10.f;
        tgui::Layout y = 40.f + row * 36.f;

        auto rowPanel = tgui::Panel::create();
        rowPanel->setPosition(x, y);
        rowPanel->setSize({sidebarSize.x / 2.f, 28});
        rowPanel->getRenderer()->setBackgroundColor(tgui::Color::Transparent);

        auto colorBox = tgui::Panel::create();
        colorBox->setSize(22, 22);
        colorBox->setPosition(0, 3);
        colorBox->getRenderer()->setBackgroundColor(color);
        rowPanel->add(colorBox);

        auto label = tgui::Label::create(text);
        label->setPosition(30, 2);
        label->setTextSize(15);
        label->getRenderer()->setTextColor(tgui::Color(200, 200, 200));
        rowPanel->add(label);

        legend->add(rowPanel);
    };

    addLegend2Col(COLOR_START, "Start Node", 0);
    addLegend2Col(COLOR_END, "End Node", 1);
    addLegend2Col(COLOR_PATH, "Shortest Path", 2);
    addLegend2Col(COLOR_VISITED, "Visited Node", 3);
    addLegend2Col(COLOR_DISCOVERED, "Discovered", 4);
    addLegend2Col(COLOR_DEFAULT, "Unvisited", 5);
    addLegend2Col(COLOR_WALL, "Wall", 6);

    sidebar->add(legend);

    //  CELL DISTANCE PANEL 
    auto cellDist = tgui::Panel::create();
    cellDist->setSize({sidebarSize.x, cellDistPanelHeight});
    cellDist->setPosition(0, legendPanelHeight + 20);
    cellDist->getRenderer()->setBackgroundColor(CARD_COLOR);
    cellDist->getRenderer()->setRoundedBorderRadius(borderRadius);
    cellDist->getRenderer()->setPadding(20);

    auto cdTitle = tgui::Label::create("Cell Distance");
    cdTitle->setTextSize(20);
    cdTitle->getRenderer()->setTextColor(tgui::Color::White);
    cellDist->add(cdTitle);

    auto cdText = tgui::Label::create(
        "The cost to move from one cell to another:\n\n"
        "• Adjacent (H/V): 1\n"
        "• Diagonal: 1.41421356 (√2)"
    );
    cdText->setPosition(0, 40);
    cdText->setTextSize(15);
    cdText->getRenderer()->setTextColor(tgui::Color(180, 188, 200));
    cellDist->add(cdText);

    sidebar->add(cellDist);


    //  HOW IT WORKS PANEL 
    auto works = tgui::Panel::create();
    works->setSize({sidebarSize.x, howItWorksPanelHeight});
    works->setPosition(0, legendPanelHeight + cellDistPanelHeight + 40);
    works->getRenderer()->setBackgroundColor(CARD_COLOR);
    works->getRenderer()->setRoundedBorderRadius(borderRadius);
    works->getRenderer()->setPadding(20);

    auto hwTitle = tgui::Label::create("How it Works");
    hwTitle->setTextSize(20);
    hwTitle->getRenderer()->setTextColor(tgui::Color::White);
    works->add(hwTitle);

    auto step1 = tgui::Label::create("1. Click on the grid to add walls/obstacles.");
    step1->setPosition(0, 40);
    step1->setTextSize(15);
    step1->getRenderer()->setTextColor(tgui::Color(180, 188, 200));
    works->add(step1);

    auto step2 = tgui::Label::create("2. Drag the start and end nodes to move them.");
    step2->setPosition(0, 70);
    step2->setTextSize(15);
    step2->getRenderer()->setTextColor(tgui::Color(180, 188, 200));
    works->add(step2);

    auto step3 = tgui::Label::create("3. Click \"Visualize\" to find the shortest path.");
    step3->setPosition(0, 100);
    step3->setTextSize(15);
    step3->getRenderer()->setTextColor(tgui::Color(180, 188, 200));
    works->add(step3);

    sidebar->add(works);


    // RESULTS PANEL
    auto results = tgui::Panel::create();
    results->setSize({sidebarSize.x, resultsPanelHeight});
    results->setPosition(0, legendPanelHeight + cellDistPanelHeight + howItWorksPanelHeight + 60);
    results->getRenderer()->setBackgroundColor(CARD_COLOR);
    results->getRenderer()->setRoundedBorderRadius(borderRadius);
    results->getRenderer()->setPadding(20);

    auto resultsTitle = tgui::Label::create("Results");
    resultsTitle->setTextSize(20);
    resultsTitle->getRenderer()->setTextColor(tgui::Color::White);
    results->add(resultsTitle);

    pathLengthLabel = tgui::Label::create("--");
    pathLengthLabel->setPosition(0, 40);
    pathLengthLabel->setTextSize(20);
    pathLengthLabel->getRenderer()->setTextColor(sf::Color::White);
    results->add(pathLengthLabel);

    sidebar->add(results);
}

tgui::Panel::Ptr UIManager::createSidebarPanel(const tgui::String &title) {
    auto panel = tgui::Panel::create();
    panel->getRenderer()->setBackgroundColor(tgui::Color(28, 30, 35));
    panel->getRenderer()->setRoundedBorderRadius(10);

    const auto titleLabel = tgui::Label::create(title);
    titleLabel->setTextSize(18);
    panel->add(titleLabel);

    return panel;
}

tgui::HorizontalLayout::Ptr UIManager::createLegendEntry(const tgui::Color &color, const tgui::String &text) {
    auto layout = tgui::HorizontalLayout::create();
    const auto colorBox = tgui::Panel::create();
    colorBox->getRenderer()->setBackgroundColor(color);
    colorBox->setSize(20, 20);
    layout->add(colorBox);
    const auto label = tgui::Label::create(text);
    layout->add(label);
    return layout;
}

void UIManager::bindRedrawOnInteraction(const tgui::Widget::Ptr &widget, bool *needsRedraw) {
    widget->onMouseEnter([needsRedraw] {
        *needsRedraw = true;
    });

    widget->onMouseLeave([needsRedraw] {
        *needsRedraw = true;
    });

    widget->onFocus([needsRedraw] {
        *needsRedraw = true;
    });

    widget->onUnfocus([needsRedraw] {
        *needsRedraw = true;
    });

    widget->onPositionChange([needsRedraw] {
        *needsRedraw = true;
    });

    widget->onSizeChange([needsRedraw] {
        *needsRedraw = true;
    });

    widget->onAnimationFinish([needsRedraw] {
        *needsRedraw = true;
    });
}
