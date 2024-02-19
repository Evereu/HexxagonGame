#include <fstream>
#include "SaveScore.h"
#include "Move.h"
#include <fmt/ostream.h>

auto SaveScore::saveScore(int scorePlayerOne, int scorePlayerTwo) -> void{

    //https://cplusplus.com/doc/tutorial/exceptions/

    try {
        auto file = std::fstream("../score.txt", std::ios::out | std::ios::app);

        if (!file.is_open()) {
            fmt::println("{}","Nie można załadować czcionki") ;
        }

        fmt::println(file, "{}", scorePlayerOne);
        fmt::println(file, "{}", scorePlayerTwo);

    } catch (const std::exception& e) {
        fmt::println("{}",e.what()) ;
    }
}
