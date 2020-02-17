#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <iostream>
#include <functional>

Button::Button(const char *label, const sf::Font &font)
{
    m_ShapeBuffer = new sf::RectangleShape(sf::Vector2f(400.f, 100.f));
    m_ShapeBuffer->setFillColor(sf::Color(85, 85, 85));

    m_LabelBuffer = new sf::Text();
    m_LabelBuffer->setFont(font);
    m_LabelBuffer->setString(label);
    m_LabelBuffer->setStyle(sf::Text::Bold);
    this->setLabelPosition();
}

Button::~Button()
{
    delete m_ShapeBuffer;
    delete m_LabelBuffer;
}

void Button::SetPosition(const sf::Vector2f &position)
{
    m_ShapeBuffer->setPosition(position);
    this->setLabelPosition();
}

void Button::SetSize(const sf::Vector2f &size)
{
    m_ShapeBuffer->setSize(size);
    this->setLabelPosition();
}

const sf::Vector2f &Button::GetPosition() const
{
    return m_ShapeBuffer->getPosition();
}
const sf::Vector2f &Button::GetSize() const
{
    return m_ShapeBuffer->getSize();
}

const sf::RectangleShape &Button::GetButtonShape() const
{
    return *m_ShapeBuffer;
}

const sf::Text &Button::GetLabelShape() const
{
    return *m_LabelBuffer;
}

void Button::OnClick(const sf::Vector2i &mousePosition, const std::function<void(void)> &callback)
{
    if (mousePosition.x >= m_ShapeBuffer->getPosition().x &&
        mousePosition.x <= m_ShapeBuffer->getPosition().x + m_ShapeBuffer->getSize().x &&
        mousePosition.y >= m_ShapeBuffer->getPosition().y &&
        mousePosition.y <= m_ShapeBuffer->getPosition().y + m_ShapeBuffer->getSize().y)
    {
        callback();
    }
}

void Button::setLabelPosition()
{
    sf::FloatRect boundingBox = m_LabelBuffer->getLocalBounds();
    m_LabelBuffer->setOrigin(boundingBox.left + boundingBox.width / 2.0f,
                             boundingBox.top + boundingBox.height / 2.0f);
    m_LabelBuffer->setPosition(m_ShapeBuffer->getPosition().x + m_ShapeBuffer->getSize().x / 2,
                               m_ShapeBuffer->getPosition().y + m_ShapeBuffer->getSize().y / 2);
}
