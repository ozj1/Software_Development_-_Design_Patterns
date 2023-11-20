#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

struct Character {// a character with name and x and y position will be subjected to move and undo move
    int x;
    int y;
    std::string name;
    Character(std::string _name) : name(_name) {
    }
    void move(int _x, int _y) {
        x = _x;
        y = _y;
    }
};
//here we implement the command pattern
class Command {
public:
    virtual ~Command() {}
    //we have two pure virtual functions they must be implemented in the derived classes
    virtual void execute(Character& c) = 0;
    virtual void undo(Character& c) = 0;
};
//here we model the command and inherit from it
//here move is a type of command
class Move : public Command {
public:
    void execute(Character& c) {
        int randomx = rand() % 4;
        int randomy = rand() % 4;
        c.move(randomx, randomy);
        std::cout << c.name << " moved " << c.x << "," << c.y << std::endl;
    }
    void undo(Character& c) {

        std::cout << c.name << " undo " << -c.x << "," << -c.y << std::endl;
    }

};

int main() {
    srand(time(NULL));
    //a vector where I store all the commands
    std::vector<Command*> command_queue;

    Move* m1 = new Move;
    command_queue.push_back(m1);
    Move* m2 = new Move;
    command_queue.push_back(m2);
    Move* m3 = new Move;
    command_queue.push_back(m3);
    Move* m4 = new Move;
    command_queue.push_back(m4);

    std::vector<Character> s;
    s.push_back(Character("Mike"));
    s.push_back(Character("Gorge"));
    s.push_back(Character("Bryan"));
    s.push_back(Character("Andrew"));

    for (int i = 0; i < command_queue.size(); i++) {
        command_queue[i]->execute(s[i]);
    }

    for (int i = command_queue.size() - 1; i > -1; i--) {
        command_queue[i]->undo(s[i]);
    }

    // And of course some cleanup...
    for (int i = 0; i < command_queue.size(); i++) {
        delete command_queue[i];
    }

    return 0;
}