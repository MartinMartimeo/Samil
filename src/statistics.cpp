/*
 *statistics.cpp
 */
#include <vector>
#include <iostream>

#include "statistics.h"

Statistics::Statistics()
{
    m_pvPoints = NULL;
}

Statistics::Statistics(int iPoints1, int iPoints2)
{
    m_pvPoints = new std::vector<int>(2);
/*    m_pvPoints[0] =  iPoints1;
    m_pvPoints[1] = iPoints2;*/
}

Statistics::Statistics(std::vector<int> *pvPoints)
{
    m_pvPoints = pvPoints;
}
