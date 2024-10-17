#pragma once

enum Color {GREEN = 70, BLACK = 239, PINK = 211};

static class ConsoleColors
{
	public:
		static int EnableColor();
		static void DisableColor();
		static void SetColor(Color);
};

