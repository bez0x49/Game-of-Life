#include "stdafx.h"
#include "Universe.h"

int main() {
    using namespace std::chrono_literals;
    
    Universe game(50, 50);
    game.run(Universe::Seed::Random, 100, 100ms);
}