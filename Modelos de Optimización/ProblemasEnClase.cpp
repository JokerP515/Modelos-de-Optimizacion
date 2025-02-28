#include <cstdlib>
#include <memory>

#include "ortools/base/logging.h"
#include "ortools/linear_solver/linear_solver.h"

namespace operations_research {
    void utilidadPinturas() {
        //LOG(INFO) << "Google OR-Tools version : " << OrToolsVersion::VersionString();

        // Create the linear solver with the GLOP backend.
        std::unique_ptr<MPSolver> solver(MPSolver::CreateSolver("GLOP"));
        if (!solver) {
            LOG(WARNING) << "No se pudo inicializar el solver GLOP";
            return;
        }

        // Necesario para limites de variables y restricciones
        const double infinity = solver->infinity();

        // Variables para representar toneladas producidas diariamente de pintura para interiores y exteriores
        MPVariable* const x1 = solver->MakeNumVar(0.0, infinity, "Exteriores"); //Exteriores
        MPVariable* const x2 = solver->MakeNumVar(0.0, infinity, "Interiores"); //Interiores

        //LOG(INFO) << "Number of variables = " << solver->NumVariables();

        // Create a linear constraint, 6 * x1 + 4 * x2 <= 24.
        MPConstraint* const cantidadM1 = solver->MakeRowConstraint(-infinity, 24.0, "Disponibilidad diaria max M1");
        cantidadM1->SetCoefficient(x1, 6);
        cantidadM1->SetCoefficient(x2, 4);

        // Create a linear constraint, x1 + 2*x2 <= 6.
        MPConstraint* const cantidadM2 = solver->MakeRowConstraint(-infinity, 6.0, "Disponibilidad diaria max M2");
        cantidadM2->SetCoefficient(x1, 1);
        cantidadM2->SetCoefficient(x2, 2);

        // Create a linear constraint, -x1 + x2 <= 1.
        MPConstraint* const limiteMercado = solver->MakeRowConstraint(-infinity, 1.0, "limite del mercado");
        limiteMercado->SetCoefficient(x1, -1);
        limiteMercado->SetCoefficient(x2, 1);

        // Create a linear constraint, x2 <= 2.
        MPConstraint* const limiteDemandaX2 = solver->MakeRowConstraint(-infinity, 2.0, "Limite de la demanda de x2");
        limiteDemandaX2->SetCoefficient(x2, 1);


        //LOG(INFO) << "Number of constraints = " << solver->NumConstraints();

        // Create the objective function, 5 * x1 + 4 * x2.
        MPObjective* const objective = solver->MutableObjective();
        objective->SetCoefficient(x1, 5);
        objective->SetCoefficient(x2, 4);
        objective->SetMaximization(); // Maximizar Z = 5 * x1 + 4 * x2

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

        LOG(INFO) << "Solucion encontrada:";
        LOG(INFO) << "Valor max encontrado = " << objective->Value();
        LOG(INFO) << "Valor de x1 = " << x1->solution_value();
        LOG(INFO) << "Valor de x2 = " << x2->solution_value();

        LOG(INFO) << "Costo de la operacion realizada:";
        LOG(INFO) << "Problema resuelto en: " << solver->wall_time() << " milliseg";
        LOG(INFO) << "Problema resuelto en: " << solver->iterations() << " iteracion/es";
    }
} // namespace operations_research