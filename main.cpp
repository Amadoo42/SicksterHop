#pragma execution_charecter_set("utf-8")
#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
#include <Windows.h>
using namespace std;

#define         ull unsigned long long
#define         nl '\n'
#define         sp ' '

string empty_board = "8/8/8/8/8/8/8/8 w - - ";
string starting_position = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
string tricky_position = "r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R w KQkq - 0 1";
string killer_position = "rnbqkb1r/pp1p1pPp/8/2p1pP2/1P1P4/3P3P/P1P1P3/RNBQKBNR w KQkq e6 0 1";
string test_position = "r2q1rk1/ppp2ppp/2n1bn2/2b1p3/3pP3/3P1NPP/PPP1NB1/R1BQ1RK1 b - - 0";

enum {
    a8, b8, c8, d8, e8, f8, g8, h8,
    a7, b7, c7, d7, e7, f7, g7, h7,
    a6, b6, c6, d6, e6, f6, g6, h6,
    a5, b5, c5, d5, e5, f5, g5, h5,
    a4, b4, c4, d4, e4, f4, g4, h4,
    a3, b3, c3, d3, e3, f3, g3, h3,
    a2, b2, c2, d2, e2, f2, g2, h2,
    a1, b1, c1, d1, e1, f1, g1, h1, Null
};

enum { white, black, both };

const string square_to_coordinates[] {
    "a8", "b8", "c8", "d8", "e8", "f8", "g8", "h8",
    "a7", "b7", "c7", "d7", "e7", "f7", "g7", "h7",
    "a6", "b6", "c6", "d6", "e6", "f6", "g6", "h6",
    "a5", "b5", "c5", "d5", "e5", "f5", "g5", "h5",
    "a4", "b4", "c4", "d4", "e4", "f4", "g4", "h4",
    "a3", "b3", "c3", "d3", "e3", "f3", "g3", "h3",
    "a2", "b2", "c2", "d2", "e2", "f2", "g2", "h2",
    "a1", "b1", "c1", "d1", "e1", "f1", "g1", "h1"
};

ull bitboards[12], occupancies[3];
int side, enpassant = Null, castle;

enum { wk = 1, wq = 2, bk = 4, bq = 8 };

enum { P, N, B, R, Q, K, p, n, b, r, q, k };

const char ascii_pieces[] = "PNBRQKpnbrqk";
const char *unicode_pieces[] = { "\u2659", "\u2658", "\u2657", "\u2656", "\u2655", "\u2654", "\u265F", "\u265E", "\u265D", "\u265C", "\u265B", "\u265A" };

map <char, int> char_pieces = {
    {'P', P},
    {'N', N},
    {'B', B},
    {'R', R},
    {'Q', Q},
    {'K', K},
    {'p', p},
    {'n', n},
    {'b', b},
    {'r', r},
    {'q', q},
    {'k', k}
};

const int bishop_relevant_bits[] {
    6, 5, 5, 5, 5, 5, 5, 6, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 9, 9, 7, 5, 5, 
    5, 5, 7, 7, 7, 7, 5, 5, 
    5, 5, 5, 5, 5, 5, 5, 5, 
    6, 5, 5, 5, 5, 5, 5, 6
};

const int rook_relevant_bits[] {
    12, 11, 11, 11, 11, 11, 11, 12, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    11, 10, 10, 10, 10, 10, 10, 11, 
    12, 11, 11, 11, 11, 11, 11, 12
};

ull rook_magic_numbers[] = {
    0x8a80104000800020ULL,
    0x140002000100040ULL,
    0x2801880a0017001ULL,
    0x100081001000420ULL,
    0x200020010080420ULL,
    0x3001c0002010008ULL,
    0x8480008002000100ULL,
    0x2080088004402900ULL,
    0x800098204000ULL,
    0x2024401000200040ULL,
    0x100802000801000ULL,
    0x120800800801000ULL,
    0x208808088000400ULL,
    0x2802200800400ULL,
    0x2200800100020080ULL,
    0x801000060821100ULL,
    0x80044006422000ULL,
    0x100808020004000ULL,
    0x12108a0010204200ULL,
    0x140848010000802ULL,
    0x481828014002800ULL,
    0x8094004002004100ULL,
    0x4010040010010802ULL,
    0x20008806104ULL,
    0x100400080208000ULL,
    0x2040002120081000ULL,
    0x21200680100081ULL,
    0x20100080080080ULL,
    0x2000a00200410ULL,
    0x20080800400ULL,
    0x80088400100102ULL,
    0x80004600042881ULL,
    0x4040008040800020ULL,
    0x440003000200801ULL,
    0x4200011004500ULL,
    0x188020010100100ULL,
    0x14800401802800ULL,
    0x2080040080800200ULL,
    0x124080204001001ULL,
    0x200046502000484ULL,
    0x480400080088020ULL,
    0x1000422010034000ULL,
    0x30200100110040ULL,
    0x100021010009ULL,
    0x2002080100110004ULL,
    0x202008004008002ULL,
    0x20020004010100ULL,
    0x2048440040820001ULL,
    0x101002200408200ULL,
    0x40802000401080ULL,
    0x4008142004410100ULL,
    0x2060820c0120200ULL,
    0x1001004080100ULL,
    0x20c020080040080ULL,
    0x2935610830022400ULL,
    0x44440041009200ULL,
    0x280001040802101ULL,
    0x2100190040002085ULL,
    0x80c0084100102001ULL,
    0x4024081001000421ULL,
    0x20030a0244872ULL,
    0x12001008414402ULL,
    0x2006104900a0804ULL,
    0x1004081002402ULL
};

