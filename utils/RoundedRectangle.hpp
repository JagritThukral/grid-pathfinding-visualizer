// credits: https://gist.github.com/Wesxdz/e8667fb20ce5864f758d39685d6547ce
#pragma once
#include "SFML/Graphics.hpp"
#include <numbers> 

class RoundedRectangle : public sf::Shape
{
public:
    size_t getPointCount() const override
    {
        return m_cornerPointCount * 4;
    }

    sf::Vector2f getPoint(size_t index) const override
    {
        if (m_cornerPointCount == 1 || m_radius == 0.0f)
        {
            sf::RectangleShape rect(m_size);
            return rect.getPoint(index);
        } else
        {
            const size_t corner = index/m_cornerPointCount;
            float angle = 0;
            bool isLastPointOnCorner = (index % m_cornerPointCount == m_cornerPointCount - 1);
            if (isLastPointOnCorner)
            {
                angle = 90.0f;
            } else
            {
                angle = (index % m_cornerPointCount) * m_anglePerPoint;
            }
            sf::Vector2f point;
            switch(corner)
            {
                case 0:
                    point = {m_radius, m_radius};
                    angle -= 180;
                break;
                case 1:
                    point = {m_size.x - m_radius, m_radius};
                    angle -= 90;
                break;
                case 2:
                    point = {m_size.x - m_radius, m_size.y - m_radius};
                break;
                default:
                    point = {m_radius, m_size.y - m_radius};
                    angle += 90;
            }
            point += {cosf(angle * std::numbers::pi/180) * m_radius, sinf(angle * std::numbers::pi/180) * m_radius};
            return point;
        }
        
    }

    void setSize(const sf::Vector2f size)
    {
        m_size = size;
        update();
    }

    sf::Vector2f getSize() const {
        return m_size;
    }

    void setRadius(float radius)
    {
        m_radius = radius;
        update();
    }

    float getRadius() const
    {
        return m_radius;
    }

    size_t getCornerPointCount() const
    {
        return m_cornerPointCount;
    }

    void setCornerPointCount(const float points)
    {
        m_cornerPointCount = static_cast<size_t>(points);
        m_anglePerPoint = 90.0f / points;
        update();
    }

private:
    // TODO: Per edge rounding
    size_t m_cornerPointCount = 2;
    float m_anglePerPoint{};
    float m_radius = 1.0f;
    sf::Vector2f m_size;
};