#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
private:
    sf::RectangleShape *m_ShapeBuffer;
    sf::Text *m_LabelBuffer;
public:
    Button(const char* label, const sf::Font& font);
    ~Button();
    void SetPosition(const sf::Vector2f& position);
    void SetSize(const sf::Vector2f& size);
    const sf::Vector2f& GetPosition() const;
    const sf::Vector2f& GetSize() const;
    void OnClick(const sf::Vector2i& mousePosition, const std::function<void(void)>& callback);
    const sf::RectangleShape& GetButtonShape() const;
    const sf::Text& GetLabelShape() const;
private:
    void setLabelPosition();
};