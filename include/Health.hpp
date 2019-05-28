#ifndef ENTITY_HPP
#define ENTITY_HPP

template<typename Parent>
class Health
{
public:
    bool isDead();
    int getHp();
    void setHp(unsigned int val);
    int getMaxHp();
    void setMaxHp();

    int damage(int hpLoss);     // Returns remaining hp 
    virtual void setOnDamage(void (*onDamage)(Parent *self));
    
    int heal(int hpGain); // Return new Hp
    virtual void setOnHeal(void (*onHeal)(Parent *self));

    virtual void setOnDeath(void (*onHeal)(Parent *self));
private:
    int _hp;
    int _maxHp;

    void (*onDamage)(Parent *self);
    void (*onDeath)(Parent *self);
    void (*onHeal)(Parent *self);
};

#endif