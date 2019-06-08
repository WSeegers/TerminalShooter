#include "Body.hpp"

Body::Body(const std::string body, uint32_t width, uint32_t height)
		: _body(body), _width(width), _height(height)
{
	if (body.length() != width * height)
		throw "Length of the body needs to be equal to WIDTH * HEIGHT";
};

Body::Body(const Body &other)
		: _body(other._body), _width(other._width), _height(other._height) {}

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