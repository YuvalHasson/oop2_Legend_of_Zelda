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
				linkPtr->pushBack();
				linkPtr->initializeInvincible();
				linkPtr->setHp(linkPtr->getHp() - 1);
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
				swordPtr->setActive(false);
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

	void OctoProjectileLink(GameObject& octorokProjectile, GameObject& link)
	{
		OctorokProjectile* octorokProjectilePtr = dynamic_cast<OctorokProjectile*>(&octorokProjectile);
		if (octorokProjectilePtr)
		{
			octorokProjectilePtr->destroy();
		}
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->pushBack();
			linkPtr->initializeInvincible();
			linkPtr->setHp(linkPtr->getHp() - 1);

		}
	}

	void LinkOctoProjectile(GameObject& link, GameObject& octorokProjectile)
	{
		OctoProjectileLink(octorokProjectile, link);
	}

	void OctorokProjectileOctorok(GameObject& octorokProjectile, GameObject& octorok)
	{
	}

	void OctorokOctorokProjectile(GameObject& octorok, GameObject& octorokProjectile)
	{
		OctorokProjectileOctorok(octorokProjectile, octorok);
	}

	void LinkSword(GameObject& link, GameObject& sword)
	{
	}

	void SwordLink(GameObject& sword, GameObject& link)
	{
		LinkSword(link, sword);
	}

	void LinkBoulder(GameObject& link, GameObject& boulder)
	{
		Boulder* boulderPtr = dynamic_cast<Boulder*>(&boulder);
		if (boulderPtr)
		{
			Link* linkPtr = dynamic_cast<Link*>(&link);
			if (linkPtr)
			{
				linkPtr->undoMove();
				if (linkPtr->getDirection() == DIRECTIONS::Up    ||
					linkPtr->getDirection() == DIRECTIONS::Down  || 
					linkPtr->getDirection() == DIRECTIONS::Left  || 
					linkPtr->getDirection() == DIRECTIONS::Right)
				{
					linkPtr->setPush(true);
					boulderPtr->setDirection(linkPtr->getDirection());
					boulderPtr->move();
				}
			}
		}
	}

	void BoulderLink(GameObject& boulder, GameObject& link)
	{
		LinkBoulder(link, boulder);
	}

	void BoulderWall(GameObject& boulder, GameObject& wall)
	{
		Boulder* boulderPtr = dynamic_cast<Boulder*>(&boulder);
		if (boulderPtr)
		{
			boulderPtr->undoMove();
		}
	}

	void WallBoulder(GameObject& wall, GameObject& boulder)
	{
		BoulderWall(boulder, wall);
	}

	void OctorockBoulder(GameObject& octorok, GameObject& boulder)
	{
		Boulder* boulderPtr = dynamic_cast<Boulder*>(&boulder);
		if (boulderPtr)
		{
			Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
			if (octorokPtr)
			{
				boulderPtr->setSpeed(0.f);
				octorokPtr->undoMove();
			}
		}
	}

	void BoulderOctorok(GameObject& boulder, GameObject& octorok)
	{
		OctorockBoulder(octorok, boulder);
	}

	void BoulderOctorokProjectile(GameObject& boulder, GameObject& octorokProjectile)
	{
		OctorokProjectile* octorokProjectilePtr = dynamic_cast<OctorokProjectile*>(&octorokProjectile);
		if (octorokProjectilePtr)
		{
			Boulder* boulderPtr = dynamic_cast<Boulder*>(&boulder);
			if (boulderPtr)
			{
				octorokProjectilePtr->destroy();
			}
		}
	}

	void OctorokProjectileBoulder(GameObject& octorokProjectile, GameObject& boulder)
	{
		BoulderOctorokProjectile(boulder, octorokProjectile);
	}

	void SwordPot(GameObject& sword, GameObject& pot)
	{
		Pot* potPtr = dynamic_cast<Pot*>(&pot);
		Sword* swordPtr = dynamic_cast<Sword*>(&sword);
		if (potPtr && swordPtr)
		{
			if (swordPtr->getActive()) {
				potPtr->destroy();
				swordPtr->setActive(false);
			}
		}
	}

	void PotSword(GameObject& pot, GameObject& sword)
	{
		SwordPot(sword, pot);
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
		phm[Key(typeid(Link), typeid(WaterTile))] = &LinkWater;
		phm[Key(typeid(Link), typeid(Octorok))] = &LinkOctorok;
		phm[Key(typeid(Link), typeid(OctorokProjectile))] = &LinkOctoProjectile;
		phm[Key(typeid(Link), typeid(Sword))] = &LinkSword;
		phm[Key(typeid(Link), typeid(Boulder))] = &LinkBoulder;
		phm[Key(typeid(Wall), typeid(Link))] = &WallLink; // ==> wall to link collision
		phm[Key(typeid(Wall), typeid(Octorok))] = &WallOctorok;
		phm[Key(typeid(Wall), typeid(OctorokProjectile))] = &WallOctoProjectile;
		phm[Key(typeid(Wall), typeid(Sword))] = &WallSword;
		phm[Key(typeid(Wall), typeid(Boulder))] = &WallBoulder;
		phm[Key(typeid(Pot), typeid(Link))] = &PotLink; // ==> Pot to link collision
		phm[Key(typeid(Pot), typeid(Sword))] = &PotSword;
		phm[Key(typeid(WaterTile), typeid(Link))] = &WaterLink;
		phm[Key(typeid(WaterTile), typeid(Octorok))] = &WaterOctorok;
		phm[Key(typeid(Octorok), typeid(Link))] = &OctorokLink;
		phm[Key(typeid(Octorok), typeid(Wall))] = &OctorokWall;
		phm[Key(typeid(Octorok), typeid(WaterTile))] = &OctorokWater;
		phm[Key(typeid(Octorok), typeid(Sword))] = &OctorokSword;
		phm[Key(typeid(Octorok), typeid(OctorokProjectile))] = &OctorokOctorokProjectile;
		phm[Key(typeid(Octorok), typeid(Boulder))] = &OctorockBoulder;
		phm[Key(typeid(Sword), typeid(Octorok))] = &SwordOctorok;
		phm[Key(typeid(Sword), typeid(Wall))] = &SwordWall;
		phm[Key(typeid(Sword), typeid(Link))] = &SwordLink;
		phm[Key(typeid(Sword), typeid(Pot))] = &SwordPot;
		phm[Key(typeid(OctorokProjectile), typeid(Wall))] = &OctoProjectileWall;
		phm[Key(typeid(OctorokProjectile), typeid(Link))] = &OctoProjectileLink;
		phm[Key(typeid(OctorokProjectile), typeid(Octorok))] = &OctorokProjectileOctorok;
		phm[Key(typeid(OctorokProjectile), typeid(Boulder))] = &OctorokProjectileBoulder;
		phm[Key(typeid(Boulder), typeid(Link))] = &BoulderLink;
		phm[Key(typeid(Boulder), typeid(Wall))] = &BoulderWall;
		phm[Key(typeid(Boulder), typeid(Octorok))] = &BoulderOctorok;
		phm[Key(typeid(Boulder), typeid(OctorokProjectile))] = &BoulderOctorokProjectile;


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
