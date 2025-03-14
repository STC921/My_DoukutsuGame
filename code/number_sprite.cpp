#include "number_sprite.h"
#include "sprite.h"
#include <assert.h>

namespace{
	const std::string kSpritePath("TextBox");
	//const units::Game kSourceX = digit * units::kHalfTile;
	const units::Game kSourceRedY = 8 * units::kHalfTile;
	const units::Game kSourceWhiteY = 7 * units::kHalfTile;

	const units::Game kPlusSourceX = 4 * units::kHalfTile;
	const units::Game kMinusSourceX = 5 * units::kHalfTile;
	const units::Game kOpSourceY = 6 * units::kHalfTile;

	const units::Game kSourceWidth = units::kHalfTile;
	const units::Game kSourceHeight = units::kHalfTile;

	const int kRadix = 10;
}

NumberSprite::NumberSprite(Graphics& graphics, int number, int num_digits, ColorType color, OperatorType op) : padding_(0.0f){
	assert(number >= 0);
	units::Game source_y = color == RED ? kSourceRedY : kSourceWhiteY;
	int digit_count = 0;
	do{
		const int digit = number % kRadix;
		reversed_glyphs_.push_back(boost::shared_ptr<Sprite>(new Sprite(
			graphics, "TextBox",
			units::gameToPixel(digit * units::kHalfTile), units::gameToPixel(source_y),
			units::gameToPixel(kSourceWidth), units::gameToPixel(kSourceHeight))));
		number /= 10;
		++digit_count;
	} while (number != 0);
	assert(num_digits == 0 || num_digits >= digit_count);
	padding_ = num_digits == 0 ? 0.0f : units::kHalfTile * (num_digits - digit_count);
	switch (op){
	case PLUS:
		reversed_glyphs_.push_back(boost::shared_ptr<Sprite>(new Sprite(
			graphics, "TextBox",
			units::gameToPixel(kPlusSourceX), units::gameToPixel(kOpSourceY),
			units::gameToPixel(kSourceWidth), units::gameToPixel(kSourceHeight))));
		break;
	case MINUS:
		reversed_glyphs_.push_back(boost::shared_ptr<Sprite>(new Sprite(
			graphics, "TextBox",
			units::gameToPixel(kMinusSourceX), units::gameToPixel(kOpSourceY),
			units::gameToPixel(kSourceWidth), units::gameToPixel(kSourceHeight))));
		break;
	case NONE:
		break;
	}

}

void NumberSprite::draw(Graphics& graphics, units::Game x, units::Game y){
	for (size_t i = 0; i < reversed_glyphs_.size(); ++i){
		const units::Game offset = units::kHalfTile * (reversed_glyphs_.size() - 1 - i);
		reversed_glyphs_[i]->draw(graphics, x + offset + padding_, y);
	}
}