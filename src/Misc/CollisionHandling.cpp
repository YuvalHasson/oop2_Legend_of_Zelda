#include "CollisionHandling.h"

#include <iostream> //debugging


namespace
{

	void LinkWall(GameObject& link, GameObject& wall)
	{
		link.handleCollision();

		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->undoMove();
		}

	}

	void LinkWater(GameObject& link, GameObject& water)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->undoMove();
		}
	}

	void WaterLink(GameObject& water, GameObject& link)
	{
		LinkWater(link, water);
	}

	void LinkPot(GameObject& link, GameObject& pot)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->undoMove();
			if (linkPtr->isAttacking())
			{
				pot.destroy();
			}
		}
	}
	
	void PotLink(GameObject& pot, GameObject& link)
	{
		LinkPot(link, pot);
	}

	void WallLink(GameObject& wall, GameObject& link)
	{
		LinkWall(link, wall);
	}

	void LinkOctorok(GameObject& link, GameObject& octorok)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			if(!linkPtr->getInvincible()){
				std::cout<<linkPtr->getInvincible()<<std::endl;
				linkPtr->pushBack();
				linkPtr->initializeInvincible();
				linkPtr->setHp(linkPtr->getHp() - 1);
			}
			if (linkPtr->isAttacking())
			{
				octorok.handleCollision();
			}
		}
	}

	void OctorokLink(GameObject& octorok, GameObject& link)
	{
		LinkOctorok(link, octorok);
	}

	void OctorokWall(GameObject& octorok, GameObject& wall)
	{
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		if (octorokPtr)
		{
			octorokPtr->undoMove();
		}
	}

	void WallOctorok(GameObject& wall, GameObject& octorok)
	{
		OctorokWall(octorok, wall);
	}

	void OctorokWater(GameObject& octorok, GameObject& water)
	{
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		if (octorokPtr)
		{
			octorokPtr->undoMove();
		}
	}

	void WaterOctorok(GameObject& water, GameObject& octorok)
	{
		OctorokWater(octorok, water);
	}

	void SwordOctorok(GameObject& sword, GameObject& octorok){
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		Sword* swordPtr = dynamic_cast<Sword*>(&sword);
		if (octorokPtr && swordPtr)
		{	
			if(swordPtr->getActive()){
				octorokPtr->pushBack();
				octorokPtr->setHp(octorokPtr->getHp() - 1);
				swordPtr->deActivate();

			}
		}
	}

	void OctorokSword(GameObject& octorok, GameObject& sword)
	{
	}

	void SwordWall(GameObject& sword, GameObject& wall)
	{
	}

	void WallSword(GameObject& wall, GameObject& sword)
	{
		SwordWall(sword, wall);
	}

	void OctoProjectileWall(GameObject& octorokProjectile, GameObject& wall)
	{
		OctorokProjectile* octorokProjectilePtr = dynamic_cast<OctorokProjectile*>(&octorokProjectile);
		if (octorokProjectilePtr)
		{
			octorokProjectilePtr->destroy();
		}
	}

	void WallOctoProjectile(GameObject& wall, GameObject& octorokProjectile)
	{
		OctoProjectileWall(octorokProjectile, wall);
	}

	using HitFunctionPtr = void (*)(GameObject&, GameObject&);
	// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	// std::unordered_map is better, but it requires defining good hash function for pair
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Link), typeid(Wall))] = &LinkWall;
		phm[Key(typeid(Link), typeid(Pot))] = &LinkPot;
		phm[Key(typeid(Wall), typeid(Link))] = &WallLink; // ==> wall to link collision
		phm[Key(typeid(Pot), typeid(Link))] = &PotLink; // ==> Pot to link collision
		phm[Key(typeid(Link), typeid(WaterTile))] = &LinkWater;
		phm[Key(typeid(WaterTile), typeid(Link))] = &WaterLink;
		phm[Key(typeid(Link), typeid(Octorok))] = &LinkOctorok;
		phm[Key(typeid(Octorok), typeid(Link))] = &OctorokLink;
		phm[Key(typeid(Octorok), typeid(Wall))] = &OctorokWall;
		phm[Key(typeid(Wall), typeid(Octorok))] = &WallOctorok;
		phm[Key(typeid(Octorok), typeid(WaterTile))] = &OctorokWater;
		phm[Key(typeid(WaterTile), typeid(Octorok))] = &WaterOctorok;
		phm[Key(typeid(Sword), typeid(Octorok))] = &SwordOctorok;
		phm[Key(typeid(Octorok), typeid(Sword))] = &OctorokSword;
		phm[Key(typeid(OctorokProjectile), typeid(Wall))] = &OctoProjectileWall;
		phm[Key(typeid(Wall), typeid(OctorokProjectile))] = &WallOctoProjectile;
		phm[Key(typeid(Sword), typeid(Wall))] = &SwordWall;
		phm[Key(typeid(Wall), typeid(Sword))] = &WallSword;

		//...
		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}
}

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2);
	

}
