#include "Body.hpp"

Body::Body(const std::string body, uint32_t width, uint32_t height)
		: _body(body), _width(width), _height(height)
{
	if (body.length() != width * height)
		throw "Length of the body needs to be equal to WIDTH * HEIGHT";
};

Body::Body(const Body &other)
		: _body(other._body), _width(other._width), _height(other._height) {}

Body::~Body() {};

Body &Body::operator=(const Body other)
{
	if (&other != this)
	{
		this->_body = other._body;
		this->_width = other._width;
		this->_height = other._height;
	}
	return *this;
}

int Body::getWidth() const
{
	return this->_width;
};

int Body::getHeight() const
{
	return this->_height;
};

const std::string &Body::getBody() const
{
	return this->_body;
}

void Body::setBody(const std::string body, uint32_t width, uint32_t height){
	if (body.length() != width * height && body.length() > 0)
		throw "Length of the body needs to be equal to WIDTH * HEIGHT";
		this->_body = body;
		this->_width = width;
		this->_height = height;
}

bool Body::isColliding(Body &other)
{
	char thisChar;
	char otherChar;
	int thisWidth = this->getWidth();
	int otherWidth = other.getWidth();
	int thisHeight = this->getHeight();
	int otherHeight = other.getHeight();
	int offsetX = this->getPosition().x - other.getPosition().x;
	int offsetY = this->getPosition().y - other.getPosition().y;

	if ((offsetX <= 0 && offsetX - thisWidth >= 0) || (offsetX > 0 && offsetX - otherWidth >= 0))
	{
		return false;
	}
	else if ((offsetY <= 0 && offsetY - thisHeight >= 0) || (offsetY > 0 && offsetY - otherHeight >= 0))
	{
		return false;
	}
	else
	{
		for (int y = 0; y < thisHeight; y++)
		{
			for (int x = 0; x < thisWidth; x++)
			{
				if (((x + offsetX >= 0) && (x + offsetX < otherWidth)) && ((y + offsetY >= 0) && (y + offsetY < otherHeight)))
				{
					thisChar = this->_body[(y * thisWidth) + x];
					otherChar = other._body[((y + offsetY) * otherWidth) + (x + offsetX)];

					if (thisChar != ' ' && otherChar != ' ')
						return true;
				}
			}
		}
		return false;
	}
}