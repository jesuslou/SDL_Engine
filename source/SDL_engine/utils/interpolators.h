#ifndef _INTERPOLATORS_H_
#define _INTERPOLATORS_H_

#include <math.h>

class IInterpolation { };

////////////
// LINEAR //
////////////

class LerpInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    return end*factor + begin*( 1 - factor );
  }
};

/////////////////
/// QUADRATIC ///
/////////////////

class EaseInQuadInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return c*factor*factor + begin;
  }
};

class EaseOutQuadInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return -c * factor * ( factor - 2.f ) + begin;
  }
};


class EaseInOutQuadInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float t = factor * 2.f;
    if( t < 1.f ) return ( ( c*0.5f )*t*t ) + begin;
    const float tm = t - 1;
    return -( c * 0.5f ) * ( ( ( t - 2.f )*( tm ) ) - 1.f ) + begin;
  }
};

/////////////
/// CUBIC ///
/////////////

class EaseInCubicInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return c*factor*factor*factor + begin;
  }
};

class EaseOutCubicInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    const float factor2 = factor - 1;
    return c*( factor2*factor2*factor2 + 1 ) + begin;
  }
};

class EaseInOutCubicInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float factor2 = 2 * factor;
    if( factor2 < 1 ) return c / 2 * factor2*factor2*factor2 + begin;
    factor2 -= 2;
    return c / 2 * ( factor2*factor2*factor2 + 2 ) + begin;
  }
};

/////////////
/// QUART ///
/////////////

class EaseInQuartInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return c*factor*factor*factor*factor + begin;
  }
};

class EaseOutQuartInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    const float t = factor - 1;
    return -c * ( t*t*t*t - 1.f ) + begin;
  }
};

class EaseInOutQuartInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float t = factor * 2.f;
    if( t < 1.f ) return c * 0.5f *t*t*t*t + begin;
    t -= 2.f;
    return -c*0.5f * ( ( t ) *t*t*t - 2.f ) + begin;
  }
};

/////////////
/// QUINT ///
/////////////

class EaseInQuintInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return c*factor*factor*factor*factor*factor + begin;
  }
};

class EaseOutQuintInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float factor2 = factor - 1.f;
    return c*( ( factor2 ) *factor2*factor2*factor2*factor2 + 1.f ) + begin;
  }
};

class EaseInOutQuintInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float t = factor * 2.f;
    if( t < 1.f ) return c * 0.5f *t*t*t*t*t + begin;
    t -= 2.f;
    return c*0.5f*( ( t ) *t*t*t*t + 2.f ) + begin;
  }
};


////////////
/// BACK ///
////////////

class EaseInBackInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float s = 1.70158f;
    return c*( factor ) *factor*( ( s + 1 )*factor - s ) + begin;
  }
};

class EaseOutBackInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    const float s = 1.70158f;
    const float factor2 = factor - 1;
    return c*( factor2*factor2*( ( s + 1 )*factor2 + s ) + 1 ) + begin;
  }
};


class EaseInOutBackInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float s = 1.70158f;
    s *= ( 1.525f );
    float factor2 = factor;
    if( ( factor2 *= 2 ) < 1 ) return c / 2 * ( factor2*factor2*( ( ( s ) +1 )*factor2 - s ) ) + begin;
    const float postFix = factor2 -= 2;
    return c / 2 * ( ( postFix ) *factor2*( ( ( s ) +1 )*factor2 + s ) + 2 ) + begin;
  }
};

///////////////
/// ELASTIC ///
///////////////

class EaseInElasticInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    const float p = 0.3f;
    const T a = c;
    const float s = p*0.25f;
    float factor2 = factor;
    const T postFix = a*powf( 2.f, 10.f*( factor2 -= 1 ) ); // this is a fix, again, with post-increment operators
    return -( postFix * sinf( ( float ) ( ( factor2 - s )*( 2 * M_PI ) / p ) ) ) + begin;
  }
};

class EaseOutElasticInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    const float p = 0.3f;
    const T a = c;
    const float s = p*0.25f;
    return ( a*powf( 2.f, -10 * factor ) * sinf( ( float ) ( ( factor - s )*( 2 * M_PI ) / p ) ) + c + begin );
  }
};

class EaseInOutElasticInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    float factor2 = 2 * factor;
    const T c = end - begin;
    const float p = ( .3f*1.5f );
    const T a = c;
    const float s = p*0.25f;

    if( factor2 < 1 ) {
      const T postFix = a*powf( 2.f, 10.f*( factor2 -= 1 ) ); // postIncrement is evil
      return -.5f*( postFix* sinf( ( float ) ( ( factor2 - s )*( 2 * M_PI ) / p ) ) ) + begin;
    }
    const T postFix = a*powf( 2.f, -10.f*( factor2 -= 1 ) ); // postIncrement is evil
    return postFix * sinf( ( float ) ( ( factor2 - s )*( 2 * M_PI ) / p ) )*.5f + c + begin;
  }
};


//////////////
/// BOUNCE ///
//////////////

class EaseOutBounceInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    if( factor < ( 1.f / 2.75f ) ) return c * ( 7.5625f * factor * factor ) + begin;
    if( factor < ( 2 / 2.75f ) ) {
      const float t = factor - ( 1.5f / 2.75f );
      return c*( 7.5625f*t*t + .75f ) + begin;
    }
    if( factor < ( 2.5 / 2.75 ) ) {
      const float t = factor - ( 2.25f / 2.75f );
      return c*( 7.5625f*t*t + .9375f ) + begin;
    }

    const float t = factor - ( 2.625f / 2.75f );
    return c*( 7.5625f*t*t + .984375f ) + begin;
  }
};

class EaseInBounceInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    //const T c = end - begin;
    EaseOutBounceInterpolation easeOut;
    //return c - easeOut(0.f,c,1.0f-factor) + begin;
    return easeOut( end, begin, 1.0f - factor );
  }
};

class EaseInOutBounceInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    //const T c = end - begin;
    const T m = ( begin + end ) * 0.5f;
    EaseOutBounceInterpolation easeOut;
    EaseInBounceInterpolation easeIn;
    if( factor < 0.5f ) return easeIn( begin, m, factor*2.f );
    return easeOut( m, end, factor*2.f - 1.f );
    //if (factor < 0.5f) return easeIn(0.f,c,factor*2.f) * 0.5f + begin;
    //return easeOut(0.f, c,factor*2.f - 1.f) * 0.5f + c*0.5f + begin; 
  }
};

////////////////
/// CIRCULAR ///
////////////////

class EaseInCircInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return -c * ( std::sqrt( 1.f - factor * factor ) - 1.f ) + begin;
  }
};

class EaseOutCircInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    const float t = factor - 1.f;
    return c * std::sqrt( 1.f - t*t ) + begin;
  }
};


class EaseInOutCircInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float t = factor * 2.f;
    if( t < 1.f ) return -c*0.5f * ( sqrtf( 1.f - t*t ) - 1.f ) + begin;
    const float t2 = t - 2.f;
    return c*0.5f * ( sqrtf( 1.f - t*( t2 ) ) + 1.f ) + begin;
  }
};

////////////
/// EXPO ///
////////////

class EaseInExpoInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return c * powf( 2.f, 10 * ( factor - 1.f ) ) + begin;
  }
};

class EaseOutExpoInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return c * ( -powf( 2.f, -10 * factor ) + 1.f ) + begin;
  }
};


class EaseInOutExpoInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    float t = factor * 2.f;
    if( t < 1.f ) return c * 0.5f * powf( 2.f, 10 * ( t - 1.f ) ) + begin;
    return c*0.5f * ( -powf( 2.f, -10.f * --t ) + 2 ) + begin;
  }
};

////////////
/// SINE ///
////////////

class EaseInSineInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return -c * cosf( ( float ) ( factor * M_PI * 0.5f ) ) + c + begin;
  }
};

class EaseOutSineInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return c * sinf( ( float ) ( factor * M_PI * 0.5f ) ) + begin;
  }
};


class EaseInOutSineInterpolation : public IInterpolation {
public:
  template< typename T > inline const T operator() ( const T& begin, const T& end, const float factor ) const {
    if( factor <= 0.0f ) return begin;
    if( factor >= 1.0f ) return end;
    const T c = end - begin;
    return -c * 0.5f * ( cosf( ( float ) ( M_PI * factor ) ) - 1.f ) + begin;
  }
};

//GENERAL INTERPOLATOR



class IInterpolatorAccess {
public:
  virtual ~IInterpolatorAccess( ) { }
  virtual float blend( const float begin, const float end, const float factor ) const = 0;
};

template< class CInterpolatorMethod >
class TInterpolatorAccess : public IInterpolatorAccess {
  void checkTypeInput( ) {
    //  COMPILE_TIME_ASSERT(SUPERSUB_INHERIT_CLASS_STRICT_CHECK(IInterpolation,CInterpolatorMethod),CInterpolatiorMethod_MUST_INHERIT_FROM_IInterpolation) 
  }
  CInterpolatorMethod instance;
public:
  float blend( const float begin, const float end, const float factor ) const {
    return instance( begin, end, factor );
  }
  TInterpolatorAccess( ) { checkTypeInput( ); }
};

//INTERPOLATOR VALUE

template< class CInterpolatorMethod, typename T = float>
class TInterpolatorValue {
private:

  void checkTypeInput( ) {
    //  COMPILE_TIME_ASSERT(SUPERSUB_INHERIT_CLASS_STRICT_CHECK(IInterpolation,CInterpolatorMethod),CInterpolatiorMethod_MUST_INHERIT_FROM_IInterpolation) 
  }

  T from;
  T to;
  T interp;
  float time_to_go;
  float time_to_interp;

  CInterpolatorMethod interpolator;

public:
  TInterpolatorValue( ) :time_to_interp( 1 ) { reset( ); checkTypeInput( ); }

  void setTotalTime( const float total_time ) { time_to_interp = total_time; }
  void setValue( const T new_target ) { from = interp; to = new_target; time_to_go = 0; }
  bool update( const float elapsed ) {
    time_to_go += elapsed;
    bool finished = false;
    if( time_to_go > time_to_interp ) { time_to_go = time_to_interp; finished = true; }
    interp = interpolator( from, to, time_to_go / time_to_interp );
    return finished;
  }
  void reset( const T new_value = 0 ) { from = new_value; to = new_value; interp = new_value; time_to_go = 0.f; }

  inline const T getValue( ) const { return interp; }
  inline const T getTarget( ) const { return to; }

};

#endif
