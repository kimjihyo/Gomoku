#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Button.hpp"
#include <iostream>
#include <functional>

Button::Button(sf::RenderWindow *window, const char *label, const sf::Font &font)
    : m_IsToggleButton(false), m_Toggle(false), m_Window(window)
{
    m_ShapeBuffer = new sf::RectangleShape(sf::Vector2f(400.f, 100.f));
    m_ShapeBuffer->setFillColor(sf::Color(85, 85, 85));
    m_ShapeBuffer->setOutlineColor(sf::Color::Black);
    m_ShapeBuffer->setOutlineThickness(4.f);
    m_LabelBuffer = new sf::Text();
    m_LabelBuffer->setFont(font);
    m_LabelBuffer->setFillColor(sf::Color::White);
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
    m_LabelBuffer->setCharacterSize(size.x / 5.f);
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

void Button::MakeButtonToggle()
{
    m_IsToggleButton = true;
}

void Button::OnClick()
{
    if (this->checkIfMouseOnButton())
    {
        this->Toggle();
        m_Callback();
    }
}

void Button::SetOnClick(const std::function<void(void)> &callback)
{
    m_Callback = std::move(callback);
}

void Button::Toggle()
{
    m_Toggle = !m_Toggle;
    if (m_IsToggleButton)
    {
        if (m_Toggle)
            m_ShapeBuffer->setFillColor(sf::Color(13, 71, 161));
        else
            m_ShapeBuffer->setFillColor(sf::Color(85, 85, 85));
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

bool Button::checkIfMouseOnButton()
{
    const sf::Vector2i &mousePosition = sf::Mouse::getPosition(*m_Window);
    return (mousePosition.x >= m_ShapeBuffer->getPosition().x &&
            mousePosition.x <= m_ShapeBuffer->getPosition().x + m_ShapeBuffer->getSize().x &&
            mousePosition.y >= m_ShapeBuffer->getPosition().y &&
            mousePosition.y <= m_ShapeBuffer->getPosition().y + m_ShapeBuffer->getSize().y);
}
