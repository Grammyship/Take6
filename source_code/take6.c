#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

typedef struct _card
{
    int number;
    int point;
    int gone;
}card;

card poker[104];

int set_table( int table[4][6] , int round , int k , int people , int arr[10] , int point[10] , int difficulty )
{
    if( round == 0 )
    {
        for( int i = 0; i < 4 ; i++ )
        {
            int a = ( rand() % 104 );
            if( poker[a].gone == 1 )
            {
                i--;
            }
            else
            {
                table[i][0] = a+1;
                poker[a].gone = 1;
            }
        }
        return 0;
    }
    else
    {
        int near = -1;
        int eat = 1;
        int max = 0;
        
        for( int i = 0; i < 4 ; i++ )
        {
            if( ( table[i][table[i][5]] <  arr[k] ) && ( table[i][table[i][5]] >= max ) && table[i][5] != 4 )
            {
                near = i;
                max = table[i][table[i][5]];
                eat = 0;
            }
        }
        if( near == -1 )
        {
            eat = 1;
        }
        //printf( "%d_%d\n" , k , eat);
        if( eat )
        {
            // human set
            if( k == 0 )
            {
                int boom = 0;
                while( boom <=0 || boom >= 5 )
                {
                    printf( "Oops, which row do you want to take?(1~4)" );
                    scanf( "%d" , &boom );
                }
                boom--;
                for( int i = 0; i <= table[boom][5] ; i++ )
                {
                    point[0]+=poker[table[boom][i]-1].point;
                }
                for( int i = 0; i < 6; i++ )
                {
                    table[boom][i] = 0;
                }

                table[boom][0] = arr[k];
                table[boom][5] = 0;
            }
            // ai set
            else
            {
                if( difficulty == 1 )
                {
                    int row = 0;
                    int max = 0;
                    for( int i = 0; i < 4 ; i++)
                    {
                        int point = 0;
                        for( int j = 0; j < 5 ; j++ )
                        {
                            point += poker[table[i][j]-1].point;
                        }
                        if( point >= max )
                        {
                            max = point;
                            row = i;
                        }
                    }

                    for( int i = 0; i < 6; i++ )
                    {
                        table[row][i] = 0;
                    }
                    point[k] += max;
                    table[row][0] = arr[k];
                }
                else if( difficulty == 2 )
                {
                    int a = ( rand() % 4 );
                    int pt = 0;
                    for( int i = 0 ; i < 5 ; i++ )
                    {
                        pt += poker[table[a][i]-1].point;
                        table[a][i] = 0;
                    }
                    table[a][0] = arr[k];
                    table[a][5] = 0;
                    point[k] += pt;
                }
                else
                {
                    int row = 0;
                    int min = 0;
                    for( int i = 0; i < 4 ; i++)
                    {
                        int point = 0;
                        for( int j = 0; j < 5 ; j++ )
                        {
                            point += poker[table[i][j]-1].point;
                        }
                        if( point <= min )
                        {
                            min = point;
                            row = i;
                        }
                    }

                    for( int i = 0; i < 5; i++ )
                    {
                        table[row][i] = 0;
                    }
                    point[k] += min;
                    table[row][0] = arr[k];
                    table[row][5] = 0;
                }
                
            }
        }   
        else
        {
            table[near][5]++;
            table[near][table[near][5]] = arr[k];            
        }
            
    }
}

void print_table( int table[4][6] )
{
    printf( "Table:\n" );
    for(int i = 0; i < 4 ; i++ )
    {
        for( int j = 0; j < 5 ; j++ )
        {
            if( table[i][j] == 0 )
            {
                continue;
            }
            else
            {
                printf( "|| %2d (%d) " , table[i][j] , poker[table[i][j]-1].point );
            }
            
            
        }
        printf( "||\n\n\n" );
    }
}

void licening( int hand[10][10] , int k )
{
    for( int i = 0 ; i < k; i++ )
    {
        for( int j = 0 ; j < 10 ; j++ )
        {
            int a = ( rand() % 104 );
            if( poker[a].gone == 1 )
            {
                j--;
            }
            else
            {
                hand[i][j] = a+1;
                poker[a].gone = 1;
            }    
        }    
    }
}