ull bishop_magic_numbers[] = {
    0x40040844404084ULL,
    0x2004208a004208ULL,
    0x10190041080202ULL,
    0x108060845042010ULL,
    0x581104180800210ULL,
    0x2112080446200010ULL,
    0x1080820820060210ULL,
    0x3c0808410220200ULL,
    0x4050404440404ULL,
    0x21001420088ULL,
    0x24d0080801082102ULL,
    0x1020a0a020400ULL,
    0x40308200402ULL,
    0x4011002100800ULL,
    0x401484104104005ULL,
    0x801010402020200ULL,
    0x400210c3880100ULL,
    0x404022024108200ULL,
    0x810018200204102ULL,
    0x4002801a02003ULL,
    0x85040820080400ULL,
    0x810102c808880400ULL,
    0xe900410884800ULL,
    0x8002020480840102ULL,
    0x220200865090201ULL,
    0x2010100a02021202ULL,
    0x152048408022401ULL,
    0x20080002081110ULL,
    0x4001001021004000ULL,
    0x800040400a011002ULL,
    0xe4004081011002ULL,
    0x1c004001012080ULL,
    0x8004200962a00220ULL,
    0x8422100208500202ULL,
    0x2000402200300c08ULL,
    0x8646020080080080ULL,
    0x80020a0200100808ULL,
    0x2010004880111000ULL,
    0x623000a080011400ULL,
    0x42008c0340209202ULL,
    0x209188240001000ULL,
    0x400408a884001800ULL,
    0x110400a6080400ULL,
    0x1840060a44020800ULL,
    0x90080104000041ULL,
    0x201011000808101ULL,
    0x1a2208080504f080ULL,
    0x8012020600211212ULL,
    0x500861011240000ULL,
    0x180806108200800ULL,
    0x4000020e01040044ULL,
    0x300000261044000aULL,
    0x802241102020002ULL,
    0x20906061210001ULL,
    0x5a84841004010310ULL,
    0x4010801011c04ULL,
    0xa010109502200ULL,
    0x4a02012000ULL,
    0x500201010098b028ULL,
    0x8040002811040900ULL,
    0x28000010020204ULL,
    0x6000020202d0240ULL,
    0x8918844842082200ULL,
    0x4010011029020020ULL
};

#define check_bit(bitboard, square) ((bitboard) & (1ULL << (square)))
#define set_bit(bitboard, square) ((bitboard) |= (1ULL << (square)))
#define unset_bit(bitboard, square) ((bitboard) &= ~(1ULL << (square)))
#define count_bits(bitboard) __builtin_popcountll((bitboard))
#define get_lsb_index(bitboard) (__builtin_ffsll((bitboard)) - 1)

void print_bitboard(ull bitboard) {
    for(int rank = 0; rank < 8; ++rank) {
        for(int file = 0; file < 8; ++file) {
            int square = rank * 8 + file;
            if(!file) cout << 8 - rank << "  ";
            cout << (check_bit(bitboard, square) ? 1 : 0) << sp;
        }
        cout << nl;
    }
    cout << "   a b c d e f g h\n";
    cout << "Bitboard: " << bitboard << nl;
}

const ull not_a_file = 18374403900871474942ULL, not_h_file = 9187201950435737471ULL, not_ab_file = 18229723555195321596ULL, not_gh_file = 4557430888798830399ULL;

ull pawn_attacks[2][64];

ull mask_pawn_attacks(int square, int side) {
    ull attacks = 0ULL, bitboard = 0ULL;
    set_bit(bitboard, square);
    if(!side) {
        attacks |= (not_a_file & (bitboard >> 7ULL) ? (bitboard >> 7ULL) : 0);
        attacks |= (not_h_file & (bitboard >> 9ULL) ? (bitboard >> 9ULL) : 0);
    }
    else {
        attacks |= (not_h_file & (bitboard << 7ULL) ? (bitboard << 7ULL) : 0);
        attacks |= (not_a_file & (bitboard << 9ULL) ? (bitboard << 9ULL) : 0);
    }
    return attacks;
}

ull knight_attacks[64];

