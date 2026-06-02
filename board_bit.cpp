#include <iostream>
#include <cstdint>

using namespace std;
#define hw  8
#define hw2  64
#define vacant 0
#define stone 1


class board{
public:
uint64_t player_board;
uint64_t opponent_board;
int player;

public:

uint64_t legal(){
    const uint64_t mask_side = opponent_board & 0x7e7e7e7e7e7e7e7eULL;
    const uint64_t mask_ver = opponent_board & 0x00FFFFFFFFFFFF00ULL;
    const uint64_t mask_all = opponent_board& 0x007e7e7e7e7e7e00ULL;
    const uint64_t vacant_board = ~(player_board | opponent_board);
    uint64_t legal_board;
    uint64_t res = 0;
//左
res = (player_board<<1) & mask_side;
res |= (res<<1)& mask_side;
res |= (res<<1)& mask_side;
res |= (res<<1)& mask_side;
res |= (res<<1)& mask_side;
res |= (res<<1)& mask_side;
legal_board= (res<<1 )& vacant_board;
//右
res = (player_board>>1) & mask_side;
res |= (res>>1)& mask_side;
res |= (res>>1)& mask_side;
res |= (res>>1)& mask_side;
res |= (res>>1)& mask_side;
res |= (res>>1)& mask_side;
legal_board |= (res >> 1 )& vacant_board;
//上
res = (player_board<<8) & mask_side;
res |= (res<<8)& mask_ver;
res |= (res<<8)& mask_ver;
res |= (res<<8)& mask_ver;
res |= (res<<8)& mask_ver;
res |= (res<<8)& mask_ver;
legal_board |= (res<<8)& vacant_board;
//下
res = (player_board>>8) & mask_side;
res |= (res>>8)& mask_ver;
res |= (res>>8)& mask_ver;
res |= (res>>8)& mask_ver;
res |= (res>>8)& mask_ver;
res |= (res>>8)& mask_ver;
legal_board |= (res >> 8 )& vacant_board;
//右下がり斜め上
res = (player_board<<9) & mask_all;
res |= (res<<9)& mask_all;
res |= (res<<9)& mask_all;
res |= (res<<9)& mask_all;
res |= (res<<9)& mask_all;
res |= (res<<9)& mask_all;
legal_board |= (res<<9)& vacant_board;
//右下がり斜め下
res = (player_board>>9) & mask_all;
res |= (res>>9)& mask_all;
res |= (res>>9)& mask_all;
res |= (res>>9)& mask_all;
res |= (res>>9)& mask_all;
res |= (res>>9)& mask_all;
legal_board |= (res >> 9 )& vacant_board;
//右下がり斜め上
res = (player_board<<7) & mask_all;
res |= (res<<7)& mask_all;
res |= (res<<7)& mask_all;
res |= (res<<7)& mask_all;
res |= (res<<7)& mask_all;
res |= (res<<7)& mask_all;
legal_board |= (res<<7)& vacant_board;
//右下がり斜め下
res = (player_board>>7) & mask_side;
res |= (res>>7)& mask_all;
res |= (res>>7)& mask_all;
res |= (res>>7)& mask_all;
res |= (res>>7)& mask_all;
res |= (res>>7)& mask_all;
legal_board |= (res >> 7 )& vacant_board;
return legal_board;  
}






};

int main(){
    board b;
b.player_board   = 0x0000000810000000;
b.opponent_board = 0x0000001008000000;
uint64_t l = b.legal();

cout << l << endl;





    return 0;
}