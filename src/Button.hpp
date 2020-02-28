#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
private:
    sf::RectangleShape *m_ShapeBuffer;
    sf::Text *m_LabelBuffer;
    bool m_IsToggleButton;
    bool m_Toggle;
    std::function<void(void)> m_Callback;
    sf::RenderWindow *m_Window;
public:
    Button(sf::RenderWindow *window, const char* label, const sf::Font& font);
    ~Button();
    void SetPosition(const sf::Vector2f& position);
    void SetSize(const sf::Vector2f& size);
    const sf::Vector2f& GetPosition() const;
    const sf::Vector2f& GetSize() const;
    void OnClick();
    void SetOnClick(const std::function<void(void)>& callback);
    const sf::RectangleShape& GetButtonShape() const;
    const sf::Text& GetLabelShape() const;
    void MakeButtonToggle();
    void Toggle();
private:
    void setLabelPosition();
    bool checkIfMouseOnButton();
};