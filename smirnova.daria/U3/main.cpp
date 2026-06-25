#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>

#include "arguments.h"
#include "database.h"
#include "meeting.h"
#include "commands.h"

using namespace smirnova;

static bool isNumber(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(c)) return false;
    }
    return true;
}

static bool loadDataFiles(Database& db, const std::vector<std::string>& dataFiles) {
    for (size_t f = 0; f < dataFiles.size(); ++f) {
        std::ifstream data(dataFiles[f].c_str());
        if (!data.is_open()) {
            std::cerr << "CANNOT OPEN DATA: " << dataFiles[f] << '\n';
            return false;
        }

        std::string line;
        while (std::getline(data, line)) {
            if (line.empty()) {
                continue;
            }

            Meeting m;
            if (!parseMeeting(line, m)) {
                // Проверяем: может это встреча с самим собой?
                std::istringstream iss(line);
                size_t day, month, year, id1, id2, duration;
                if (iss >> day >> month >> year >> id1 >> id2 >> duration) {
                    if (id1 == id2) {
                        // Это встреча с самим собой - игнорируем
                        continue;
                    }
                }
                std::cerr << "ERROR IN DATA: " << dataFiles[f] << '\n';
                return false;
            }

            addMeeting(db, m);
        }
    }

    return true;
}

static bool loadPersonsFile(Database& db, const std::string& filename) {
    if (filename.empty()) {
        return true;
    }

    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "CANNOT OPEN PERSONS FILE\n";
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        Person p;
        if (parsePerson(line, p)) {
            addPerson(db, p);
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    Arguments args;
    if (!parseArguments(argc, argv, args)) {
        std::cerr << "INVALID ARGS\n";
        return 1;
    }

    Database db;
    init(db);

    // Загружаем данные о людях (если есть)
    if (!loadPersonsFile(db, args.inFile)) {
        destroy(db);
        return 2;
    }

    // Загружаем все файлы со встречами
    if (!loadDataFiles(db, args.dataFiles)) {
        destroy(db);
        return 3;
    }

    // Устанавливаем начальный диапазон
    updateRange(db);

    // Обрабатываем команды
    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        // ========== СТАРЫЕ КОМАНДЫ ==========
        if (cmd == "anons") {
            commandAnons(db, std::cout);
        }
        else if (cmd == "desc") {
            std::string idStr;
            iss >> idStr;
            if (isNumber(idStr)) {
                commandDesc(db, std::stoul(idStr), std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "redesc") {
            std::string idStr;
            iss >> idStr;
            std::string desc;
            std::getline(iss, desc);
            if (isNumber(idStr) && !desc.empty()) {
                // Убираем первый пробел
                if (!desc.empty() && desc[0] == ' ') {
                    desc = desc.substr(1);
                }
                commandRedesc(db, std::stoul(idStr), desc, std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "deanon") {
            std::string anonStr, idStr;
            iss >> anonStr >> idStr;
            if (isNumber(anonStr) && isNumber(idStr)) {
                commandDeanon(db, std::stoul(anonStr), std::stoul(idStr), std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "meets") {
            std::string idStr;
            iss >> idStr;
            if (isNumber(idStr)) {
                commandMeets(db, std::stoul(idStr), std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "commons") {
            std::string id1Str, id2Str;
            iss >> id1Str >> id2Str;
            if (isNumber(id1Str) && isNumber(id2Str)) {
                commandCommons(db, std::stoul(id1Str), std::stoul(id2Str), std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "less") {
            std::string durationStr, idStr;
            iss >> durationStr >> idStr;
            if (isNumber(durationStr) && isNumber(idStr)) {
                commandLess(db, std::stoul(durationStr), std::stoul(idStr), std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "greater") {
            std::string durationStr, idStr;
            iss >> durationStr >> idStr;
            if (isNumber(durationStr) && isNumber(idStr)) {
                commandGreater(db, std::stoul(durationStr), std::stoul(idStr), std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "out-persons") {
            std::string filename;
            iss >> filename;
            if (!filename.empty()) {
                commandOutPersons(db, filename);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
            // ========== НОВЫЕ КОМАНДЫ ==========
        else if (cmd == "range") {
            commandRange(db, std::cout);
        }
        else if (cmd == "before") {
            size_t day, month, year;
            if (iss >> day >> month >> year) {
                commandBefore(db, day, month, year, std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "after") {
            size_t day, month, year;
            if (iss >> day >> month >> year) {
                commandAfter(db, day, month, year, std::cout);
            } else {
                std::cout << "<INVALID COMMAND>\n";
            }
        }
        else if (cmd == "pop-range") {
            commandPopRange(db, std::cout);
        }
        else {
            std::cout << "<INVALID COMMAND>\n";
        }
    }

    destroy(db);
    return 0;
}