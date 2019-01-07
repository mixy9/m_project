#pragma once
#include "stdafx.h"




class SceneNode : public sf::Transformable, public sf::Drawable, public sf::NonCopyable
{
public:
	SceneNode();
	~SceneNode();

	virtual void draw() = 0;

	virtual void initialize() = 0;

	virtual void update(sf::Time& elapsedTime) = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual void drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
};



