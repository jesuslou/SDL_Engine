#ifndef _INC_TIMER_H_
#define _INC_TIMER_H_

typedef float TTimeStamp;

class CTimer {
public:
  CTimer( );

  void start( );
  void stop( );
  void pause( );
  void unpause( );

  unsigned getTicks( );
  TTimeStamp elapsed( );

  bool isStarted( );
  bool isPaused( );

private:
  unsigned m_start_ticks;
  unsigned m_paused_ticks;

  bool m_paused;
  bool m_started;
};
#endif