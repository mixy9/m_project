#include "Card.h" 


Card::Card()
{
}

Card::Card(sPtr<SpriteNode>& cardSprite, size_t cardNumber) :
	m_backSprite(cardSprite),
	m_number(cardNumber),
	m_showCard(false)
{
	m_frontCardTexture = "Graphics/Cards/" + std::to_string(cardNumber) + ".png";
	m_backSprite = std::make_shared<SpriteNode>(Filename::backCard, NULL, NULL, 2101.53f, 1129.41f);
	m_frontSprite = std::make_shared<SpriteNode>(m_frontCardTexture, NULL, NULL, 2101.53f, 1129.41f);	
}

sf::Sprite& Card::setBackSprite()
{ 
	return *m_backSprite;
}

sf::Sprite& Card::setFrontSprite()
{
	return *m_frontSprite;
}

void Card::setPosition(float posX, float posY)
{
	m_backSprite->setPosition(posX, posY);
	m_frontSprite->setPosition(posX, posY);
}

int Card::getNumber()
{
	return m_number;
}

bool Card::inactive()
{
	if (m_showCard == true)
		return false;
}

bool Card::isShown(bool show)
{ 
	return m_showCard = show;
}

void Card::draw()
{ 
	if (m_showCard == true)
	{
		Screen::window.draw(*m_frontSprite);
	}
	else 
	{
		Screen::window.draw(*m_backSprite);
	}
}

Card::~Card()
{
}



