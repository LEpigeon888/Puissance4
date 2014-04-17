#include "IA.hpp"

void IAclass::setColor(typeCase newColor)
{
    color = newColor;
    if(color == BLEU)
    {
        enemiColor = ROUGE;
    }
    else
    {
        enemiColor = BLEU;
    }
}

int IAclass::calcCoup(std::map<poseCase, typeCase>& mapLevel, int prof)
{
    int alpha = -10001;
    int beta = 10001;
    int tmpMax = 0;
    poseCase poseMax(-1, -1);
    poseCase poseActu(-1, -1);
    for(int i = 0; i < 7; ++i)
    {
        poseActu = coupPossible(mapLevel, i);
        if(poseActu == poseCase(-1, -1))
        {
            continue;
        }

        mapLevel[poseActu] = color;
        lastPose = poseActu;
        tmpMax = calcMinMax(mapLevel, prof - 1, false, alpha, beta);
        if(tmpMax > alpha)
        {
            alpha = tmpMax;
            poseMax = poseActu;
        }

        mapLevel[poseActu] = VIDE;
    }

    return poseMax.first;
}

int IAclass::evalue(std::map<poseCase, typeCase>& mapLevel)
{
    int numberEvalue = 0;
    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 6; ++j)
        {
            if(mapLevel[poseCase(i, j)] == VIDE)
            {
                continue;
            }

            for(int tmpI = i; tmpI < i + 2; ++tmpI)
            {
                for(int tmpJ = j - 1; tmpJ < j + 2; ++tmpJ)
                {
                    if((tmpI == i && tmpJ == j) || mapLevel[poseCase(tmpI, tmpJ)] == VIDE || (tmpI == i && tmpJ == j - 1))
                    {
                        continue;
                    }

                    if(mapLevel[poseCase(tmpI, tmpJ)] == mapLevel[poseCase(i, j)] && mapLevel[poseCase(i + (i - tmpI), j + (j - tmpJ))] != mapLevel[poseCase(i, j)])
                    {
                        int tmpX = tmpI;
                        int tmpY = tmpJ;
                        int numberToken = 1;
                        do
                        {
                            ++numberToken;
                            tmpX = tmpX - (i - tmpI);
                            tmpY = tmpY - (j - tmpJ);
                        }
                        while(mapLevel[poseCase(tmpX, tmpY)] == mapLevel[poseCase(i, j)]);

                        if(((mapLevel[poseCase(tmpX, tmpY)] == VIDE || mapLevel[poseCase(i + (i - tmpI), j + (j - tmpJ))] == VIDE) && tmpX > 0 && tmpX < 7 && tmpY > 0 && tmpY < 6) || numberToken >= 4)
                        {
                            int tmpNumberEvalue = 0;
                            if(numberToken == 2)
                            {
                                tmpNumberEvalue = 10;
                            }
                            else if(numberToken == 3)
                            {
                                tmpNumberEvalue = 100;
                            }
                            else if(numberToken >= 4)
                            {
                                if(mapLevel[poseCase(i, j)] == color)
                                {
                                    numberEvalue = 10000;
                                }
                                else
                                {
                                    numberEvalue = -10000;
                                }
                                return numberEvalue;
                            }

                            if(mapLevel[poseCase(i, j)] != color)
                            {
                                tmpNumberEvalue *= -1;
                            }
                            numberEvalue += tmpNumberEvalue;
                        }
                    }
                }
            }
        }
    }

    return numberEvalue;
}

poseCase IAclass::coupPossible(std::map<poseCase, typeCase>& mapLevel, int numberColumn)
{
    for(int i = 5; i >= 0; --i)
    {
        if(mapLevel[poseCase(numberColumn, i)] == VIDE)
        {
            return poseCase(numberColumn, i);
        }
    }

    return poseCase(-1, -1);
}

int IAclass::calcMinMax(std::map<poseCase, typeCase>& mapLevel, int prof, bool isMax, int alpha, int beta)
{
    int tmpNb = 0;
    poseCase poseActu(-1, -1);

    if(checkEndGame(mapLevel) == true || prof <= 0)
    {
        return evalue(mapLevel);
    }

    for(int i = 0; i < 7; ++i)
    {
        poseActu = coupPossible(mapLevel, i);
        if(poseActu == poseCase(-1, -1))
        {
            continue;
        }

        mapLevel[poseActu] = isMax ? color : enemiColor;
        lastPose = poseActu;
        tmpNb = calcMinMax(mapLevel, prof - 1, !isMax, alpha, beta);
        mapLevel[poseActu] = VIDE;
        if(isMax)
        {
            if(tmpNb > alpha)
            {
                alpha = tmpNb;
            }
            if(alpha >= beta)
            {
                return alpha;
            }
        }
        else if(!isMax)
        {
            if(tmpNb < beta)
            {
                beta = tmpNb;
            }
            if(beta <= alpha)
            {
                return beta;
            }
        }
    }

    return (isMax ? alpha : beta);
}

bool IAclass::checkWin(std::map<poseCase, typeCase>& mapLevel)
{
    if(mapLevel.size() < 7)
    {
        return false;
    }

    for(int i = lastPose.first - 1; i < lastPose.first + 2; ++i)
    {
        for(int j = lastPose.second - 1; j < lastPose.second + 2; ++j)
        {
            if((i == lastPose.first && j == lastPose.second) || mapLevel[poseCase(i, j)] == VIDE)
            {
                continue;
            }

            if(mapLevel[poseCase(i, j)] == mapLevel[lastPose])
            {
                int tmpX = i;
                int tmpY = j;
                int numberToken = 1;
                do
                {
                    ++numberToken;
                    tmpX = tmpX - (lastPose.first - i);
                    tmpY = tmpY - (lastPose.second - j);
                }
                while(mapLevel[poseCase(tmpX, tmpY)] == mapLevel[lastPose]);

                tmpX = lastPose.first;
                tmpY = lastPose.second;
                --numberToken;
                do
                {
                    ++numberToken;
                    tmpX = tmpX + (lastPose.first - i);
                    tmpY = tmpY + (lastPose.second - j);
                }
                while(mapLevel[poseCase(tmpX, tmpY)] == mapLevel[lastPose]);

                if(numberToken > 3)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

bool IAclass::checkEndGame(std::map<poseCase, typeCase>& mapLevel)
{
    if(checkWin(mapLevel))
    {
        return true;
    }
    bool mapLevelIsFull = true;
    for(int i = 0; i < 7; ++i)
    {
        for(int j = 0; j < 6; ++j)
        {
            if(mapLevel[poseCase(i, j)] == VIDE)
            {
                mapLevelIsFull = false;
                break;
            }
        }
        if(mapLevelIsFull == false)
        {
            break;
        }
    }

    if(mapLevelIsFull)
    {
        return true;
    }

    return false;
}
