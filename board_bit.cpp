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

inline uint64_t legal(){
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

inline board move(const uint64_t p){
    board res;
    uint64_t rev_ = 0;
    res.player_board = this<-player_board;
    res.opponent_board = this<-opponent_board;

     for (int k = 0; k < 8; ++k) {
            uint64_t rev_ = 0;
            uint64_t mask = make_mask(p, k);

            while (mask != 0 && (mask & opponent_board) != 0) {
                rev_ |= mask;
                mask = transfer(mask, k);
            }

            if ((mask & player_board) != 0) {
                rev |= rev_;
            }
        }

        res.player_board  ^= put | rev;
        opponent_board ^= rev;
        res.player = 1 - this<-player;
        return res;

    }
    


}
private:

inline uint64_t make_mask(uint64_t put, int k) const {
        switch (k) {
        case 0: // 上
            return (put << 8) & 0xffffffffffffff00ULL;
        case 1: // 右上
            return (put << 7) & 0x7f7f7f7f7f7f7f00ULL;
        case 2: // 右
            return (put >> 1) & 0x7f7f7f7f7f7f7f7fULL;
        case 3: // 右下
            return (put >> 9) & 0x007f7f7f7f7f7f7fULL;
        case 4: // 下
            return (put >> 8) & 0x00ffffffffffffffULL;
        case 5: // 左下
            return (put >> 7) & 0x00fefefefefefefeULL;
        case 6: // 左
            return (put << 1) & 0xfefefefefefefefeULL;
        case 7: // 左上
            return (put << 9) & 0xfefefefefefe00ULL;
        default:
            return 0ULL;
        }
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