#include "Octorok.h"
#include "OctorokState.h"

class OctorokAttackState : public OctorokState
{
public:
	OctorokAttackState();
	virtual std::unique_ptr<OctorokState> handleInput(Input) override;
	virtual void enter(Octorok&) override;
private:
	sf::Clock m_attackTimer;
	sf::Time m_attackDuration;
	bool m_isAnimationSet;
};