ull mask_knight_attacks(int square) {
    ull attacks = 0ULL, bitboard = 0ULL;
    set_bit(bitboard, square);
    attacks |= (not_h_file & (bitboard >> 17ULL) ? (bitboard >> 17ULL) : 0);
    attacks |= (not_a_file & (bitboard >> 15ULL) ? (bitboard >> 15ULL) : 0);
    attacks |= (not_gh_file & (bitboard >> 10ULL) ? (bitboard >> 10ULL) : 0);
    attacks |= (not_ab_file & (bitboard >> 6ULL) ? (bitboard >> 6ULL) : 0);
    attacks |= (not_a_file & (bitboard << 17ULL) ? (bitboard << 17ULL) : 0);
    attacks |= (not_h_file & (bitboard << 15ULL) ? (bitboard << 15ULL) : 0);
    attacks |= (not_ab_file & (bitboard << 10ULL) ? (bitboard << 10ULL) : 0);
    attacks |= (not_gh_file & (bitboard << 6ULL) ? (bitboard << 6ULL) : 0);
    return attacks;
}

ull king_attacks[64];

ull mask_king_attacks(int square) {
    ull attacks = 0ULL, bitboard = 0ULL;
    set_bit(bitboard, square);
    attacks |= ((bitboard >> 8ULL) ? (bitboard >> 8ULL) : 0);
    attacks |= (not_h_file & (bitboard >> 9ULL) ? (bitboard >> 9ULL) : 0);
    attacks |= (not_a_file & (bitboard >> 7ULL) ? (bitboard >> 7ULL) : 0);
    attacks |= (not_h_file & (bitboard >> 1ULL) ? (bitboard >> 1ULL) : 0);
    attacks |= ((bitboard << 8ULL) ? (bitboard << 8ULL) : 0);
    attacks |= (not_a_file & (bitboard << 9ULL) ? (bitboard << 9ULL) : 0);
    attacks |= (not_h_file & (bitboard << 7ULL) ? (bitboard << 7ULL) : 0);
    attacks |= (not_a_file & (bitboard << 1ULL) ? (bitboard << 1ULL) : 0);
    return attacks;
}

void precalculate_leapers_attacks() {
    for(int square = 0; square < 64; ++square) {
        pawn_attacks[white][square] = mask_pawn_attacks(square, white);
        pawn_attacks[black][square] = mask_pawn_attacks(square, black);
        knight_attacks[square] = mask_knight_attacks(square);
        king_attacks[square] = mask_king_attacks(square);
    }
}

ull mask_bishop_attacks(int square) {
    ull attacks = 0ULL;
    int tr = square / 8, tf = square % 8;
    for(int r = tr + 1, f = tf + 1; r <= 6 && f <= 6; ++r, ++f) set_bit(attacks, r * 8 + f);
    for(int r = tr - 1, f = tf + 1; r >= 1 && f <= 6; --r, ++f) set_bit(attacks, r * 8 + f);
    for(int r = tr + 1, f = tf - 1; r <= 6 && f >= 1; ++r, --f) set_bit(attacks, r * 8 + f);
    for(int r = tr - 1, f = tf - 1; r >= 1 && f >= 1; --r, --f) set_bit(attacks, r * 8 + f);
    return attacks;
}

ull mask_rook_attacks(int square) {
    ull attacks = 0ULL;
    int tr = square / 8, tf = square % 8;
    for(int r = tr + 1; r <= 6; ++r) set_bit(attacks, r * 8 + tf);
    for(int r = tr - 1; r >= 1; --r) set_bit(attacks, r * 8 + tf);
    for(int f = tf + 1; f <= 6; ++f) set_bit(attacks, tr * 8 + f);
    for(int f = tf - 1; f >= 1; --f) set_bit(attacks, tr * 8 + f);
    return attacks;
}

ull bishop_attacks_on_the_fly(int square, ull block) {
    ull attacks = 0ULL;
    int tr = square / 8, tf = square % 8;
    for(int r = tr + 1, f = tf + 1; r <= 7 && f <= 7; ++r, ++f) {
        set_bit(attacks, r * 8 + f);
        if((1ULL << (r * 8 + f)) & block) break;
    }
    for(int r = tr - 1, f = tf + 1; r >= 0 && f <= 7; --r, ++f) {
        set_bit(attacks, r * 8 + f);
        if((1ULL << (r * 8 + f)) & block) break;
    }
    for(int r = tr + 1, f = tf - 1; r <= 7 && f >= 0; ++r, --f) {
        set_bit(attacks, r * 8 + f);
        if((1ULL << (r * 8 + f)) & block) break;
    }
    for(int r = tr - 1, f = tf - 1; r >= 0 && f >= 0; --r, --f) {
        set_bit(attacks, r * 8 + f);
        if((1ULL << (r * 8 + f)) & block) break;
    }
    return attacks;
}

ull rook_attacks_on_the_fly(int square, ull block) {
    ull attacks = 0ULL;
    int tr = square / 8, tf = square % 8;
    for(int r = tr + 1; r <= 7; ++r) {
        set_bit(attacks, r * 8 + tf);
        if((1ULL << (r * 8 + tf)) & block) break;
    }
    for(int r = tr - 1; r >= 0; --r) {
        set_bit(attacks, r * 8 + tf);
        if((1ULL << (r * 8 + tf)) & block) break;
    }
    for(int f = tf + 1; f <= 7; ++f) {
        set_bit(attacks, tr * 8 + f);
        if((1ULL << (tr * 8 + f)) & block) break;
    }
    for(int f = tf - 1; f >= 0; --f) {
        set_bit(attacks, tr * 8 + f);
        if((1ULL << (tr * 8 + f)) & block) break;
    }
    return attacks;
}

