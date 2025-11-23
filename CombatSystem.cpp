#include "CombatSystem.h"

CombatOutcome CombatSystem::ResolveCombat(CombatChoice p, CombatChoice g)
{
	if (p == g)
		return CombatOutcome::Draw;

	if ((p == CombatChoice::Attack && g == CombatChoice::Counter)
		|| (p == CombatChoice::Counter && g == CombatChoice::Defend)
		|| (p == CombatChoice::Defend && g == CombatChoice::Attack))
		return CombatOutcome::PlayerWin;

	return CombatOutcome::GoblinWin;
}
