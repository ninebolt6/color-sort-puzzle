#include "ScoreManager.h"

ScoreManager* ScoreManager::instance = nullptr;

ScoreManager::ScoreManager() : score{ 0, 0 } {}

ScoreManager::~ScoreManager() {
    delete instance;
}

ScoreManager* ScoreManager::get_instance() {
    if (instance == nullptr) {
        instance = new ScoreManager();
    }
    return instance;
}

Score ScoreManager::get_score() {
    return score;
}

void ScoreManager::set_score(const int& move_count, const int& play_sec) {
    score.move_count = move_count;
    score.play_sec = play_sec;
}