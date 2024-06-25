#include "CollisionHandling.h"

#include <iostream> //debugging


namespace
{
	void LinkWall(GameObject& link, GameObject& wall)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->undoMove();
			linkPtr->setPush(true);
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
			linkPtr->setPush(true);
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
				linkPtr->pushBack(getCollisionDirection(link, octorok));
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
				octorokPtr->pushBack(-getCollisionDirection(sword, octorok));
				octorokPtr->setHp(octorokPtr->getHp() - 1);
				swordPtr->setActive(false);
			}
		}
	}

	void OctorokSword(GameObject& octorok, GameObject& sword) {}

	void SwordWall(GameObject& sword, GameObject& wall) {}

	void WallSword(GameObject& wall, GameObject& sword)
	{
		SwordWall(sword, wall);
	}

	void OctoProjectileWall(GameObject& Project, GameObject& wall)
	{
		Projectile* ProjectilePtr = dynamic_cast<Projectile*>(&Project);
		if (ProjectilePtr)
		{
			ProjectilePtr->destroy();
		}
	}

	void WallOctoProjectile(GameObject& wall, GameObject& Projectile)
	{
		OctoProjectileWall(Projectile, wall);
	}

	void OctoProjectileLink(GameObject& project, GameObject& link)
	{
		Projectile* ProjectilePtr = dynamic_cast<Projectile*>(&project);
		if (ProjectilePtr)
		{
			ProjectilePtr->destroy();
		}
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->pushBack(getCollisionDirection(project, link));
			linkPtr->initializeInvincible();
			linkPtr->setHp(linkPtr->getHp() - 1);

		}
	}

	void LinkOctoProjectile(GameObject& link, GameObject& Projectile)
	{
		OctoProjectileLink(Projectile, link);
	}

	void ProjectileOctorok(GameObject& Projectile, GameObject& octorok) {}

	void OctorokProjectile(GameObject& octorok, GameObject& Projectile)
	{
		ProjectileOctorok(Projectile, octorok);
	}

	void LinkSword(GameObject& link, GameObject& sword) {}

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

	void BoulderProjectile(GameObject& boulder, GameObject& project)
	{
		Projectile* ProjectilePtr = dynamic_cast<Projectile*>(&project);
		if (ProjectilePtr)
		{
			Boulder* boulderPtr = dynamic_cast<Boulder*>(&boulder);
			if (boulderPtr)
			{
				ProjectilePtr->destroy();
			}
		}
	}

	void ProjectileBoulder(GameObject& projectile, GameObject& boulder)
	{
		BoulderProjectile(boulder, projectile);
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

	void OctorokPot(GameObject& octorok, GameObject& pot)
	{
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		if (octorokPtr)
		{
			octorokPtr->undoMove();
		}
	}

	void PotOctorok(GameObject& pot, GameObject& octorok)
	{
		OctorokPot(octorok, pot);
	}

	void LinkPigWarrior(GameObject& link, GameObject& pigWarrior)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->undoMove();
			if (linkPtr->isAttacking())
			{
			}
		}
	}

	void PigWarriorLink(GameObject& pigWarrior, GameObject& link)
	{
		LinkPigWarrior(link, pigWarrior);
	}

	void PigWarriorWall(GameObject& pigWarrior, GameObject& wall)
	{
		PigWarrior* pigWarriorPtr = dynamic_cast<PigWarrior*>(&pigWarrior);
		if (pigWarriorPtr)
		{
			pigWarriorPtr->undoMove();
		}
	}

	void WallPigWarrior(GameObject& wall, GameObject& pigWarrior)
	{
		PigWarriorWall(pigWarrior, wall);
	}

	void PigWarriorWater(GameObject& pigWarrior, GameObject& water)
	{
		PigWarrior* pigWarriorPtr = dynamic_cast<PigWarrior*>(&pigWarrior);
		if (pigWarriorPtr)
		{
			pigWarriorPtr->undoMove();
		}
	}

	void WaterPigWarrior(GameObject& water, GameObject& pigWarrior)
	{
		PigWarriorWater(pigWarrior, water);
	}

	void SwordPigWarrior(GameObject& sword, GameObject& pigWarrior) {
		PigWarrior* pigWarriorPtr = dynamic_cast<PigWarrior*>(&pigWarrior);
		Sword* swordPtr = dynamic_cast<Sword*>(&sword);
		if (pigWarriorPtr && swordPtr)
		{
			if (swordPtr->getActive()) {
				pigWarriorPtr->pushBack(-getCollisionDirection(sword, pigWarrior));
				pigWarriorPtr->setHp(pigWarriorPtr->getHp() - 1);
				swordPtr->setActive(false);
			}
		}
	}

	void PigWarriorSword(GameObject& pigWarrior, GameObject& sword)
	{
	}

	void LinkArrowOctorok(GameObject& arrow, GameObject& octorok)
	{
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		LinkArrow* arrowPtr = dynamic_cast<LinkArrow*>(&arrow);
		if (octorokPtr && arrowPtr)
		{	
			octorokPtr->pushBack(-getCollisionDirection(arrow, octorok));
			octorokPtr->setHp(octorokPtr->getHp() - 1);
			arrowPtr->destroy();
		}
	}

	void OctorokLinkArrow(GameObject& octorok, GameObject& arrow)
	{
		LinkArrowOctorok(arrow, octorok);
	}

	void LinkLinkArrow(GameObject& link, GameObject& arrow) {}
	void LinkArrowLink(GameObject& arrow, GameObject& link) {}

	void LinkArrowWall(GameObject& arrow, GameObject& wall)
	{
		LinkArrow* arrowPtr = dynamic_cast<LinkArrow*>(&arrow);
		if (arrowPtr)
		{
			arrowPtr->destroy();
		}
	}

	void ShieldOctorok(GameObject& shield, GameObject& octorok){
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		Shield* shieldPtr = dynamic_cast<Shield*>(&shield);
		sf::Vector2i direction = getCollisionDirection(shield, octorok);
		if (octorokPtr && shieldPtr)
		{
			octorokPtr->pushBack(-direction);
			shieldPtr->pushBack(direction);
		}
	}

	void OctorokShield(GameObject& octorok, GameObject& shield){
		ShieldOctorok(shield, octorok);
	}

	void ShieldProjectile(GameObject& shield, GameObject& projectile){
		Projectile* ProjectilePtr = dynamic_cast<Projectile*>(&projectile);
		Shield* shieldPtr = dynamic_cast<Shield*>(&shield);
		sf::Vector2i direction = getCollisionDirection(shield, projectile);
		if (ProjectilePtr && shieldPtr)
		{
			ProjectilePtr->setDirection(direction);
		}
	}
	void ProjectileShield(GameObject& projectile, GameObject& shield){
		ShieldProjectile(shield, projectile);
	}


	void WallLinkArrow(GameObject& wall, GameObject& arrow) 
	{
		LinkArrowWall(arrow, wall);
	}

	void LinkDoor(GameObject& link, GameObject& door)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		Door* doorPtr = dynamic_cast<Door*>(&door);
		if (doorPtr)
		{
			doorPtr->setChangeLevel(true);
			auto pos = doorPtr->getLinkOutPosition();
			if (linkPtr)
			{
				linkPtr->setPosition(pos);
				linkPtr->getSprite().setPosition(pos);
			}
		}
	}

	void DoorLink(GameObject& door, GameObject& link)
	{
		LinkDoor(link, door);
	}

	void LinkSwordItem(GameObject& link, GameObject& swordItem)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		SwordItem* swordItemPtr = dynamic_cast<SwordItem*>(&swordItem);
		if(swordItemPtr && linkPtr){
			linkPtr->takeSword();
			swordItemPtr->destroy();
		}
		
	}
	
	void LinkBowItem(GameObject& link, GameObject& bowItem)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		BowItem* bowItemPtr = dynamic_cast<BowItem*>(&bowItem);
		if(bowItemPtr && linkPtr){
			linkPtr->takeBow();
			bowItemPtr->destroy();
		}
	}

	void OctorokOctorok(GameObject& octorok1, GameObject& octorok2) {}

	void LinkHeart(GameObject& link, GameObject& heart)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		Heart* heartPtr = dynamic_cast<Heart*>(&heart);
		if (linkPtr && heartPtr)
		{
			if (linkPtr->getHp() < MAX_HEALTH)
			{
				linkPtr->setHp(linkPtr->getHp() + 1);
				heartPtr->destroy();
			}
		}
	}

	void HeartLink(GameObject& heart, GameObject& link)
	{
		LinkHeart(link, heart);
	}

	void BoulderBoulder(GameObject& boulder1, GameObject& boulder2)
	{
		Boulder* boulderPtr = dynamic_cast<Boulder*>(&boulder1);
		Boulder* boulderPtr2 = dynamic_cast<Boulder*>(&boulder2);
		if (boulderPtr && boulderPtr2)
		{
			boulderPtr->undoMove();
			boulderPtr2->undoMove();
		}
	}

	using HitFunctionPtr = void (*)(GameObject&, GameObject&);
	// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	// std::unordered_map is better, but it requires defining good hash function for pair
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Link), typeid(Wall))] =					&LinkWall;
		phm[Key(typeid(Link), typeid(Pot))] =					&LinkPot;
		phm[Key(typeid(Link), typeid(WaterTile))] =				&LinkWater;
		phm[Key(typeid(Link), typeid(Octorok))] =				&LinkOctorok;
		phm[Key(typeid(Link), typeid(Projectile))] =			&LinkOctoProjectile;
		phm[Key(typeid(Link), typeid(Sword))] =					&LinkSword;
		phm[Key(typeid(Link), typeid(Boulder))] =				&LinkBoulder;
		phm[Key(typeid(Link), typeid(PigWarrior))] =			&LinkPigWarrior;
		phm[Key(typeid(Link), typeid(LinkArrow))] =				&LinkLinkArrow;
		phm[Key(typeid(Link), typeid(Door))] =					&LinkDoor;
		phm[Key(typeid(Link), typeid(SwordItem))] =				&LinkSwordItem;
		phm[Key(typeid(Link), typeid(BowItem))] =				&LinkBowItem;
		phm[Key(typeid(Link), typeid(Heart))] =					&LinkHeart;
		phm[Key(typeid(Wall), typeid(Link))] =					&WallLink;
		phm[Key(typeid(Wall), typeid(Octorok))] =				&WallOctorok;
		phm[Key(typeid(Wall), typeid(Projectile))] =			&WallOctoProjectile;
		phm[Key(typeid(Wall), typeid(Sword))] =					&WallSword;
		phm[Key(typeid(Wall), typeid(Boulder))] =				&WallBoulder;
		phm[Key(typeid(Wall), typeid(PigWarrior))] =			&WallPigWarrior;
		phm[Key(typeid(Wall), typeid(LinkArrow))] =				&WallLinkArrow;
		phm[Key(typeid(Wall), typeid(LinkArrow))] =				&WallLinkArrow;
		phm[Key(typeid(Pot), typeid(Link))] =					&PotLink;
		phm[Key(typeid(Pot), typeid(Sword))] =					&PotSword;
		phm[Key(typeid(Pot), typeid(Octorok))] =				&PotOctorok;
		phm[Key(typeid(WaterTile), typeid(Link))] =				&WaterLink;
		phm[Key(typeid(WaterTile), typeid(Octorok))] =			&WaterOctorok;
		phm[Key(typeid(WaterTile), typeid(PigWarrior))] =		&WaterPigWarrior;
		phm[Key(typeid(Octorok), typeid(Link))] =				&OctorokLink;
		phm[Key(typeid(Octorok), typeid(Wall))] =				&OctorokWall;
		phm[Key(typeid(Octorok), typeid(WaterTile))] =			&OctorokWater;
		phm[Key(typeid(Octorok), typeid(Sword))] =				&OctorokSword;
		phm[Key(typeid(Octorok), typeid(Projectile))] =			&OctorokProjectile;
		phm[Key(typeid(Octorok), typeid(Boulder))] =			&OctorockBoulder;
		phm[Key(typeid(Octorok), typeid(Pot))] =				&OctorokPot;
		phm[Key(typeid(Octorok), typeid(LinkArrow))] =			&OctorokLinkArrow;
		phm[Key(typeid(Octorok), typeid(Shield))] =				&OctorokShield;
		phm[Key(typeid(Octorok), typeid(Octorok))] =			&OctorokOctorok;
		phm[Key(typeid(Sword), typeid(Octorok))] =				&SwordOctorok;
		phm[Key(typeid(Sword), typeid(Wall))] =					&SwordWall;
		phm[Key(typeid(Sword), typeid(Link))] =					&SwordLink;
		phm[Key(typeid(Sword), typeid(Pot))] =					&SwordPot;
		phm[Key(typeid(Sword), typeid(PigWarrior))] =			&SwordPigWarrior;
		phm[Key(typeid(Shield), typeid(Octorok))] =				&ShieldOctorok;
		phm[Key(typeid(Shield), typeid(Projectile))] =			&ShieldProjectile;
		phm[Key(typeid(Projectile), typeid(Wall))] =			&OctoProjectileWall;
		phm[Key(typeid(Projectile), typeid(Link))] =			&OctoProjectileLink;
		phm[Key(typeid(Projectile), typeid(Octorok))] =			&ProjectileOctorok;
		phm[Key(typeid(Projectile), typeid(Boulder))] =			&ProjectileBoulder;
		phm[Key(typeid(Projectile), typeid(Shield))] =			&ProjectileShield;
		phm[Key(typeid(Boulder), typeid(Link))] =				&BoulderLink;
		phm[Key(typeid(Boulder), typeid(Wall))] =				&BoulderWall;
		phm[Key(typeid(Boulder), typeid(Octorok))] =			&BoulderOctorok;
		phm[Key(typeid(Boulder), typeid(Projectile))] =			&BoulderProjectile;
		phm[Key(typeid(Boulder), typeid(Boulder))] =			&BoulderBoulder;
		phm[Key(typeid(PigWarrior), typeid(Link))] =			&PigWarriorLink;
		phm[Key(typeid(PigWarrior), typeid(Wall))] =			&PigWarriorWall;
		phm[Key(typeid(PigWarrior), typeid(WaterTile))] =		&PigWarriorWater;
		phm[Key(typeid(PigWarrior), typeid(Sword))] =			&PigWarriorSword;
		phm[Key(typeid(LinkArrow), typeid(Octorok))] =			&LinkArrowOctorok;
		phm[Key(typeid(LinkArrow), typeid(Link))] =				&LinkArrowLink;
		phm[Key(typeid(LinkArrow), typeid(Wall))] =				&LinkArrowWall;
		phm[Key(typeid(Door), typeid(Link))] =					&DoorLink;
		phm[Key(typeid(Heart), typeid(Link))] =					&HeartLink;

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

sf::Vector2i getCollisionDirection(GameObject& a, GameObject& b){
    sf::Vector2f pos1 = a.getPosition();
    sf::Vector2f pos2 = b.getPosition();

    // Calculate the vector from object1 to object2
    sf::Vector2f direction = pos2 - pos1;

    // Normalize the direction vector
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) {
        direction.x /= length;
        direction.y /= length;
    }

    // Convert to sf::Vector2i with values -1, 0, or 1
    sf::Vector2i intDirection(static_cast<int>(std::round(direction.x)), static_cast<int>(std::round(direction.y)));

    return intDirection;
}