ull set_occupancy(int index, ull attack_mask) {
    ull occupancy = 0ULL;
    int n = count_bits(attack_mask);
    for(int i = 0; i < n; ++i) {
        int square = get_lsb_index(attack_mask);
        unset_bit(attack_mask, square);
        if(index & (1ULL << i)) occupancy |= (1ULL << square);
    }
    return occupancy;
}

ull bishop_masks[64], rook_masks[64], bishop_attacks[64][512], rook_attacks[64][4096];

void precalculate_sliders_attacks() {
    for(int square = 0; square < 64; ++square) {
        ull bishop_attack_mask, rook_attack_mask;
        bishop_attack_mask = bishop_masks[square] = mask_bishop_attacks(square);
        rook_attack_mask = rook_masks[square] = mask_rook_attacks(square);
        int cnt_bishop = count_bits(bishop_attack_mask), cnt_rook = count_bits(rook_attack_mask);
        for(int i = 0; i < (1 << cnt_bishop); ++i) {
            ull occupancy = set_occupancy(i, bishop_attack_mask);
            int magic_index = (occupancy * bishop_magic_numbers[square]) >> (64 - bishop_relevant_bits[square]);
            bishop_attacks[square][magic_index] = bishop_attacks_on_the_fly(square, occupancy);
        }
        for(int i = 0; i < (1 << cnt_rook); ++i) {
            ull occupancy = set_occupancy(i, rook_attack_mask);
            int magic_index = (occupancy * rook_magic_numbers[square]) >> (64 - rook_relevant_bits[square]);
            rook_attacks[square][magic_index] = rook_attacks_on_the_fly(square, occupancy);
        } 
    }
}

ull get_bishop_attacks(int square, ull occupancy) {
    occupancy &= bishop_masks[square];
    occupancy *= bishop_magic_numbers[square];
    occupancy >>= (64 - bishop_relevant_bits[square]);
    return bishop_attacks[square][occupancy];
}

ull get_rook_attacks(int square, ull occupancy) {
    occupancy &= rook_masks[square];
    occupancy *= rook_magic_numbers[square];
    occupancy >>= (64 - rook_relevant_bits[square]);
    return rook_attacks[square][occupancy];
}

ull get_queen_attacks(int square, ull occupancy) {
    return (get_bishop_attacks(square, occupancy) | get_rook_attacks(square, occupancy));
}

void print_board() {
    for(int rank = 0; rank < 8; ++rank) {
        for(int file = 0; file < 8; ++file) {
            int square = rank * 8 + file, piece = -1;
            if(!file) cout << 8 - rank << sp;
            for(int i = P; i <= k; ++i) {
                if(check_bit(bitboards[i], square)) piece = i;
            }
            if(piece == -1) cout << ". ";
            else cout << ascii_pieces[piece] << sp;
        }
        cout << nl;
    }
    cout << "  a b c d e f g h\n";
    cout << "Side: " << (!side ? "White" : "Black") << nl;
    cout << "Enpassant: " << (enpassant == Null ? "Null" : square_to_coordinates[enpassant]) << nl;
    cout << "Castling: " << ((castle & wk) ? 'K' : '-') << ((castle & wq) ? 'Q' : '-') << ((castle & bk) ? 'k' : '-') << ((castle & bq) ? 'q' : '-') << nl;
}
    
int fifty;

static inline void parse_fen(char *fen) {
    for(int sqr = 0; sqr < 64 && *fen != ' '; ) {
        if((*fen >= 'b' && *fen <= 'r') || (*fen >= 'B' && *fen <= 'R')) {
            int piece;
            if(*fen == 'P') piece = P;
            else if(*fen == 'N') piece = N;
            else if(*fen == 'B') piece = B;
            else if(*fen == 'R') piece = R;
            else if(*fen == 'Q') piece = Q;
            else if(*fen == 'K') piece = K;
            else if(*fen == 'p') piece = p;
            else if(*fen == 'n') piece = n;
            else if(*fen == 'b') piece = b;
            else if(*fen == 'r') piece = r;
            else if(*fen == 'q') piece = q;
            else if(*fen == 'k') piece = k;
            set_bit(bitboards[piece], sqr);
            fen++;
        }
        else if(*fen >= '0' && *fen <= '9') sqr += (*fen - '0'), fen++;
        else if(*fen == '/') fen++;
    }
    fen++;
    side = (*fen == 'w' ? white : black);
    fen += 2;
    while(*fen != ' ') {
        if(*fen == 'K') castle |= wk;
        else if(*fen == 'Q') castle |= wq;
        else if(*fen == bk) castle |= bk;
        else if(*fen == bq) castle |= bq;
        else if(*fen == '-') { fen++; break; }
        fen++;
    }
    fen++;
    if(*fen == '-') enpassant = Null;
    else {
        int file = (fen[0] - 'a'), rank = (8 - (fen[1] - '0'));
        enpassant = rank * 8 + file;
    }
    fen++;
    fifty = atoi(fen);
    for(int piece = P; piece <= K; ++piece) occupancies[white] |= occupancies[piece];
    for(int piece = p; piece <= k; ++piece) occupancies[black] |= occupancies[piece];
    occupancies[both] |= (occupancies[white] | occupancies[black]);
}

