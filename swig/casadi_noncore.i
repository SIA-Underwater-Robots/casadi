#ifdef WITH_SWIG_SPLIT
%module casadi_noncore

%include "common.i"

%import "casadi_primitive_tools.i"
#endif //WITH_SWIG_SPLIT


// FX
%include "casadi_fx.i"

// integration
%include "casadi_integration.i"

// optimal_control
%include "casadi_optimal_control.i"

// nonlinear programming
%include "casadi_nonlinear_programming.i"

// interfaces
%include "casadi_interfaces.i"


