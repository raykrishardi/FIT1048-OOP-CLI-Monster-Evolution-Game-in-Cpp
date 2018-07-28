#include "BossMonster.h"

//-------------------------------------
//				Constructor
//-------------------------------------

static const MonsterType BOSS_MONSTER_TYPE = Skeletor;
static const int INITIAL_SKILL_LEVEL = 10;
static const int INITIAL_HEALTH = 20;
static const int INITIAL_SPECIAL_POWER_MODIFIER = 2;

//when creating a boss monster, initialise the object with the appropriate values for each attributes
BossMonster::BossMonster() : HigherRankMonster(BOSS_MONSTER_TYPE, INITIAL_SKILL_LEVEL, INITIAL_HEALTH, INITIAL_SPECIAL_POWER_MODIFIER, ObjectType::BossMonster){}