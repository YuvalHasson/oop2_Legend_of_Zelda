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
			linkPtr->resetTimeSinceLastPushed();
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

	void ProjectileWall(GameObject& project, GameObject& wall)
	{
		Projectile* ProjectilePtr = dynamic_cast<Projectile*>(&project);
		if (ProjectilePtr)
		{
			ProjectilePtr->destroy();
		}
	}

	void WallProjectile(GameObject& wall, GameObject& projectile)
	{
		ProjectileWall(projectile, wall);
	}

	void ProjectileLink(GameObject& project, GameObject& link)
	{
		Projectile* ProjectilePtr = dynamic_cast<Projectile*>(&project);
		if (ProjectilePtr)
		{
			ProjectilePtr->destroy();
		}
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (linkPtr)
		{
			linkPtr->pushBack(-getCollisionDirection(project, link));
			linkPtr->initializeInvincible();
			linkPtr->setHp(linkPtr->getHp() - 1);

		}
	}

	void LinkProjectile(GameObject& link, GameObject& projectile)
	{
		ProjectileLink(projectile, link);
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
					linkPtr->resetTimeSinceLastPushed();
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
				boulderPtr->setSpeed(0);
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
		PigWarrior* pigWarriorPtr = dynamic_cast<PigWarrior*>(&pigWarrior);
		if (linkPtr)
		{
			if (!linkPtr->getInvincible()) {
				linkPtr->pushBack(getCollisionDirection(link, pigWarrior));
				linkPtr->initializeInvincible();
				linkPtr->setHp(linkPtr->getHp() - 1);
				pigWarriorPtr->undoMove();
			}
			pigWarriorPtr->undoMove();
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

	void PigWarriorSword(GameObject& pigWarrior, GameObject& sword){}

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
	void LinkArrowPigWarrior(GameObject& arrow, GameObject& pigWarrior)
	{
		PigWarrior* pigWarriorPtr = dynamic_cast<PigWarrior*>(&pigWarrior);
		LinkArrow* arrowPtr = dynamic_cast<LinkArrow*>(&arrow);
		if (pigWarriorPtr && arrowPtr)
		{
			pigWarriorPtr->pushBack(-getCollisionDirection(arrow, pigWarrior));
			pigWarriorPtr->setHp(pigWarriorPtr->getHp() - 1);
			arrowPtr->destroy();
		}
	}

	void PigWarriorLinkArrow(GameObject& pigWarrior, GameObject& arrow)
	{
		LinkArrowPigWarrior(arrow, pigWarrior);
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

	void BoulderPot(GameObject& boulder, GameObject& pot)
	{
		Boulder* boulderPtr = dynamic_cast<Boulder*>(&boulder);
		Pot* potPtr = dynamic_cast<Pot*>(&pot);
		if (boulderPtr && potPtr)
		{
			boulderPtr->undoMove();
		}
	}

	void PotBoulder(GameObject& pot, GameObject& boulder)
	{
		BoulderPot(boulder, pot);
	}

	void EnemySwordWall(GameObject& enemySword, GameObject& wall) {}

	void WallEnemySword(GameObject& wall, GameObject& enemySword)
	{
		EnemySwordWall(enemySword, wall);
	}

	void EnemySwordLink(GameObject& enemySword, GameObject& link)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		EnemySword* enemySwordPtr = dynamic_cast<EnemySword*>(&enemySword);
		if (linkPtr && enemySwordPtr)
		{
			if (!linkPtr->getInvincible()) {
				linkPtr->pushBack(getCollisionDirection(link, enemySword));
				linkPtr->initializeInvincible();
				linkPtr->setHp(linkPtr->getHp() - 1);
			}
		}
	}

	void PigWarriorEnemySword(GameObject& pigWarrior, GameObject& enemySword) {}

	void EnemySwordPigWarrior(GameObject& enemySword, GameObject& pigWarrior)
	{
		PigWarriorEnemySword(pigWarrior, enemySword);
	}

	void EnemySwordWater(GameObject& enemySword, GameObject& water) {}

	void WaterEnemySword(GameObject& water, GameObject& enemySword)
	{
		EnemySwordWater(enemySword, water);
	}

	void LinkEnemySword(GameObject& link, GameObject& enemySword)
	{
		EnemySwordLink(enemySword, link);
	}

	void ShieldEnemySword(GameObject& shield, GameObject& enemySword)
	{
		Shield* shieldPtr = dynamic_cast<Shield*>(&shield);
		EnemySword* enemySwordPtr = dynamic_cast<EnemySword*>(&enemySword);
		if (shieldPtr && enemySwordPtr)
		{
			shieldPtr->pushBack(getCollisionDirection(shield, enemySword));
		}
	}

	void EnemySwordShield(GameObject& enemySword, GameObject& shield)
	{
		ShieldEnemySword(shield, enemySword);
	}

	void ShieldPigWarrior(GameObject& shield, GameObject& pigWarrior)
	{
		Shield* shieldPtr = dynamic_cast<Shield*>(&shield);
		PigWarrior* pigWarriorPtr = dynamic_cast<PigWarrior*>(&pigWarrior);
		if (shieldPtr && pigWarriorPtr)
		{
			shieldPtr->pushBack(getCollisionDirection(shield, pigWarrior));
			pigWarriorPtr->pushBack(-getCollisionDirection(shield, pigWarrior));
		}
	}

	void PigWarriorShield(GameObject& pigWarrior, GameObject& shield)
	{
		ShieldPigWarrior(shield, pigWarrior);
	}

	void ShieldSeaUrchin(GameObject& shield, GameObject& seaUrchin)
	{
		Shield* shieldPtr = dynamic_cast<Shield*>(&shield);
		SeaUrchin* seaUrchinPtr = dynamic_cast<SeaUrchin*>(&seaUrchin);
		if (shieldPtr && seaUrchinPtr)
		{
			seaUrchinPtr->setDirection(shieldPtr->getLinkDirection());
			seaUrchinPtr->move();
		}
	}

	void SeaUrchinShield(GameObject& seaUrchin, GameObject& shield)
	{
		ShieldSeaUrchin(shield, seaUrchin);
	}

	void SeaUrchinLink(GameObject& seaUrchin, GameObject& link)
	{
		SeaUrchin* seaUrchinPtr = dynamic_cast<SeaUrchin*>(&seaUrchin);
		Link* linkPtr = dynamic_cast<Link*>(&link);
		if (seaUrchinPtr && linkPtr)
		{
			if (!linkPtr->getInvincible())
			{
				linkPtr->pushBack(getCollisionDirection(link, seaUrchin));
				linkPtr->initializeInvincible();
				linkPtr->setHp(linkPtr->getHp() - 1);
			}
			linkPtr->undoMove();
		}
	}

	void LinkSeaUrchin(GameObject& link, GameObject& seaUrchin)
	{
		SeaUrchinLink(seaUrchin, link);
	}

	void SeaUrchinWall(GameObject& seaUrchin, GameObject& wall)
	{
		SeaUrchin* seaUrchinPtr = dynamic_cast<SeaUrchin*>(&seaUrchin);
		if (seaUrchinPtr)
		{
			seaUrchinPtr->undoMove();
		}
	}

	void WallSeaUrchin(GameObject& wall, GameObject& seaUrchin)
	{
		SeaUrchinWall(seaUrchin, wall);
	}

	void SeaUrchinWater(GameObject& seaUrchin, GameObject& water)
	{
		SeaUrchin* seaUrchinPtr = dynamic_cast<SeaUrchin*>(&seaUrchin);
		if (seaUrchinPtr)
		{
			seaUrchinPtr->undoMove();
		}
	}

	void WaterSeaUrchin(GameObject& water, GameObject& seaUrchin)
	{
		SeaUrchinWater(seaUrchin, water);
	}

	void SeaUrchinSeaUrchin(GameObject& seaUrchin1, GameObject& seaUrchin2)
	{
		SeaUrchin* seaUrchinPtr1 = dynamic_cast<SeaUrchin*>(&seaUrchin1);
		SeaUrchin* seaUrchinPtr2 = dynamic_cast<SeaUrchin*>(&seaUrchin2);

		if (seaUrchinPtr1 && seaUrchinPtr2)
		{
			seaUrchinPtr1->undoMove();
			seaUrchinPtr2->undoMove();
		}
	}

	void ProjectileProjectile(GameObject& projectile1, GameObject& projectile2) {}

	void OctorokPigWarrior(GameObject& octorok, GameObject& pigWarrior) {}

	void PigWarriorOctorok(GameObject& pigWarrior, GameObject& octorok) {}

	void OctorokEnemySword(GameObject& octorok, GameObject& enemySword) {}

	void EnemySwordOctorok(GameObject& enemySword, GameObject& octorok) {}

	void PigWarriorProjectile(GameObject& pigWarrior, GameObject& projectile) {}

	void ProjectilePigWarrior(GameObject& projectile, GameObject& pigWarrior) {}

	void PigWarriorPigWarrior(GameObject& pigWarrior1, GameObject& pigWarrior2) {}

	void ShieldBoulder(GameObject& shield, GameObject& boulder) {}

	void BoulderShield(GameObject& boulder, GameObject& shield)
	{
		ShieldBoulder(shield, boulder);
	}

	void SwordSeaUrchin(GameObject& sword, GameObject& seaUrchin) 
	{
		Sword* swordPtr = dynamic_cast<Sword*>(&sword);
		SeaUrchin* seaUrchinPtr = dynamic_cast<SeaUrchin*>(&seaUrchin);
		if (swordPtr && seaUrchinPtr)
		{
			if (swordPtr->getActive()) {
				seaUrchinPtr->setHp(seaUrchinPtr->getHp() - 1);
				swordPtr->setActive(false);
			}
		}
	}

	void SeaUrchinSword(GameObject& seaUrchin, GameObject& sword)
	{
		SwordSeaUrchin(sword, seaUrchin);
	}

	void ProjectileWater(GameObject& projectile, GameObject& water) {}

	void WaterProjectile(GameObject& water, GameObject& projectile) {}

	void SeaUrchinProjectile(GameObject& seaUrchin, GameObject& projectile) {}

	void ProjectileSeaUrchin(GameObject& projectile, GameObject& seaUrchin) {}

	void SeaUrchinOctorok(GameObject& seaUrchin, GameObject& octorok) {}

	void OctorokSeaUrchin(GameObject& octorok, GameObject& seaUrchin) {}

	void SignLink(GameObject& sign, GameObject& link)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		Sign* signPtr = dynamic_cast<Sign*>(&sign);
		if (linkPtr && signPtr)
		{
			if (signPtr->getInnerBox(linkPtr->getHitBox())) {
				linkPtr->undoMove();
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			{
				signPtr->setActive(true);
			}
			else {
				signPtr->setActive(false);
			}
		}
	}

	void LinkSign(GameObject& link, GameObject& sign)
	{
		SignLink(sign, link);
	}

	void SignOctorok(GameObject& sign, GameObject& octorok)
	{
		Sign* signPtr = dynamic_cast<Sign*>(&sign);
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		if (signPtr && octorokPtr)
		{
			if (signPtr->getInnerBox(octorokPtr->getHitBox())) {
				octorokPtr->undoMove();
			}
		}

	}

	void OctorokSign(GameObject& octorok, GameObject& sign)
	{
		SignOctorok(sign, octorok);
	}

	void LinkHole(GameObject& link, GameObject& hole)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		Hole* holePtr = dynamic_cast<Hole*>(&hole);
		if (linkPtr && holePtr)
		{
			if (!linkPtr->getInvincible())
			{
				linkPtr->pushBack(getCollisionDirection(link, hole));
				linkPtr->initializeInvincible();
				linkPtr->setHp(linkPtr->getHp() - 1);
			}
			linkPtr->undoMove();
		}
	}

	void HoleLink(GameObject& hole, GameObject& link)
	{
		LinkHole(link, hole);
	}

	void LinkShrub(GameObject& link, GameObject& shrub)
	{
		Link* linkPtr = dynamic_cast<Link*>(&link);
		Shrub* shrubPtr = dynamic_cast<Shrub*>(&shrub);
		if (linkPtr && shrubPtr)
		{
			linkPtr->setSpeed(0.5f);
		}
	}

	void ShrubLink(GameObject& shrub, GameObject& link)
	{
		LinkShrub(link, shrub);
	}

	void SwordShrub(GameObject& sword, GameObject& shrub)
	{
		Sword* swordPtr = dynamic_cast<Sword*>(&sword);
		Shrub* shrubPtr = dynamic_cast<Shrub*>(&shrub);
		if (swordPtr && shrubPtr)
		{
			if (swordPtr->getActive()) {
				shrubPtr->destroy();
				swordPtr->setActive(false);
			}
		}
	}

	void ShrubSword(GameObject& shrub, GameObject& sword)
	{
		SwordShrub(sword, shrub);
	}

	void octorokShrub(GameObject& octorok, GameObject& shrub)
	{
		Octorok* octorokPtr = dynamic_cast<Octorok*>(&octorok);
		Shrub* shrubPtr = dynamic_cast<Shrub*>(&shrub);
		if (octorokPtr && shrubPtr)
		{
			octorokPtr->setSpeed(0.5f);
		}
	}

	void ShrubOctorok(GameObject& shrub, GameObject& octorok)
	{
		octorokShrub(octorok, shrub);
	}

	void PigWarriorShrub(GameObject& pigWarrior, GameObject& shrub)
	{
		PigWarrior* pigWarriorPtr = dynamic_cast<PigWarrior*>(&pigWarrior);
		Shrub* shrubPtr = dynamic_cast<Shrub*>(&shrub);
		if (pigWarriorPtr && shrubPtr)
		{
			pigWarriorPtr->setSpeed(0.5f);
		}
	}

	void ShrubPigWarrior(GameObject& shrub, GameObject& pigWarrior)
	{
		PigWarriorShrub(pigWarrior, shrub);
	}

	void ProjectileShrub(GameObject& projectile, GameObject& shrub) {}

	void ShrubProjectile(GameObject& shrub, GameObject& projectile) {}

	void ShrubEnemySword(GameObject& shrub, GameObject& enemySword) {}

	void EnemySwordShrub(GameObject& enemySword, GameObject& shrub) {}

	//...

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
		phm[Key(typeid(Link), typeid(Projectile))] =			&LinkProjectile;
		phm[Key(typeid(Link), typeid(Sword))] =					&LinkSword;
		phm[Key(typeid(Link), typeid(Boulder))] =				&LinkBoulder;
		phm[Key(typeid(Link), typeid(PigWarrior))] =			&LinkPigWarrior;
		phm[Key(typeid(Link), typeid(LinkArrow))] =				&LinkLinkArrow;
		phm[Key(typeid(Link), typeid(Door))] =					&LinkDoor;
		phm[Key(typeid(Link), typeid(SwordItem))] =				&LinkSwordItem;
		phm[Key(typeid(Link), typeid(BowItem))] =				&LinkBowItem;
		phm[Key(typeid(Link), typeid(Heart))] =					&LinkHeart;
		phm[Key(typeid(Link), typeid(EnemySword))] =			&LinkEnemySword;
		phm[Key(typeid(Link), typeid(SeaUrchin))] =				&LinkSeaUrchin;
		phm[Key(typeid(Link), typeid(Sign))] =					&LinkSign;
		phm[Key(typeid(Link), typeid(Hole))] =					&LinkHole;
		phm[Key(typeid(Link), typeid(Shrub))] =					&LinkShrub;
		phm[Key(typeid(Wall), typeid(Link))] =					&WallLink;
		phm[Key(typeid(Wall), typeid(Octorok))] =				&WallOctorok;
		phm[Key(typeid(Wall), typeid(Projectile))] =			&WallProjectile;
		phm[Key(typeid(Wall), typeid(Sword))] =					&WallSword;
		phm[Key(typeid(Wall), typeid(Boulder))] =				&WallBoulder;
		phm[Key(typeid(Wall), typeid(PigWarrior))] =			&WallPigWarrior;
		phm[Key(typeid(Wall), typeid(LinkArrow))] =				&WallLinkArrow;
		phm[Key(typeid(Wall), typeid(LinkArrow))] =				&WallLinkArrow;
		phm[Key(typeid(Wall), typeid(EnemySword))] =			&WallEnemySword;
		phm[Key(typeid(Wall), typeid(SeaUrchin))] =				&WallSeaUrchin; 
		phm[Key(typeid(Pot), typeid(Link))] =					&PotLink;
		phm[Key(typeid(Pot), typeid(Sword))] =					&PotSword;
		phm[Key(typeid(Pot), typeid(Octorok))] =				&PotOctorok;
		phm[Key(typeid(Pot), typeid(Boulder))] =				&PotBoulder;
		phm[Key(typeid(WaterTile), typeid(Link))] =				&WaterLink;
		phm[Key(typeid(WaterTile), typeid(Octorok))] =			&WaterOctorok;
		phm[Key(typeid(WaterTile), typeid(PigWarrior))] =		&WaterPigWarrior;
		phm[Key(typeid(WaterTile), typeid(EnemySword))] =		&WaterEnemySword;
		phm[Key(typeid(WaterTile), typeid(SeaUrchin))] =		&WaterSeaUrchin;
		phm[Key(typeid(WaterTile), typeid(Projectile))] =		&WaterProjectile;
		phm[Key(typeid(Octorok), typeid(Link))] =				&OctorokLink;
		phm[Key(typeid(Octorok), typeid(Wall))] =				&OctorokWall;
		phm[Key(typeid(Octorok), typeid(WaterTile))] =			&OctorokWater;
		phm[Key(typeid(Octorok), typeid(Sword))] =				&OctorokSword;
		phm[Key(typeid(Octorok), typeid(Projectile))] =			&OctorokProjectile;
		phm[Key(typeid(Octorok), typeid(Boulder))] =			&OctorockBoulder;
		phm[Key(typeid(Octorok), typeid(Pot))] =				&OctorokPot;
		phm[Key(typeid(Octorok), typeid(LinkArrow))] =			&OctorokLinkArrow;
		phm[Key(typeid(Octorok), typeid(Shield))] =				&OctorokShield;
		phm[Key(typeid(Octorok), typeid(PigWarrior))] =			&OctorokPigWarrior;
		phm[Key(typeid(Octorok), typeid(EnemySword))] =			&OctorokEnemySword;
		phm[Key(typeid(Octorok), typeid(SeaUrchin))] =			&OctorokSeaUrchin;
		phm[Key(typeid(Octorok), typeid(Sign))] =				&OctorokSign;
		phm[Key(typeid(Octorok), typeid(Shrub))] =				&octorokShrub;
		phm[Key(typeid(Octorok), typeid(Octorok))] =			&OctorokOctorok;
		phm[Key(typeid(Sword), typeid(Octorok))] =				&SwordOctorok;
		phm[Key(typeid(Sword), typeid(Wall))] =					&SwordWall;
		phm[Key(typeid(Sword), typeid(Link))] =					&SwordLink;
		phm[Key(typeid(Sword), typeid(Pot))] =					&SwordPot;
		phm[Key(typeid(Sword), typeid(PigWarrior))] =			&SwordPigWarrior;
		phm[Key(typeid(Sword), typeid(SeaUrchin))] =			&SwordSeaUrchin;
		phm[Key(typeid(Sword), typeid(Shrub))] =				&SwordShrub;
		phm[Key(typeid(Shield), typeid(Octorok))] =				&ShieldOctorok;
		phm[Key(typeid(Shield), typeid(Projectile))] =			&ShieldProjectile;
		phm[Key(typeid(Shield), typeid(PigWarrior))] =			&ShieldPigWarrior;
		phm[Key(typeid(Shield), typeid(EnemySword))] =			&ShieldEnemySword;
		phm[Key(typeid(Shield), typeid(SeaUrchin))] =			&ShieldSeaUrchin;
		phm[Key(typeid(Shield), typeid(Boulder))] =				&ShieldBoulder;
		phm[Key(typeid(Projectile), typeid(Wall))] =			&ProjectileWall;
		phm[Key(typeid(Projectile), typeid(Link))] =			&ProjectileLink;
		phm[Key(typeid(Projectile), typeid(Octorok))] =			&ProjectileOctorok;
		phm[Key(typeid(Projectile), typeid(Boulder))] =			&ProjectileBoulder;
		phm[Key(typeid(Projectile), typeid(Shield))] =			&ProjectileShield;
		phm[Key(typeid(Projectile), typeid(PigWarrior))] =		&ProjectilePigWarrior;
		phm[Key(typeid(Projectile), typeid(Projectile))] =		&ProjectileProjectile;
		phm[Key(typeid(Projectile), typeid(WaterTile))] =		&ProjectileWater;
		phm[Key(typeid(Projectile), typeid(SeaUrchin))] =		&ProjectileSeaUrchin;
		phm[Key(typeid(Projectile), typeid(Shrub))] =		&ProjectileShrub;
		phm[Key(typeid(Boulder), typeid(Link))] =				&BoulderLink;
		phm[Key(typeid(Boulder), typeid(Wall))] =				&BoulderWall;
		phm[Key(typeid(Boulder), typeid(Octorok))] =			&BoulderOctorok;
		phm[Key(typeid(Boulder), typeid(Projectile))] =			&BoulderProjectile;
		phm[Key(typeid(Boulder), typeid(Boulder))] =			&BoulderBoulder;
		phm[Key(typeid(Boulder), typeid(Pot))] =				&BoulderPot;
		phm[Key(typeid(Boulder), typeid(Shield))] =				&BoulderShield;
		phm[Key(typeid(PigWarrior), typeid(Link))] =			&PigWarriorLink;
		phm[Key(typeid(PigWarrior), typeid(Wall))] =			&PigWarriorWall;
		phm[Key(typeid(PigWarrior), typeid(WaterTile))] =		&PigWarriorWater;
		phm[Key(typeid(PigWarrior), typeid(Sword))] =			&PigWarriorSword;
		phm[Key(typeid(PigWarrior), typeid(LinkArrow))] =		&PigWarriorLinkArrow;
		phm[Key(typeid(PigWarrior), typeid(EnemySword))] =		&PigWarriorEnemySword;
		phm[Key(typeid(PigWarrior), typeid(Shield))] =			&PigWarriorShield;
		phm[Key(typeid(PigWarrior), typeid(Octorok))] =			&PigWarriorOctorok;
		phm[Key(typeid(PigWarrior), typeid(Projectile))] =		&PigWarriorProjectile;
		phm[Key(typeid(PigWarrior), typeid(Shrub))] =			&PigWarriorShrub;
		phm[Key(typeid(PigWarrior), typeid(PigWarrior))] =		&PigWarriorPigWarrior;
		phm[Key(typeid(LinkArrow), typeid(Octorok))] =			&LinkArrowOctorok;
		phm[Key(typeid(LinkArrow), typeid(PigWarrior))] =		&LinkArrowPigWarrior;
		phm[Key(typeid(LinkArrow), typeid(Link))] =				&LinkArrowLink;
		phm[Key(typeid(LinkArrow), typeid(Wall))] =				&LinkArrowWall;
		phm[Key(typeid(EnemySword), typeid(Link))] =			&EnemySwordLink;
		phm[Key(typeid(EnemySword), typeid(Wall))] =			&EnemySwordWall;
		phm[Key(typeid(EnemySword), typeid(PigWarrior))] =		&EnemySwordPigWarrior;
		phm[Key(typeid(EnemySword), typeid(WaterTile))] =		&EnemySwordWater;
		phm[Key(typeid(EnemySword), typeid(Shield))] =			&EnemySwordShield;
		phm[Key(typeid(EnemySword), typeid(Octorok))] =			&EnemySwordOctorok;
		phm[Key(typeid(EnemySword), typeid(Shrub))] =			&EnemySwordShrub;
		phm[Key(typeid(SeaUrchin), typeid(Shield))] =			&SeaUrchinShield;
		phm[Key(typeid(SeaUrchin), typeid(Link))] =				&SeaUrchinLink;
		phm[Key(typeid(SeaUrchin), typeid(Wall))] =				&SeaUrchinWall;
		phm[Key(typeid(SeaUrchin), typeid(WaterTile))] =		&SeaUrchinWater;
		phm[Key(typeid(SeaUrchin), typeid(SeaUrchin))] =		&SeaUrchinSeaUrchin;
		phm[Key(typeid(SeaUrchin), typeid(Sword))] =			&SeaUrchinSword;
		phm[Key(typeid(SeaUrchin), typeid(Projectile))] =		&SeaUrchinProjectile;
		phm[Key(typeid(SeaUrchin), typeid(Octorok))] =			&SeaUrchinOctorok;
		phm[Key(typeid(Sign), typeid(Link))] =					&SignLink;
		phm[Key(typeid(Sign), typeid(Octorok))] =				&SignOctorok;
		phm[Key(typeid(Shrub), typeid(Link))] =					&ShrubLink;
		phm[Key(typeid(Shrub), typeid(Sword))] =				&ShrubSword;
		phm[Key(typeid(Shrub), typeid(Octorok))] =				&ShrubOctorok;
		phm[Key(typeid(Shrub), typeid(PigWarrior))] =			&ShrubPigWarrior;
		phm[Key(typeid(Shrub), typeid(EnemySword))] =			&ShrubEnemySword;
		phm[Key(typeid(Shrub), typeid(Projectile))] =			&ShrubProjectile;
		phm[Key(typeid(Door), typeid(Link))] =					&DoorLink;
		phm[Key(typeid(Heart), typeid(Link))] =					&HeartLink;
		phm[Key(typeid(Hole), typeid(Link))] =					&HoleLink;


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
