// __BEGIN_LICENSE__
// Copyright (C) 2006-2011 United States Government as represented by
// the Administrator of the National Aeronautics and Space Administration.
// All Rights Reserved.
// __END_LICENSE__


#include <gtest/gtest_VW.h>
#include <vw/Math/Vector.h>
#include <vw/Math/NelderMead.h>

using namespace vw;
using namespace vw::math;

static const double DELTA = 1e-4;

// This quadratic function has a single minimum at [0.1962, 0.4846].
struct QuadraticFunction {
  typedef double result_type;
  typedef Vector2 domain_type;
  typedef Vector2 gradient_type;

  result_type operator()( domain_type const& x ) const {
    return 1.2 * pow(x[0] - 0.6, 2) + 1.7 * pow(x[1] - 0.6, 2) + 2 * x[0] * x[1];
  }
  gradient_type gradient( domain_type const& x ) const {
    return Vector2( 2.4*x[0]-1.44+2*x[1],
                    3.4*x[1]-2.04+2*x[0]);
  }

  unsigned dimension() const { return 2; }
};


static double quadratic_c_function( Vector2 const& x ) {
  return 1.2 * pow(x[0] - 0.6, 2) + 1.7 * pow(x[1] - 0.6, 2) + 2 * x[0] * x[1];
}


TEST(NelderMead, FunctorCostFunction) {
  Vector2 initial_guess(2,2);
  QuadraticFunction cost_functor;
  int status;
  QuadraticFunction::domain_type result = nelder_mead( cost_functor, initial_guess, status );

  EXPECT_NEAR( 0.1962, result[0], DELTA );
  EXPECT_NEAR( 0.4846, result[1], DELTA );
}

TEST(NelderMead, CCostFunction) {
  Vector2 initial_guess(2,2);
  int status;
  Vector2 result = nelder_mead( &quadratic_c_function, initial_guess, status );
  EXPECT_NEAR( 0.1962, result[0], DELTA );
  EXPECT_NEAR( 0.4846, result[1], DELTA );
}
