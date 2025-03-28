#include <cstdlib>
#include <memory>

#include "ortools/base/logging.h"
#include "ortools/linear_solver/linear_solver.h"

namespace operations_research {
	void clase1() {
        std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));
        if (!solver) {
            LOG(WARNING) << "No se pudo inicializar el solver GLOP";
            return;
        }

        // Necesario para limites de variables y restricciones
        const double infinity = solver->infinity();

        MPVariable* const x1 = solver->MakeNumVar(0.0, infinity, "x1"); 
        MPVariable* const x2 = solver->MakeNumVar(0.0, infinity, "x2"); 
        MPVariable* const x3 = solver->MakeNumVar(0.0, infinity, "x3"); 
        MPVariable* const x4 = solver->MakeNumVar(0.0, infinity, "x4"); 


        // Create a linear constraint, x1 + 2x2 + 2x3 <= 40.
        MPConstraint* const constraint_1 = solver->MakeRowConstraint(-infinity, 40.0, "Const 1");
        constraint_1->SetCoefficient(x1, 1);
        constraint_1->SetCoefficient(x2, 2);
        constraint_1->SetCoefficient(x3, 2);
        constraint_1->SetCoefficient(x4, 0);

        // Create a linear constraint, 2x1 - x2 + x3 + 2x4 <= 8.
		MPConstraint* const constraint_2 = solver->MakeRowConstraint(-infinity, 8.0, "Const 2");
		constraint_2->SetCoefficient(x1, 2);
		constraint_2->SetCoefficient(x2, -1);
		constraint_2->SetCoefficient(x3, 1);
		constraint_2->SetCoefficient(x4, 2);
		
        // Create a linear constraint, 4x1 - 2x2 + x3 - x4 <= 10.
		MPConstraint* const constraint_3 = solver->MakeRowConstraint(-infinity, 10.0, "Const 3");
		constraint_3->SetCoefficient(x1, 4);
		constraint_3->SetCoefficient(x2, -2);
		constraint_3->SetCoefficient(x3, 1);
		constraint_3->SetCoefficient(x4, -1);
		
		// Create the objective function, 2x1 + x2 - 3x3 + 5x4.
		MPObjective* const objective = solver->MutableObjective();
		objective->SetCoefficient(x1, 2);
		objective->SetCoefficient(x2, 1);
		objective->SetCoefficient(x3, -3);
		objective->SetCoefficient(x4, 5);
		objective->SetMaximization(); // Maximizar Z = 2x1 + x2 - 3x3 + 5x4


        LOG(INFO) << "Solving with " << solver->SolverVersion();
        const MPSolver::ResultStatus result_status = solver->Solve();

        // Check that the problem has an optimal solution.
        LOG(INFO) << "Status: " << result_status;
        if (result_status != MPSolver::OPTIMAL) {
            LOG(INFO) << "Este problema no tiene una sol optima";
            if (result_status == MPSolver::FEASIBLE) {
                LOG(INFO) << "Se acaba de encontrar una solucion factible";
            }
            else {
                LOG(WARNING) << "Hubo un problema, Solver no pudo resolverlo";
                return;
            }
        }

		LOG(INFO) << "Objective value = " << objective->Value();
		LOG(INFO) << "x1 = " << x1->solution_value();
		LOG(INFO) << "x2 = " << x2->solution_value();
		LOG(INFO) << "x3 = " << x3->solution_value();
		LOG(INFO) << "x4 = " << x4->solution_value();
	}
}