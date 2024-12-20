#ifndef OBSERVERS_HPP
#define OBSERVERS_HPP

#include "npc.hpp"

struct FightObserver {
    virtual void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) = 0;
};

class TextObserver final : public FightObserver {
public:
    static ptr<FightObserver> get();
    void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) override;

private:
    TextObserver();

};

class FileObserver final : public FightObserver {
public:
    static ptr<FightObserver> get();
    void on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) override;

private:
    FileObserver();
};

#endif // OBSERVERS_HPP
