#ifndef IKILLABLE_HPP
#define IKILLABLE_HPP

class IKillable
{
public:
	IKillable(bool isAlive);
	IKillable();
	~IKillable();

	void revive();
	void kill();
	bool isAlive(void);

private:
	bool _isAlive;
};

#endif
