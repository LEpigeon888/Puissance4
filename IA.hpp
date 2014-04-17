#ifndef IA_HPP
#define IA_HPP

#include <SFML/Graphics.hpp>

typedef std::pair<int, int> poseCase;

enum typeCase {VIDE = 0, BLEU, ROUGE};

class IAclass
{
public:
    void setColor(typeCase newColor);
    int calcCoup(std::map<poseCase, typeCase>& mapLevel, int prof = 42);
    int calcMinMax(std::map<poseCase, typeCase>& mapLevel, int prof, bool isMax, int alpha, int beta);
    int evalue(std::map<poseCase, typeCase>& mapLevel);
    poseCase coupPossible(std::map<poseCase, typeCase>& mapLevel, int numberColumn);
    bool checkWin(std::map<poseCase, typeCase>& mapLevel);
    bool checkEndGame(std::map<poseCase, typeCase>& mapLevel);
private:
    typeCase color;
    typeCase enemiColor;
    poseCase lastPose;
};

#endif
