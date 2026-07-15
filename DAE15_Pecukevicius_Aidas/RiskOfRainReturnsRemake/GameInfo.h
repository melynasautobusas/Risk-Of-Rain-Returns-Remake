#pragma once

const int frameCap{ 60 };

enum class CommandoState {
	idle,
	walk,
	back,
	jump,
	climb,
	death
};

enum class CommandoAbilities {
	doubleTap,
	fullMetalJacket,
	tacticalDive,
	suppresiveFire
};