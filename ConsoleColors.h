#pragma once

enum Color {
	LIME_GREEN = 70,
	DARK_GREEN = 22,
	LIGHT_GREEN = 154,
	BLACK = 239,
	PINK = 211,
	LIGHT_BLUE = 4,
	BABY_BLUE = 123,
	BROWN = 94,
	TAN = 179,
	ORANGE = 172,
	WHITE = 231,
	RED = 196,
	DARK_RED = 124,
	PURPLE = 141,
	DARK_PURPLE = 55,
	LAVENDER = 189,
	GRAY = 244,
	LIGHT_YELLOW = 227,
	DARK_YELLOW = 220
};

static class ConsoleColors
{
	public:
		static int EnableColor();
		static void DisableColor();
		static void SetColor(Color);
};

