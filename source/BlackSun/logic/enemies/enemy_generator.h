#ifndef _INC_ENEMY_GENERATOR_H_
#define _INC_ENEMY_GENERATOR_H_

class CBoard;

class CEnemyGenerator {
public:
  CEnemyGenerator( );

  bool init( CBoard *board_p1, CBoard *board_p2, float time_between_enemies );
  void destroy( );
  
  void update( float elapsedd );

  void reset( );

  void spawnEnemies( );

private:

  CBoard *m_board_p1;
  CBoard *m_board_p2;

  float m_time;
  float m_time_between_enemies;
  
  float m_global_acc_time;
};

#endif