bool is_square_attacked(int square, int side) {
    if((side == white) && (pawn_attacks[black][square] & bitboards[P])) return 1;
    if((side == black) && (pawn_attacks[white][square] & bitboards[p])) return 1;
    if(knight_attacks[square] & ((side == white) ? bitboards[N] : bitboards[n])) return 1;
    if(king_attacks[square] & ((side == white) ? bitboards[K] : bitboards[k])) return 1;
    if(get_bishop_attacks(square, occupancies[both]) & ((side == white) ? bitboards[B] : bitboards[b])) return 1;
    if(get_rook_attacks(square, occupancies[both]) & ((side == white) ? bitboards[R] : bitboards[r])) return 1;
    if(get_queen_attacks(square, occupancies[both]) & ((side == white) ? bitboards[Q] : bitboards[q])) return 1;
    return 0;
}

void print_attacked_squares(int side) {
    for(int rank = 0; rank < 8; ++rank) {
        for(int file = 0; file < 8; ++file) {
            int square = rank * 8 + file, piece = -1;
            if(!file) cout << 8 - rank << sp;
            cout << ((is_square_attacked(square, side)) ? 1 : 0) << sp;
        }
        cout << nl;
    }
    cout << "  a b c d e f g h\n";
}

#define encode_move(source, target, piece, promoted, capture, Double, enpassant, castling) (source) | (target << 6) | (piece << 12) | (promoted << 16) | (capture << 20) | (Double << 21) | (enpassant << 22) | (castling << 23) 
#define get_move_source(move) (move & 0x3f)
#define get_move_target(move) ((move & 0xfc0) >> 6)
#define get_move_piece(move) ((move & 0xf000) >> 12)
#define get_move_promoted(move) ((move & 0xf0000) >> 16)
#define get_move_capture(move) (move & 0x100000)
#define get_move_double(move) (move & 0x200000)
#define get_move_enpassant(move) (move & 0x400000)
#define get_move_castling(move) (move & 0x800000)

typedef struct {
    int moves[256], cnt = 0;
} moves;

void add_move(moves &move_list, int move) {
    move_list.moves[move_list.cnt] = move;
    move_list.cnt++;
}

map <int, char> promoted_pieces = {
    {Q, 'q'},
    {R, 'r'},
    {B, 'b'},
    {N, 'n'},
    {q, 'q'},
    {r, 'r'},
    {b, 'b'},
    {n, 'n'}
};

void print_move(int move) {
    cout << square_to_coordinates[get_move_source(move)] << square_to_coordinates[get_move_target(move)] ;
    int promoted = get_move_promoted(move);
    if(promoted) cout << promoted_pieces[promoted];
}

void print_move_list(moves &move_list) {
    if(!move_list.cnt) return void(cout << "No moves found.\n");
    cout << "      Move      Piece      Capture      Double      Enpassant      Castling\n\n";
    for(int i = 0; i < move_list.cnt; ++i) {
        int move = move_list.moves[i];
        cout << "      " << square_to_coordinates[get_move_source(move)] << square_to_coordinates[get_move_target(move)];
        char promoted_piece = promoted_pieces[get_move_promoted(move)];
        cout << (promoted_piece ? promoted_piece : ' ');
        cout << "       " << unicode_pieces[get_move_piece(move)];
        cout << "           " << (get_move_capture(move) ? 1 : 0);
        cout << "           " << (get_move_double(move) ? 1 : 0);
        cout << "             " << (get_move_enpassant(move) ? 1 : 0);
        cout << "             " << (get_move_castling(move) ? 1 : 0) << nl;
    }
    cout << "\n\n      Total number of moves: " << (int)(move_list.cnt) << nl;
}

