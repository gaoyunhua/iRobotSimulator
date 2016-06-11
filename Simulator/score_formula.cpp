
#include <map>
#include <string>
#include <algorithm>


using namespace std;

extern "C" int calc_score(const map<string, int>& score_params)
{
    int posScore, winnerScore, dirtLeftScore, dockScore, position;

    int actualPosition = score_params.at("actual_position_in_competition");
    winnerScore = (score_params.at("winner_num_steps") - score_params.at("this_num_steps")) * 10;
    dirtLeftScore = (score_params.at("sum_dirt_in_house") - score_params.at("dirt_collected")) * 3;
    dockScore = score_params.at("is_back_in_docking") == 1 ? 50 : -200;
    if (dockScore == 50 && dirtLeftScore == 0)
        position = min(4, actualPosition);
    else
        position = 10;
    posScore = (position - 1) * 50;

    int score = 2000 - posScore + winnerScore - dirtLeftScore + dockScore;
    return max(0, score);
}
