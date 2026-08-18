#pragma once
const float frameCap{ 60 };

const std::string resourceDirectory{ "../../RiskOfRainReturnsRemake/Resources/" };

struct MapData {
	Rectf hitbox;
	bool interactable{ false };
};

struct EntityData {
	Vector2f pivotPoint;
	Rectf sourceRect;
	Rectf hitbox;
};

enum class CommandoSprites {
	none = 0,
	idle,
	idlehalf,
	walk,
	walkhalf,
	back,
	backhalf,
	jump,
	peak,
	fall,
	climbUp,
	climbDown,
	death,
	doubleTapA,
	doubleTapB,
	fullMetalJacket,
	tacticalDive,
	singleSuppressive,
	doubleSuppressive,
	tracer
};

enum class ChestType {
	damage,
	healing,
	utility,
	regular
};

enum class Items {
	meatNugger,
	lensMakersGlasses,
	sproutingEgg,
	headstompers,
	lifeSavings,
	barbedWire,
	rustyKnife,
	mysteriousVial,
	monsterTooth,
	soldiersSyringe,
	crowbar,
	medkit
};