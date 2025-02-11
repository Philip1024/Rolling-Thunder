#include "Shooter.h"
#include"../../Player/Player.h"
#include"../../Bullet/Bullet.h"

//When this collies with 
void Shooter::collide(Entity* other)
{
	Player* playerCast = dynamic_cast<Player*>(other);

	//if they collide set the player bounce bool to true
	//then set shooter bounce bool to true.
	if (playerCast != nullptr)
	{
		playerCast->update();
	}

	Bullet* bulletCast = dynamic_cast<Bullet*>(other);

	if (bulletCast != nullptr)
	{
		bulletCast->open();
	}
}