<h1 align="center">Sickster Hop</h1>

A UCI chess engine written in C++. If you find this repository, come play me on lichess!

[Play me on Lichess](https://lichess.org/@/SicksterHop)

# Features
- Board representation  
  - [Bitboards](https://en.wikipedia.org/wiki/Bitboard)
- Move generation  
  - [Fancy magic bitboard hashing](https://www.chessprogramming.org/Magic_Bitboards#Fancy)
- Search  
  - [Principal Variation Search](https://www.chessprogramming.org/Principal_Variation_Search)  
  - [Lazy SMP](https://www.chessprogramming.org/Lazy_SMP)  
  - [Iterative Deepening](https://en.wikipedia.org/wiki/Iterative_deepening_depth-first_search)  
  - [Quiescence Search](https://en.wikipedia.org/wiki/Quiescence_search)  
  - [Aspiration Windows](https://www.chessprogramming.org/Aspiration_Windows)  
  - [Reverse Futility Pruning](https://www.chessprogramming.org/Reverse_Futility_Pruning)  
  - [Null Move Pruning](https://www.chessprogramming.org/Null_Move_Pruning)  
  - [Check Extensions](https://www.chessprogramming.org/Check_Extensions)
- [NNUE Evaluation](https://www.chessprogramming.org/NNUE)
- Move ordering  
  - [Hash Move](https://www.chessprogramming.org/Hash_Move)  
  - [Static Exchange Evaluation](https://www.chessprogramming.org/Static_Exchange_Evaluation)  
  - [Killer Heuristic](https://www.chessprogramming.org/Killer_Heuristic)  
  - [History Heuristic](https://www.chessprogramming.org/History_Heuristic)
- Other  
  - [Zobrist Hashing](https://www.chessprogramming.org/Zobrist_Hashing) / [Transposition Table](https://en.wikipedia.org/wiki/Transposition_table)
