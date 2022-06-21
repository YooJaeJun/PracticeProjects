#include "Slime/Slime.h"
#include "Fairy/Fairy.h"

int main()
{
	Monster monster = Monster("∏ÛΩ∫≈Õ", 1, 10, 5);
	monster.Print();
	monster.Attack();

	puts("");

	Slime slime;
	slime.Print();
	slime.Attack();
	slime.Skill();
	((Monster)slime).Attack();

	puts("");

	Fairy fairy;
	fairy.Print();
	fairy.Attack();
	fairy.Flying();

	return 0;
}