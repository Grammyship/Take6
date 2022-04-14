#pragma once
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

int32_t cardtoeat(int32_t number )
{
    int32_t point;
    if( number  == 55 )
        point = 7;
    else if( number % 11 == 0 )
        point = 5;
    else if( number %10 == 0)
        point = 3;
    else if( number % 5 == 0 )
        point = 2;
    else
        point = 1;
    return point;
}

int32_t _40847041S_card[10];

void CSIE_41S_setup( int32_t id )
{
    for( int i = 0; i < 10; i++ )
        _40847041S_card[i] = 0;
    return;
}

void CSIE_41S_deal( const int32_t card[10] )
{
    for( int i = 0; i < 10; i++ )
        _40847041S_card[i] = card[i];
    return;
}

int32_t CSIE_41S_pick( const int32_t table[4][5] , const int score[2] , const int last[8] , const int card[10])
{
    srand( time( NULL) );
    int random = rand()%10;
    int pick = _40847041S_card[random];
    return pick;
}

int CSIE_41S_choose( const int32_t table[4][5] , int card )
{
    int total_card[4] = {0};
    int max = 0;
    for( int i = 0; i< 4 ; i++ )
    {
        for(int j = 0; j < 5; j++ )
        {
            total_card[i] -= cardtoeat(table[i][j]);
        }
    }
    max = -100;
    int best;
    for( int i = 0; i < 4; i++ )
    {
        if( max <total_card[i])
        {
            max = total_card[i];
            best = i;
        }

    }

    return best;
}