void generate_moves(moves &move_list) {
    move_list.cnt = 0;
    int source_square, target_square;
    for(int piece = P; piece <= k; ++piece) {
        ull bitboard = bitboards[piece];
        if(side == white) {
            if(piece == P) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    target_square = source_square - 8;
                    if(!(target_square < 0) && !check_bit(occupancies[both], target_square)) {
                        if(source_square >= a7 && source_square <= h7) {
                            add_move(move_list, encode_move(source_square, target_square, piece, Q, 0, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, R, 0, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, B, 0, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, N, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                            if((source_square >= a2 && source_square <= h2) && !check_bit(occupancies[both], target_square - 8)) {
                                add_move(move_list, encode_move(source_square, target_square - 8, piece, 0, 0, 1, 0, 0));
                            }
                        }
                    }
                    ull attacks = pawn_attacks[white][source_square] & occupancies[black];
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(source_square >= a7 && source_square <= h7) {
                            add_move(move_list, encode_move(source_square, target_square, piece, Q, 1, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, R, 1, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, B, 1, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, N, 1, 0, 0, 0));
                        }
                        else add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        unset_bit(attacks, target_square);
                    }
                    if(enpassant != Null) {
                        ull enpassant_attacks = pawn_attacks[white][source_square] & (1ULL << enpassant);
                        if(enpassant_attacks) {
                            target_square = get_lsb_index(enpassant_attacks);
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 1, 0));
                        }
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == K) {
                if(castle & wk) {
                    if(!check_bit(occupancies[both], f1) && !check_bit(occupancies[both], g1)) {
                        if(!is_square_attacked(e1, black) && !is_square_attacked(f1, black)) {
                            add_move(move_list, encode_move(e1, g1, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }
                if(castle & wq) {
                    if(!check_bit(occupancies[both], d1) && !check_bit(occupancies[both], c1) && !check_bit(occupancies[both], b1)) {
                        if(!is_square_attacked(e1, black) && !is_square_attacked(d1, black)) {
                            add_move(move_list, encode_move(e1, c1, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = king_attacks[source_square] & ~(occupancies[white]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[black], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == N) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = knight_attacks[source_square] & ~(occupancies[white]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[black], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == B) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = get_bishop_attacks(source_square, occupancies[both]) & ~(occupancies[white]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[black], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == R) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = get_rook_attacks(source_square, occupancies[both]) & ~(occupancies[white]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[black], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == Q) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = get_queen_attacks(source_square, occupancies[both]) & ~(occupancies[white]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[black], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
        }
        else {
            if(piece == p) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    target_square = source_square + 8;
                    if(!(target_square > h1) && !check_bit(occupancies[both], target_square)) {
                        if(source_square >= a2 && source_square <= h2) {
                            add_move(move_list, encode_move(source_square, target_square, piece, q, 0, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, r, 0, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, b, 0, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, n, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                            if((source_square >= a7 && source_square <= h7) && !check_bit(occupancies[both], target_square + 8)) {
                                add_move(move_list, encode_move(source_square, target_square + 8, piece, 0, 0, 1, 0, 0));
                            }
                        }
                    }
                    ull attacks = pawn_attacks[black][source_square] & occupancies[white];
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(source_square >= a2 && source_square <= h2) {
                            add_move(move_list, encode_move(source_square, target_square, piece, q, 1, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, r, 1, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, b, 1, 0, 0, 0));
                            add_move(move_list, encode_move(source_square, target_square, piece, n, 1, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    if(enpassant != Null) {
                        ull enpassant_attacks = pawn_attacks[black][source_square] & (1ULL << enpassant);
                        if(enpassant_attacks) {
                            target_square = get_lsb_index(enpassant_attacks);
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 1, 0));
                        }
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == k) {
                if(castle & bk) {
                    if(!check_bit(occupancies[both], f8) && !check_bit(occupancies[both], g8)) {
                        if(!is_square_attacked(e8, white) && !is_square_attacked(f8, white)) {
                            add_move(move_list, encode_move(e8, g8, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }
                if(castle & bq) {
                    if(!check_bit(occupancies[both], d8) && !check_bit(occupancies[both], c8) && !check_bit(occupancies[both], b8)) {
                        if(!is_square_attacked(e8, white) && !is_square_attacked(d8, white)) {
                            add_move(move_list, encode_move(e8, c8, piece, 0, 0, 0, 0, 1));
                        }
                    }
                }
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = king_attacks[source_square] & ~(occupancies[black]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[white], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == n) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = knight_attacks[source_square] & ~(occupancies[black]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[white], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == b) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = get_bishop_attacks(source_square, occupancies[both]) & ~(occupancies[black]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[white], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == r) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = get_rook_attacks(source_square, occupancies[both]) & ~(occupancies[black]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[white], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
            if(piece == q) {
                while(bitboard) {
                    source_square = get_lsb_index(bitboard);
                    ull attacks = get_queen_attacks(source_square, occupancies[both]) & ~(occupancies[black]);
                    while(attacks) {
                        target_square = get_lsb_index(attacks);
                        if(!check_bit(occupancies[white], target_square)) {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 0, 0, 0, 0));
                        }
                        else {
                            add_move(move_list, encode_move(source_square, target_square, piece, 0, 1, 0, 0, 0));
                        }
                        unset_bit(attacks, target_square);
                    }
                    unset_bit(bitboard, source_square);
                }
            }
        }
    }
}

#define copy_board()                                                                \
    ull bitboards_copy[12], occupancies_copy[3];                                    \
    int side_copy, enpassant_copy, castle_copy;                                     \
    memcpy(bitboards_copy, bitboards, 96);                                          \
    memcpy(occupancies_copy, occupancies, 24);                                      \
    side_copy = side, enpassant_copy = enpassant, castle_copy = castle;             \

#define take_back()                                                                 \
    memcpy(bitboards, bitboards_copy, 96);                                          \
    memcpy(occupancies, occupancies_copy, 24);                                      \
    side = side_copy, enpassant = enpassant_copy, castle = castle_copy;             \

enum { all_moves, only_captures };

const int castling_rights[64] = {
     7, 15, 15, 15,  3, 15, 15, 11,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    15, 15, 15, 15, 15, 15, 15, 15,
    13, 15, 15, 15, 12, 15, 15, 14
};

bool make_move(int move, bool move_flag) {
    if(move_flag == all_moves) {
        copy_board();
        int source_square = get_move_source(move);
        int target_square = get_move_target(move);
        int piece = get_move_piece(move);
        int promoted_piece = get_move_promoted(move);
        bool capture = get_move_capture(move);
        bool double_push = get_move_double(move);
        bool is_enpassant = get_move_enpassant(move);
        bool castling = get_move_castling(move);
        unset_bit(bitboards[piece], source_square);
        set_bit(bitboards[piece], target_square);
        if(capture) {
            int start_piece, end_piece;
            if(side == white) start_piece = p, end_piece = k;
            else start_piece = P, end_piece = K;
            for(int piece = start_piece; piece <= end_piece; ++piece) {
                if(check_bit(bitboards[piece], target_square)) { unset_bit(bitboards[piece], target_square); break; }
            }
        }
        if(promoted_piece) {
            unset_bit(bitboards[piece], target_square);
            set_bit(bitboards[promoted_piece], target_square);
        }
        if(is_enpassant) {
            if(side == white) unset_bit(bitboards[p], target_square + 8);
            else unset_bit(bitboards[P], target_square - 8);
        }
        enpassant = Null;
        if(double_push) {
            if(side == white) enpassant = target_square + 8;
            else enpassant = target_square - 8;
        }
        if(castling) {
            if(target_square == g1) unset_bit(bitboards[R], h1), set_bit(bitboards[R], f1);
            if(target_square == c1) unset_bit(bitboards[R], a1), set_bit(bitboards[R], d1);
            if(target_square == g8) unset_bit(bitboards[r], h8), set_bit(bitboards[r], f8);
            if(target_square == c8) unset_bit(bitboards[r], a8), set_bit(bitboards[r], d8);
        }
        castle &= ((castling_rights[source_square]) & (castling_rights[target_square]));
        memset(occupancies, 0ULL, 24);
        for(int piece = P; piece <= K; ++piece) occupancies[white] |= bitboards[piece];
        for(int piece = p; piece <= k; ++piece) occupancies[black] |= bitboards[piece];
        occupancies[both] |= (occupancies[white] | occupancies[black]);
        side ^= 1;
        if(is_square_attacked((side == white ? get_lsb_index(bitboards[k]) : get_lsb_index(bitboards[K])), side)) {
            take_back();
            return 0;
        }
        else return 1;
    }
    else {
        if(get_move_capture(move)) { make_move(move, all_moves); return 1; }
        else return 0;
    }
}

ull nodes = 0, cnt = 0;

void perft_driver(int depth) {
    if(!depth) { nodes++; return; }
    moves move_list;
    generate_moves(move_list);
    for(int i = 0; i < move_list.cnt; ++i) {
        copy_board();
        if(!make_move(move_list.moves[i], all_moves)) continue;
        perft_driver(depth - 1);
        take_back();
    }
}

int material_score[] { 100, 300, 350, 500, 1000, 10000, -100, -300, -350, -500, -1000, -10000 };

const int pawn_score[64] {
    90,  90,  90,  90,  90,  90,  90,  90,
    30,  30,  30,  40,  40,  30,  30,  30,
    20,  20,  20,  30,  30,  30,  20,  20,
    10,  10,  10,  20,  20,  10,  10,  10,
     5,   5,  10,  20,  20,   5,   5,   5,
     0,   0,   0,   5,   5,   0,   0,   0,
     0,   0,   0, -10, -10,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0
};

const int knight_score[64] = {
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   0,   0,  10,  10,   0,   0,  -5,
    -5,   5,  20,  20,  20,  20,   5,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,  10,  20,  30,  30,  20,  10,  -5,
    -5,   5,  20,  10,  10,  20,   5,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5, -10,   0,   0,   0,   0, -10,  -5
};

const int bishop_score[64] {
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,  10,  10,   0,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,  10,   0,   0,   0,   0,  10,   0,
     0,  30,   0,   0,   0,   0,  30,   0,
     0,   0, -10,   0,   0, -10,   0,   0

};

const int rook_score[64] {
    50,  50,  50,  50,  50,  50,  50,  50,
    50,  50,  50,  50,  50,  50,  50,  50,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,  10,  20,  20,  10,   0,   0,
     0,   0,   0,  20,  20,   0,   0,   0

};

const int king_score[64] {
     0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   5,   5,   5,   5,   0,   0,
     0,   5,   5,  10,  10,   5,   5,   0,
     0,   5,  10,  20,  20,  10,   5,   0,
     0,   5,  10,  20,  20,  10,   5,   0,
     0,   0,   5,  10,  10,   5,   0,   0,
     0,   5,   5,  -5,  -5,   0,   5,   0,
     0,   0,   5,   0, -15,   0,  10,   0
};

const int mirror_score[128] {
	a1, b1, c1, d1, e1, f1, g1, h1,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a8, b8, c8, d8, e8, f8, g8, h8
};

int evaluate() {
    int score = 0, piece, square;
    ull bitboard;
    for(int piece = P; piece <= k; ++piece) {
        bitboard = bitboards[piece];
        while(bitboard) {
            square = get_lsb_index(bitboard);
            score += material_score[piece];
            if(piece == P) score += pawn_score[square];
            else if(piece == N) score += knight_score[square];
            else if(piece == B) score += bishop_score[square];
            else if(piece == R) score += rook_score[square];
            else if(piece == K) score += king_score[square];
            else if(piece == p) score -= pawn_score[mirror_score[square]];
            else if(piece == n) score -= knight_score[mirror_score[square]];
            else if(piece == b) score -= bishop_score[mirror_score[square]];
            else if(piece == r) score -= rook_score[mirror_score[square]];
            else if(piece == k) score -= king_score[mirror_score[square]];
            unset_bit(bitboard, square);
        }
    }
    return (side == white ? score : -score);
}

int ply, best_move;

int negamax(int alpha, int beta, int depth) {
    cout << depth << sp << alpha << sp << beta << sp << ply << nl;
    if(!depth) return evaluate();
    nodes++;
    int best_so_far, old_alpha = alpha;
    moves move_list;
    generate_moves(move_list);
    for(int i = 0; i < move_list.cnt; ++i) {
        copy_board();
        ply++;
        if(!make_move(move_list.moves[i], all_moves)) {
            ply--;
            continue;
        }
        int score = -negamax(-beta, -alpha, depth - 1);
        ply--;
        take_back();
        if(score >= beta) return beta;
        if(score > alpha) { 
            cout << "Alpha updated: " << score << nl;
            print_board();
            alpha = score;
            if(ply == 0) {
                best_so_far = move_list.moves[i];
                cout << "Best so far updated: " << best_so_far << nl;
            }
        }
    }
    if(old_alpha != alpha) best_move = best_so_far;
    return alpha;
}

int parse_move(string move) {
    moves move_list;
    generate_moves(move_list);
    int source_square = (move[0] - 'a') + (8 - (move[1] - '0')) * 8;
    int target_square = (move[2] - 'a') + (8 - (move[3] - '0')) * 8;
    for(int i = 0; i < move_list.cnt; ++i) {
        int Move = move_list.moves[i];
        if(source_square == get_move_source(Move) && target_square == get_move_target(Move)) {
            int promoted_piece = get_move_promoted(Move);
            if(((promoted_piece == Q || promoted_piece == q) && move[4] == 'q') || ((promoted_piece == R || promoted_piece == r) && move[4] == 'r') || ((promoted_piece == B || promoted_piece == b) && move[4] == 'b') || ((promoted_piece == N || promoted_piece == n) && move[4] == 'n')) return Move;
            return Move;
        }
    }
    return 0;
}

// void parse_position(char command) {
//     int idx = 9;
//     if(command[idx] == 's') {
//         parse_fen(starting_position);
//     }
//     else {
//         string fen = command.substr(13);
//         parse_fen(fen);
//     }
//     int moves_idx = command.find("moves");
//     if(moves_idx != -1) {
//         string Moves = command.substr(moves_idx + 6);
//         Moves += ' ';
//         int last = 0;
//         for(int i = 0; i < (int)Moves.size(); ++i) {
//             if(Moves[i] == ' ') {
//                 int move = parse_move(Moves.substr(last, i - last));
//                 if(!move) { cout << "ILLEGAL MOVE!\n"; continue; }
//                 last = i + 1;
//                 make_move(move, all_moves);
//             }
//         }
//     }
//     print_board();
// }

void search_position(int depth) {
    int score = negamax(-50000, 50000, depth);
    if(best_move) {
        cout << "bestmove ";
        print_move(best_move);
        cout << endl;
    }
}

void parse_go(string command) {
    int depth = 2;
    search_position(depth);
}

// void uci_loop() {
//     while(1) {
//         string s;
//         getline(cin, s);
//         if(s == "isready") { cout << "readyok" << endl; continue; }
//         if(s[0] == 'p' && s[1] == 'o') { parse_position(s); continue; }
//         if(s[0] == 'g') { parse_go(s); continue; }
//         if(s[0] == 'q') break;
//         if((int)s.size() == 3 && s == "uci") {
//             cout << "id name SicksterHop" << endl;
//             cout << "id author Amadoo" << endl;
//             cout << "uciok" << endl;
//             continue;
//         }
//     }
// }

int main() {
    SetConsoleOutputCP(65001);
    precalculate_leapers_attacks();
    precalculate_sliders_attacks();
    bool debug = 1;
    if(debug) {
        // cout << "Debugging\n";
        parse_fen("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        print_board();
    }
    else ;//uci_loop();
    return 0;
}


