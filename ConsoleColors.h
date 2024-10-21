#pragma once

enum Color {GREEN = 70, DARK_GREEN = 22, BLACK = 239, PINK = 211, BLUE = 4, DARK_ORANGE = 172};

static class ConsoleColors
{
	public:
		static int EnableColor();
		static void DisableColor();
		static void SetColor(Color);
};