void print_hand( int hand[10][10] , int k )
{
    printf( "Your hand: " );
    for(int i = 0; i < 10; i++ )
    {
        if( hand[k][i] != 0 )
        {
            printf( "||%3d " , hand[k][i] );
        }
    }
    printf( "||\n\n" );
}

int pick_hand( int hand[10][10] , int a )
{
    for( int i = 0; i < 10 ; i++ )
    {
        if( a == hand[0][i] )
        {
            hand[0][i] = 0;
            //printf( "%d\n" , a );
            return a;
        }
    }
    
    return -1;
}

int ai_pick_hand( int hand[10][10] , int ai , int dif )
{
    if( dif == 1 )
    {
        int max = 0;
        int j = 0;
        for( int i = 0; i < 10 ; i++ )
        {
            
            if( hand[ai][i] >= max )
            {
                max = hand[ai][i];
                j = i;
            }
        }
        hand[ai][j] = 0;
        return max;
    }
    else if( dif == 2 )
    {
        int min = 105;
        int j = 0;
        for( int i = 0; i < 10 ; i++ )
        {
            
            if( hand[ai][i] <= min && hand[ai][i] != 0 )
            {
                min = hand[ai][i];
                j = i;
            }
        }
        hand[ai][j] = 0;
        return min;
    }
    else
    {
        int a = ( rand() % 10 );
        int pick = hand[ai][a];
        while( pick == 0 )
        {
            a = ( rand() % 10 );
            pick = hand[ai][a];
        }
        hand[ai][a] = 0;
        return pick;
    }
    
}

