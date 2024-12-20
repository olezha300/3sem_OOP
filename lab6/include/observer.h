#pragma once

#include "npc.h"

class TextObserver final : public IFightObserver {
public:
    static std::shared_ptr<IFightObserver> get() {
        static TextObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker,
                  const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::cout << std::endl << "The murder took place." << std::endl;
            std::cout << "Killer: ";
            attacker->print();
            std::cout << "Victim: ";
            defender->print();
        }
    }

private:
    TextObserver() {};
};

class FileObserver final : public IFightObserver {
public:
    static std::shared_ptr<IFightObserver> get() {
        static FileObserver instance;
        return std::shared_ptr<IFightObserver>(&instance, [](IFightObserver *) {});
    }

    void on_fight(const std::shared_ptr<NPC> attacker,
                  const std::shared_ptr<NPC> defender, bool win) override {
        if (win) {
            std::ofstream fs("log.txt", std::ios::app);
            fs << std::endl
               << "The murder took place." << std::endl
               << "Killer: " << *attacker << std::endl
               << "Victim: " << *defender;
            fs.close();
        }
    }
private:
    FileObserver() {};
};
