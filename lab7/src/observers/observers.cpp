#include "observers.hpp"

TextObserver::TextObserver() {}

ptr<FightObserver> TextObserver::get() {
    static TextObserver instance;
    return ptr<FightObserver>(&instance, [](FightObserver *) {});
}

void TextObserver::on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) {
    std::cout << std::endl << "The murder took place." << std::endl;
    std::cout << "Killer: ";
    attacker->print();
    std::cout << "Victim: ";
    defender->print();
    std::cout << '\n';
}


FileObserver::FileObserver() {}

ptr<FightObserver> FileObserver::get() {
    static FileObserver instance;
    return ptr<FightObserver>(&instance, [](FightObserver *) {});
}

void FileObserver::on_fight(const ptr<NPC> attacker, const ptr<NPC> defender) {
    std::ofstream fs("log.txt", std::ios::app);
    fs << '\n'
       << "The murder took place." << '\n'
       << "Killer: " << *attacker << '\n'
       << "Victim: " << *defender << '\n';
    fs.close();
}
