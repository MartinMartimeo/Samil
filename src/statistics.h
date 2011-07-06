#pragma once
#ifndef __statistics_h
#define __statistics_h

/*
 *  File: statistics.h
 *  Autor: bastinat0r
 *
 *  Inhalt: klasse Statistics zur Speicherung, Ausgabe von Spielstatistik eines Spiels
 */

class Statistics
{
    public:
    Statistics();
    Statistics(Statistics& stats);
    Statistics(int iPoints1, int iPoints2);
    Statistics(std::vector<int> *pvPoints);
    void print();

    private:
    std::vector<int> *m_pvPoints;

    protected:
    std::vector<int> GetPoints();
};

#endif
