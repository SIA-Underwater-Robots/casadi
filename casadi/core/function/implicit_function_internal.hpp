/*
 *    This file is part of CasADi.
 *
 *    CasADi -- A symbolic framework for dynamic optimization.
 *    Copyright (C) 2010 by Joel Andersson, Moritz Diehl, K.U.Leuven. All rights reserved.
 *
 *    CasADi is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 3 of the License, or (at your option) any later version.
 *
 *    CasADi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with CasADi; if not, write to the Free Software
 *    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef IMPLICIT_FUNCTION_INTERNAL_HPP
#define IMPLICIT_FUNCTION_INTERNAL_HPP

#include "implicit_function.hpp"
#include "function_internal.hpp"
#include "linear_solver.hpp"
#include "plugin_interface.hpp"


/// \cond INTERNAL
namespace casadi {

  /// Internal class
  class CASADI_CORE_EXPORT ImplicitFunctionInternal : public FunctionInternal, public PluginInterface<ImplicitFunctionInternal> {
  public:
    /** \brief Constructor
     *
     * \param f   Function mapping from (n+1) inputs to 1 output.
     */
    ImplicitFunctionInternal(const Function& f, const Function& J, const LinearSolver& linsol);

    /// Destructor
    virtual ~ImplicitFunctionInternal() = 0;

    /** \brief  Clone */
    virtual ImplicitFunctionInternal* clone() const=0;

    /** \brief  Deep copy data members */
    virtual void deepCopyMembers(std::map<SharedObjectNode*, SharedObject>& already_copied);

    /** \brief  Create a new ImplicitFunctionInternal */
    virtual ImplicitFunctionInternal* create(const Function& f, const Function& jac,
                                             const LinearSolver& linsol) const = 0;

    /// Initialize
    virtual void init();

    /** \brief  Propagate the sparsity pattern through a set of
     * directional derivatives forward or backward */
    virtual void spEvaluate(bool fwd);

    /// Is the class able to propagate seeds through the algorithm?
    virtual bool spCanEvaluate(bool fwd) { return true;}

    /// Solve the system of equations and calculate derivatives
    virtual void evaluate();

    /// Solve the nonlinear system of equations
    virtual void solveNonLinear() = 0;

    // The following functions are called internally from EvaluateMX.
    // For documentation, see the MXNode class
    ///@{
    virtual void evaluateMX(MXNode* node, const MXPtrV& arg, MXPtrV& res, const MXPtrVV& fseed,
                            MXPtrVV& fsens, const MXPtrVV& aseed, MXPtrVV& asens,
                            bool output_given);
    ///@}

    /// Number of equations
    int n_;

    /// The function f(z, x1, x2, ..., xn) == 0
    Function f_;

    /// Jacobian of f with respect to z
    Function jac_;

    /// Linear solver
    LinearSolver linsol_;

    /// Factorization up-to-date?
    bool fact_up_to_date_;

    /// Constraints on decision variables
    std::vector<int> u_c_;

    /// Indices of the input and output that correspond to the actual root-finding
    int iin_, iout_;

    // Creator function for internal class
    typedef ImplicitFunctionInternal* (*Creator)(const Function& f, const Function& J, const LinearSolver& linsol);

    /// Collection of solvers
    static std::map<std::string, Plugin> solvers_;

    /// Infix
    static const std::string infix_;
  };



} // namespace casadi
/// \endcond

#endif //IMPLICIT_FUNCTION_INTERNAL_HPP

