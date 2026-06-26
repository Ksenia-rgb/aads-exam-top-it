#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

#include "arguments.h"
#include "database.h"
#include "meeting.h"
#include "commands.h"

using namespace smirnova;

static bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s)
        if (!std::isdigit(c)) return false;
    return true;
}

int main(int argc, char* argv[]) {

    Arguments args;
    if (!parseArguments(argc, argv, args)) {
        std::cerr << "INVALID ARGS\n";
        return 1;
    }

    std::ifstream data(args.dataFile);
    if (!data.is_open()) {
        std::cerr << "CANNOT OPEN DATA\n";
        return 2;
    }

    Database db;
    init(db);

    std::string line;

    while (std::getline(data, line)) {
        Meeting m;
        if (!parseMeeting(line, m)) {
            std::cerr << "<INVALID COMMAND>\n";
            return 3;
        }

        if (m.a != m.b)
            addMeeting(db, m);
    }

    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "anons") anons(db);

        else if (cmd == "desc") {
            std::string id; iss >> id;
            if (isNumber(id)) desc(db, std::stoul(id));
            else std::cerr << "<INVALID COMMAND>\n";
        }

        else if (cmd == "redesc") {
            std::string id; iss >> id;
            std::string d; std::getline(iss, d);
            if (isNumber(id)) redesc(db, std::stoul(id), d);
            else std::cerr << "<INVALID COMMAND>\n";
        }

        else if (cmd == "meets") {
            std::string id; iss >> id;
            if (isNumber(id)) meets(db, std::stoul(id));
            else std::cerr << "<INVALID COMMAND>\n";
        }

        else if (cmd == "commons") {
            std::string a,b; iss >> a >> b;
            if (isNumber(a) && isNumber(b))
                commons(db, std::stoul(a), std::stoul(b));
            else std::cerr << "<INVALID COMMAND>\n";
        }

        else if (cmd == "less") {
            std::string t,id; iss >> t >> id;
            if (isNumber(t) && isNumber(id))
                less(db, std::stoul(t), std::stoul(id));
            else std::cerr << "<INVALID COMMAND>\n";
        }

        else if (cmd == "greater") {
            std::string t,id; iss >> t >> id;
            if (isNumber(t) && isNumber(id))
                greater(db, std::stoul(t), std::stoul(id));
            else std::cerr << "<INVALID COMMAND>\n";
        }

        else if (cmd == "out-persons") {
            std::string f; iss >> f;
            outPersons(db, f);
        }

        else {
            std::cerr << "<INVALID COMMAND>\n";
        }
    }

    destroy(db);
    return 0;
}