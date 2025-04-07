#include <cstdlib>
#include <memory>

#include "ortools/base/logging.h"
#include "ortools/linear_solver/linear_solver.h"

namespace operations_research {
	void parcial2() {
        std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));
        if (!solver) {
            LOG(WARNING) << "No se pudo inicializar el solver GLOP";
            return;
        }

        // Necesario para limites de variables y restricciones
        const double infinity = solver->infinity();

        // Variables para representar Xe y X1
		MPVariable* const xe = solver->MakeNumVar(0.0, infinity, "Xe"); //Xe
		MPVariable* const x1 = solver->MakeNumVar(0.0, infinity, "X1"); //X1

		// Create a linear constraint, Xe + 2X1 <= 6.
		MPConstraint* const constraint_1 = solver->MakeRowConstraint(-infinity, 6.0, "S1");
		constraint_1->SetCoefficient(xe, 1);
		constraint_1->SetCoefficient(x1, 2);
		
		// Create a linear constraint, 2Xe + X1 <= 8.
		MPConstraint* const constraint_2 = solver->MakeRowConstraint(-infinity, 8.0, "S2");
		constraint_2->SetCoefficient(xe, 2);
		constraint_2->SetCoefficient(x1, 1);
		
		// Create a linear constraint, -Xe + X1 <= 1.
		MPConstraint* const constraint_3 = solver->MakeRowConstraint(-infinity, 1.0, "S3");
		constraint_3->SetCoefficient(xe, -1);
		constraint_3->SetCoefficient(x1, 1);
		
		// Create a linear constraint, X1 <= 2.
		MPConstraint* const constraint_4 = solver->MakeRowConstraint(-infinity, 2.0, "S4");
		constraint_4->SetCoefficient(xe, 0);
		constraint_4->SetCoefficient(x1, 1);
		
		// Objective function, Z max = 3Xe + 2X1.
		MPObjective* const objective = solver->MutableObjective();
		objective->SetCoefficient(xe, 3);
		objective->SetCoefficient(x1, 2);
		objective->SetMaximization(); // Maximizar Z = 3Xe + 2X1
		
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
		LOG(INFO) << "xe = " << xe->solution_value();
		LOG(INFO) << "x1 = " << x1->solution_value();
	}
}