int main()
{
    srand(time(NULL));

    int mode = 0;
    int count = 0; // how many times you choose a useless function

    /*  print card's informations

    for( int i = 0; i < 104 ; i++ )
    {
        printf( "%d_%d\n" , poker[i].number , poker[i].point );
    }

    */

    //  starting page
    printf( "=======================================================\n" );
    printf( "         _______                 ____    ____          \n" );
    printf( "            |       /\\     | /  |       |             \n" );
    printf( "            |      /__\\    |/   |____   |____         \n" );
    printf( "            |     /    \\   |\\   |       |    |       \n" );
    printf( "            |    /      \\  | \\  |____   |____|       \n" );
    printf( "                                                       \n" );
    printf( "=======================================================\n" );
    printf( "                                                       \n" );
    sleep(5);
    printf( "Welcome to TAKE6!                                      \n" );
    printf( "                                                       \n" );
    printf( "This is a easy card game that is very easy to learn.   \n" );
    printf( "                                                       \n" );
    printf( "You can challenge your families and friends, since we  \n" );
    printf( "support at most 10 players playing at the same time!   \n" );
    printf( "If you are a margina, who has no friends, don't worry! \n" );
    printf( "We have some AI's who can play with you, no excuse!    \n" );
    printf( "                                                       \n" );
    printf( "So what are you waiting for? Let's playyyyyyyyyyyyyyyy!\n" );
    printf( "                                                       \n" );
    printf( "=======================================================\n" );
    printf( "                                                       \n" );
    sleep(10);
    printf( "Game Menu:                                             \n" );
    printf( "                                                       \n" );
    printf( "(1) Single player                                      \n" );
    printf( "(2) Multiplayer                                        \n" );
    printf( "(3) The Casino                                         \n" );
    printf( "(4) How to play                                        \n" );
    printf( "(5) Options                                            \n" );
    printf( "(6) Instructions                                       \n" );
    printf( "(7) Exit game                                          \n\n" );

    // enter mode
    printf( "Your choice(1~7):\n" );
    if( scanf( "%d" , &mode ) < 1 )
    {
        printf( "You have to enter number 1~7, not english words, as punishment, please restart\nthe game :(\n" );
        return -1;
    }    
    
    while( mode <= 0 || mode >= 8 )
    {
        printf( "You have to enter number 1~7\n" );
        printf( "Your choice(1~7):\n" );
        if( scanf( "%d" , &mode ) < 1 )
        {
            printf( "You have to enter number 1~7, not english words, as punishment, please restart\nthe game :(\n\n\n" );
            return -1;
        }
    }
    
    while(1)
    {
        printf( "                                                       \n" );
        printf( "                                                       \n" );
        printf( "=======================================================\n" );
        printf( "                                                       \n" );
        printf( "                                                       \n" );

        // game modes
        switch (mode)
        {
            case 1:
            {
                printf( "You chose \"Single player\"......\n\n\n" );
                
                // initialize the table
                int table[4][6];
                for( int i = 0; i < 4 ; i++ )
                {
                    for( int j = 0; j < 6; j++ )
                    {
                        table[i][j]=0;
                    }
                }
                // initialize player hands
                int hand[10][10];
                for( int i = 0; i < 10 ; i++ )
                {
                    for( int j = 0; j < 10 ; j++ )
                        hand[i][j] = 0;
                }
                int point[10];
                for( int i = 0; i < 10 ; i++ )
                {
                    point[i] = 0;
                }
                int player = 1;
                int difficulty = 0;
                // initialize the cards
                for( int i = 0; i < 104 ; i++ )
                {
                    poker[i].number = i+1;
                    poker[i].point = 1;
                    poker[i].gone = 0;
                    if( i == 54 )
                    {
                        poker[i].point = 7;
                    }
                    else if( ( (i+1) % 11 ) == 0  )
                    {
                        poker[i].point = 5;
                    }
                    else if( ( (i+1) % 10 ) == 0  )
                    {
                        poker[i].point = 3;
                    }
                    else if( ( (i+1) % 5 ) == 0  )
                    {
                        poker[i].point = 2;
                    }
                }
                // enter players
                printf( "Please enter AI_player amount(1~9):\n" );
                scanf("%d" , &player );
                while( player <= 0 || player >= 10 )
                {
                    printf( "You have to enter number 1~9\n" );
                    printf( "Please enter AI_player amount(1~9):\n" );
                    if( scanf( "%d" , &player ) < 1 )
                    {
                        printf( "You have to enter number 1~9, not english words, as punishment, please restart\nthe game :(\n\n\n" );
                        return -1;
                    }
                }
                printf( "\n\n" );
                // enter difficulty
                printf( "Please enter AI_player difficulty(1~3):\n" );
                scanf("%d" , &difficulty );
                while( difficulty <= 0 || difficulty >= 10 )
                {
                    printf( "You have to enter number 1~3\n" );
                    printf( "Please enter AI_player difficulty(1~3):\n" );
                    if( scanf( "%d" , &difficulty ) < 1 )
                    {
                        printf( "You have to enter number 1~3, not english words, as punishment, please restart\nthe game :(\n\n\n" );
                        return -1;
                    }
                }
                printf( "                                                       \n" );
                printf( "                                                       \n" );               
                printf( "=======================================================\n" );
                printf( "                                                       \n" );
                printf( "                                                       \n" );
                printf( "You are playinging with %d AIs with %d difficulty......\n", player , difficulty );
                printf( "                                                       \n" );
                printf( "                                                       \n" );
                printf( "=======================================================\n" );
                printf( "                                                       \n" );
                sleep(5);

                licening( hand , player+1 );

                
                /*  print AI card
                for( int j = 1; j < player+1 ; j++ )
                {
                    print_hand( hand , j );
                }
                */
                int arr[10] = {0}; 
                int round = 0;
                set_table( table , round , 0 , player , arr , point , difficulty );
                print_table( table );
                round++;
                // in game
                for( int i = 0 ; i < 10 ; i++ )
                {
                    // picked cards
                    for( int i = 0; i < 10 ; i++ )
                    {
                        arr[i] = 0;
                    }
                    // order of players
                    int arr_[10] = {0};
                    for( int i = 0; i < 10 ; i++ )
                    {
                        arr_[i] = i;
                    }  
                    print_hand( hand , 0 );                
                    printf( "Which card do you want to pick?\n" );
                    int pick = 0; 
                    while( 1 ) 
                    {
                        if( scanf( "%d" , &pick ) < 1 )
                        {
                            printf( "You have to enter numbers in your hands, not english words, as punishment, please restart\nthe game :(\n" );
                            return -1;
                        }
                        int a = pick_hand( hand , pick );
                        //printf( "%d\n" , a );
                        if( a != -1 )
                            break;
                        printf( "Please enter the number of the cards in your hand :(\n" );
                    }
                    arr[0] = pick;
                    
                    if( player >= 1 )
                    {
                        arr[1] = ai_pick_hand( hand , 1 , difficulty );
                        printf( "AI1:%d\n" , arr[1] );
                    }
                    if( player >= 2 )
                    {
                        arr[2] = ai_pick_hand( hand , 2 , difficulty );
                        printf( "AI2:%d\n" , arr[2] );
                    }
                    if( player >= 3 )
                    {
                        arr[3] = ai_pick_hand( hand , 3 , difficulty );
                        printf( "AI3:%d\n" , arr[3] );
                    }
                    if( player >= 4 )
                    {
                        arr[4] = ai_pick_hand( hand , 4 , difficulty );
                        printf( "AI4:%d\n" , arr[4] );
                    }
                    if( player >= 5 )
                    {
                        arr[5] = ai_pick_hand( hand , 5 , difficulty );
                        printf( "AI5:%d\n" , arr[5] );
                    }
                    if( player >= 6 )
                    {
                        arr[6] = ai_pick_hand( hand , 6 , difficulty );
                        printf( "AI6:%d\n" , arr[6] );
                    }
                    if( player >= 7 )
                    {
                        arr[7] = ai_pick_hand( hand , 7 , difficulty );
                        printf( "AI7:%d\n" , arr[7] );
                    }
                    if( player >= 8 )
                    {
                        arr[8] = ai_pick_hand( hand , 8 , difficulty );
                        printf( "AI8:%d\n" , arr[8] );
                    }
                    if( player >= 9 )
                    {
                        arr[9] = ai_pick_hand( hand , 9 , difficulty );
                        printf( "AI9:%d\n" , arr[9] );
                    }
                    /* all picked cards
                    for( int i = 0; i < player+1 ; i++ )
                    {
                        printf( "%d_" , arr[i] );
                    }
                    */
                    int _arr[10];
                    for( int i = 0; i < 10 ; i++ )
                    {
                        _arr[i] = arr[i];
                    }
                    // set table order
                    for( int i = 0; i < player ; i++ )
                    {
                        for( int j = 0; j < player; j++ )
                        {
                            if( _arr[j] > _arr[j+1] )
                            {
                                int temp = 0;
                                temp = _arr[j];
                                _arr[j] = _arr[j+1];
                                _arr[j+1] = temp;
                                temp = arr_[j];
                                arr_[j] = arr_[j+1];
                                arr_[j+1] = temp;
                            }
                        }
                    }
                    /*
                    for( int i = 0; i < player+1 ; i++ )
                    {
                        printf( "%d_" , arr[i] );
                    }
                    printf( "\n");
                    for( int i = 0; i < player+1 ; i++ )
                    {
                        printf( "%d_" , arr_[i] );
                    }
                    printf( "\n" );
                    */
                    for( int i = 0; i < player+1; i++ )
                    {
                        set_table( table , round , arr_[i] , player , arr , point , difficulty );
                    }
                    round++;
                    
                    for( int i = 0; i < player+1 ; i++ )
                    {
                        if( i == 0 )
                        {
                            printf( "Your point: " );
                        }
                        else
                        {
                            printf( "AI %d: ", i );
                        }
                        
                        printf( "%2d\n" , point[i]) ;
                    }
                    print_table( table );
                    
                }
                // end of game
                int rank[10];
                for( int i = 0; i < 10; i++ )
                {
                    rank[i] = i;
                }
                int _point[10];
                for( int i = 0; i < 10; i++ )
                {
                    _point[i] = point[i];
                }
                for( int i = 0; i < player ; i++ )
                {
                    for( int j = i; j < player; j++ )
                    {
                        if( _point[j] > _point[j+1] )
                        {
                            int temp = 0;
                            temp = _point[j];
                            _point[j] = _point[j+1];
                            _point[j+1] = temp;
                            temp =rank[j];
                            rank[j] = rank[j+1];
                            rank[j+1] = temp;
                        }
                    }
                }

                for( int i = 0; i < player+1; i++ )
                {
                    if(i == 0 )
                    {
                        printf( "\n\nYour score: %d\n" , point[0] );
                    }
                    else
                    {
                        printf( "AI %d score: %d\n" , i , point[i] );
                    }

                }

                printf( "\n\n" );

                for( int i = 0; i < player+1; i++ )
                {
                    if( rank[i] == 0 )
                    {
                        if( i == 0 )
                        {
                            printf( "You are the greatest :D\n" );
                        }
                        else if( i == player )
                        {
                            printf( "You are the loser LOL\n" );
                        }
                        else
                        {
                            printf( "You are number %d\n" , i+1 );
                        }
                        
                    }
                    else
                    {
                        printf( "AI %d is number %d\n" , rank[i] , i+1 );
                    }
                    
                }

                sleep(5);

                break;
            }
            case 2:
            {
                printf( "You chose \"Multiplayers\"......\n\n\n" );
                printf( "Oops, looks like this feature is going to use the Internet\n" );
                printf( "And the developer hasn't learn about it :P\n" );
                printf( "Please pick another feature :(\n\n\n" );
                sleep(5);
                count++;
                break;
            }
            case 3:
            {
                printf( "You chose \"The Casino\"......\n\n\n" );
                
                int hand[10][10];
                for( int i = 0; i < 10 ; i++ )
                {
                    for( int j = 0; j < 10 ; j++ )
                        hand[i][j] = 0;
                }
                int point[10];
                for( int i = 0; i < 10 ; i++ )
                {
                    point[i] = 0;
                }
                int player = 1;
                int difficulty = 0;
                // initialize the cards
                for( int i = 0; i < 104 ; i++ )
                {
                    poker[i].number = i+1;
                    poker[i].point = 1;
                    poker[i].gone = 0;
                    if( i == 54 )
                    {
                        poker[i].point = 7;
                    }
                    else if( ( (i+1) % 11 ) == 0  )
                    {
                        poker[i].point = 5;
                    }
                    else if( ( (i+1) % 10 ) == 0  )
                    {
                        poker[i].point = 3;
                    }
                    else if( ( (i+1) % 5 ) == 0  )
                    {
                        poker[i].point = 2;
                    }
                }
                
                printf( "                                                       \n" );
                printf( "                                                       \n" );               
                printf( "=======================================================\n" );
                printf( "                                                       \n" );
                printf( "                                                       \n" );
                printf( "You're gambling with an AI......The bigger, the winner!\n" );
                printf( "                                                       \n" );
                printf( "                                                       \n" );
                printf( "=======================================================\n" );
                printf( "                                                       \n" );
                sleep(5);

                licening( hand , player+1 );
                int round= 0;
                for( int i = 0 ; i < 10; i++ )
                {
                    print_hand( hand , 0 ); 
                    printf( "Which card do you want to pick?\n" );
                    int pick = 0; 
                    while( 1 ) 
                    {
                        if( scanf( "%d" , &pick ) < 1 )
                        {
                            printf( "You have to enter numbers in your hands, not english words, as punishment, please restart\nthe game :(\n" );
                            return -1;
                        }
                        int a = pick_hand( hand , pick );
                        //printf( "%d\n" , a );
                        if( a != -1 )
                            break;
                        printf( "Please enter the number of the cards in your hand :(\n" );
                    }
                    printf( "\nYou choose %d\n\n" , pick );
                    
                    int pick2 = ai_pick_hand( hand , 1 , 3 );
                    printf( "AI choose %d\n\n" , pick2 );
                    printf( "                                                       \n" );
                    printf( "                                                       \n" );               
                    printf( "=======================================================\n" );
                    printf( "                                                       \n" );
                    printf( "                                                       \n" );
                    if( pick > pick2 )
                    {
                        printf( "You win!\n\n\n" );
                        round++;
                    }
                    else
                    {
                        printf( "You sucks!\n\n\n" );
                    }
                    printf( "                                                       \n" );
                    printf( "                                                       \n" );               
                    printf( "=======================================================\n" );
                    printf( "                                                       \n" );
                    printf( "                                                       \n" );
                }
                printf( "                                                       \n" );
                printf( "                                                       \n" );               
                printf( "=======================================================\n" );
                printf( "                                                       \n" );
                printf( "                                                       \n" );
                printf( "You have won %d rounds\n\n" , round );
                if( round > 5 )
                {
                    printf( "You win the gamble!!!\n" );
                }
                else if( round== 5 )
                {
                    printf( "It's a even!!! Good game :)\n" );
                }
                else
                {
                    printf( "You are a loser LOL\n" );
                }                
                printf( "                                                       \n" );
                printf( "                                                       \n" );
                printf( "=======================================================\n" );
                printf( "                                                       \n" );
                sleep(5);
                break;
            }
            case 4:
            {
                printf( "You chose \"How to play\"......\n\n\n" );
                printf( "The goal is to be the player with the fewest points. To do this, the players need to avoid picking up penalty cards.\n\n" );
                printf( "At each turn, each player selects a card to play, and puts the card face down on the table.\nWhen all the players have selected a card, the cards are uncovered.\n\n" );
                printf( "Starting with the lowest valued card, and continuing in increasing order.\nEach player must put their card at the end of one of the four rows on the table, following these rules:\n\n" );
                printf( "(1)The card must be put on a row where the latest (end) card is lower in value than the card that is about to be played.\n\n" );
                printf( "(2)The card must be put on the row where the latest (end) card is the closest in value to the card that is about to be played\n   (if your card is 33, then place it next to the 30 not the 29, for example)\n\n" );
                printf( "(3)If the row where the played card must be placed already contains 5 cards (the player's card is the 6th),\n   the player must gather the 5 cards on the table, leaving only the 6th card in their place to start a new row.\n   The gathered cards must be taken separated and never mixed with the hand cards.\n   The sum of the number of cattle head on the gathered cards will be calculated at the end of the round.\n\n" );
                printf( "(4)If the played card is lower than all the latest cards present on the four rows,\n   the player must choose a row and gather the cards on that row (usually the row with the fewest cattle heads),\n   leaving only the played card on the row.\n\n" );
                printf( "( copied from https://en.wikipedia.org/wiki/6_Nimmt! , if you don't undestand it, that's not my problem :P )\n" );
                sleep(10);
                break;
            }
            case 5:
            {
                printf( "You chose \"Options\"......\n\n\n" );
                printf( "Well, usually this feature can let you change the game volume, picture quality, or something else...\n" );
                printf( "But it's obviously that we don't have any sound or pictures here :P\n" );
                printf( "Please pick another feature :(\n\n\n" );
                sleep(5);
                count++;
                break;
            }
            case 6:
            {
                printf( "You chose \"Instructions\"......\n\n\n" );
                printf( "This is the final project of the computer_programming(II) in NTNU_CSIE_2020_spring.\n" );
                printf( "Due to the evil professor Po-Wen Chi, the student in the class must make this game as final project\n" );
                printf( "This is the project of 40847041S\n\n\n");
                sleep(5);
                count++;
                break;
            }
            case 7:
            {
                printf( "Bye! See you next time ^3^\n\n" );
                return 0;
            }
            default:
            {
                printf( "wrong case :(\n" );
                return -1;
            }
        }

                // check if nerds
        if( count == 3 )
        {
            printf( "Com'on man, stop choosing these useless features :(\n\n" );
        }
        else if( count == 5 )
        {
            printf( "I told you not to do that.\n\n" );
        }
        else if( count == 7 )
        {
            printf( "I'm warning you, don't do that again, damn it.\n\n" );
        }
        else if( count == 9 )
        {
            printf( "I'm warning you the last time, don't do that again, damn it.\n\n" );
        }
        else if( count == 10 )
        {
            printf( "You are such a nerd.\n\n" );
            return -1;
        }

        // keep playing
        printf( "                                                       \n" );
        printf( "                                                       \n" );
        printf( "=======================================================\n" );
        printf( "                                                       \n" );
        printf( "Enjoy this game? Please give us a 5 star review :)     \n" );
        printf( "                                                       \n" );
        printf( "Game Menu:                                             \n" );
        printf( "                                                       \n" );
        printf( "(1) Single player                                      \n" );
        printf( "(2) Multiplayer                                        \n" );
        printf( "(3) The Casino                                         \n" );
        printf( "(4) How to play                                        \n" );
        printf( "(5) Options                                            \n" );
        printf( "(6) Instructions                                       \n" );
        printf( "(7) Exit game                                          \n\n" );

        // enter mode
        printf( "Your choice(1~7):\n" );
        if( scanf( "%d" , &mode ) < 1 )
        {
            printf( "You have to enter number 1~6, not english words, as punishment, please restart\nthe game :(\n" );
            return -1;
        }    
        
        while( mode <= 0 || mode >= 8 )
        {
            printf( "You have to enter number 1~6\n" );
            printf( "Your choice:\n" );
            if( scanf( "%d" , &mode ) < 1 )
            {
                printf( "You have to enter number 1~6, not english words, as punishment, please restart\nthe game :(\n" );
                return -1;
            }
        }

        // end of the while loop
    }

    printf( "If you get here, there are some bugs in this game :(\n" );

    return -1;
}